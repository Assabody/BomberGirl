#include "../includes/main.h"

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
    SDL_Surface* surfaceGrass = IMG_Load("./assets/images/grass1.png");
    texture_container->grass = SDL_CreateTextureFromSurface(game->renderer, surfaceGrass);
    SDL_FreeSurface(surfaceGrass);
    
    while(system_manager.running) {
        mapDraw(game, texture_container);
        playerDraw(game, texture_container);
	checkEvents(game, texture_container, &system_manager);
    }
    SDL_DestroyTexture(texture_container->grass);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(pWindow);
    SDL_Quit();
    return 0;
}

void    playerDraw(game_t *game, texture_container_t *texture_container) {
     SDL_Rect dstrect = { 40, 40, 40, 40 };
    SDL_Surface* image = IMG_Load("./assets/images/bombergirl.png");

    if (image == NULL) {
        printf("ERROR : FAILED TO LEAD THE IMAGE");
    }
    texture_container->player = SDL_CreateTextureFromSurface(game->renderer, image);
    /* SDL_FreeSurface(image); */
    SDL_RenderCopy(game->renderer, texture_container->player, NULL, &dstrect);
    SDL_RenderPresent(game->renderer);
}

void	movePlayer(game_t *game, texture_container_t *texture_container, system_manager_t *system_manager, char *direction) {
  (void) system_manager;
  (void) game;
  (void) texture_container;
  printf(direction);
}


void    bombeDraw(game_t *game, texture_container_t *texture_container) {
    SDL_Rect dstrect = { 40, 40, 40, 40 };
    SDL_Surface* image = IMG_Load("./assets/images/bombe.png");
    
    if (image == NULL) {
        printf("ERROR : FAILED TO LEAD THE IMAGE");
    }
    texture_container->bombe = SDL_CreateTextureFromSurface(game->renderer, image);
    /* SDL_FreeSurface(image);    */
    SDL_RenderCopy(game->renderer, texture_container->bombe, NULL, &dstrect);
    SDL_RenderPresent(game->renderer);
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
