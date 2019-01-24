#include "../includes/main.h"

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

