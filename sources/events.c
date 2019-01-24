#include "../includes/main.h"

void    checkEvents(game_t *game, texture_container_t *texture_container, system_manager_t *system_manager)
{
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {

    switch (event.type) {
    case SDL_QUIT:
      system_manager->running = 0;
      printf("Vous quittez le jeu");
      break;
    }    
    switch (event.key.keysym.sym) {
    case SDLK_SPACE:
      bombeDraw(game, texture_container);
      break;
    case SDLK_UP:
      movePlayer(game, texture_container, system_manager, "up");
      break;
    }

  }

}
