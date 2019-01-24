#include "../includes/main.h"

int init() {
    system_manager_t system_manager;
    texture_container_t *texture_container = malloc(sizeof(texture_container_t));
    SDL_Surface* surfaceGrass = IMG_Load("./assets/images/grass1.png");
    if (surfaceGrass == NULL) {
      printf("ERROR : FAILED TO LEAD THE IMAGE");
    }
    
    game_t *game = malloc(sizeof(game_t));
    game->renderer = NULL;
    
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stdout, SDL_GetError());
	// game_destroy();
        return -1;
    }

    /* Création de la fenêtre */
    SDL_Window *pWindow = NULL;
    pWindow = SDL_CreateWindow("Bombergirl", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480,
                               SDL_WINDOW_SHOWN);

    if (pWindow != NULL) {
        system_manager.running = 1;
    } else {
        system_manager.running = 0;
    }
    
    //Creation du renderer une fois la windows genere
    game->renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

    //Chargement d'une texture
    texture_container->grass = SDL_CreateTextureFromSurface(game->renderer, surfaceGrass);
    /* SDL_FreeSurface(surfaceGrass); */
    
    mapDraw(game, texture_container);
    playerDraw(game, texture_container);
    while(system_manager.running) {
	checkEvents(game, texture_container, &system_manager);
    }
    SDL_DestroyTexture(texture_container->grass);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}

int main()
{
  init();

  return 0;
}
