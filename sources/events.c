#include "../includes/main.h"


void checkEvents(game_t *game) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            printf("Vous quittez le jeu\n");
            close(game->client_sock);
            game->running = 0;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_SPACE:
                    game->request.command = 1;
                    //placeBomb(game, game->player[game->player_key].x_pos, game->player[game->player_key].y_pos);
                    break;
                case SDLK_ESCAPE:
                    game->running = 0;
                    printf("Vous quittez le jeu\n");
                    close(game->client_sock);
                    break;
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    movePlayer(game, event.key.keysym.sym);
                    break;
                default:
                    fprintf(stderr, "Touche inconnue\n");
                    break;
            }
        }
    }
}