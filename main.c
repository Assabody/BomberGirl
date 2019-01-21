#include "headers/main.h"

int init() {
    system_manager_t system_manager;
    texture_container_t *texture_container = malloc(sizeof(texture_container_t));
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
    pWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480,
                               SDL_WINDOW_SHOWN);

    if (pWindow != NULL) {
        system_manager.running = 1;
    } else {
        system_manager.running = 0;
    }
    //_________________________________//
    //Creation du renderer une fois la windows genere
    game->renderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);
    //Chargement d'une texture
    SDL_Surface* surfaceGrass = IMG_Load("./grass1.png"); //SDL_LoadBMP("./grass1.png");
    texture_container->grass = SDL_CreateTextureFromSurface(game->renderer, surfaceGrass);
    SDL_FreeSurface(surfaceGrass);
    //_________________________________//
    
    while(system_manager.running) {
      mapDraw(game, texture_container);
      inputManager(&system_manager);
    }
    SDL_Quit();
    return 0;
}

void inputManager(system_manager_t *manager) {
    while (SDL_PollEvent(&manager->events)) {
        switch (manager->events.type) {
            case SDL_QUIT:
                manager->running = 0;
                break;
        }
    }
}

void mapDraw(game_t *game, texture_container_t *texture_container)
{
  texture_container->grassPosition.x = 0;
  texture_container->grassPosition.y = 0;
  texture_container->grassPosition.w = 40;
  texture_container->grassPosition.h = 40;

  SDL_SetRenderDrawColor(game->renderer, 50, 50, 50, 255);
  SDL_RenderClear(game->renderer);

  //Affichage de la map
  while (texture_container->grassPosition.y < 480) {
      while (texture_container->grassPosition.x < 640) {
	//Affichage de la texture
	SDL_RenderCopy(game->renderer, texture_container->grass, NULL, &texture_container->grassPosition);
	texture_container->grassPosition.x += 40;
      }
      texture_container->grassPosition.x = 0;
      texture_container->grassPosition.y += 40;
    }
  SDL_RenderPresent(game->renderer);
}

int main()
{
  init();
  //  gameDraw(game);
  //game_destroy();

  return 0;
}
