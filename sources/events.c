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
                    if (game->player[game->player_key].alive) {
                        game->request.command = 1;
                    }
                    break;
                case SDLK_ESCAPE:
                    game->running = 0;
                    printf("Vous quittez le jeu\n");
                    close(game->client_sock);
                    gameDestroy(game);
                    if (game->player_key == 0) {
                        stopServer(game);
                    }
                    exit(0);
                    break;
                case SDLK_UP:
                case SDLK_DOWN:
                case SDLK_LEFT:
                case SDLK_RIGHT:
                    if (game->player[game->player_key].alive) {
                        movePlayer(game, event.key.keysym.sym);
                    }
                    break;
                default:
                    fprintf(stderr, "Touche inconnue\n");
                    break;
            }
        }
    }
}
