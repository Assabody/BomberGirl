#include "../includes/main.h"


int drawGame(game_t *game)
{
    puts("STARTING GAME\n");
    if (game == NULL)
        return (EXIT_FAILURE);
    Uint32 frameStart;
    int frameTime;
    int wait_server = 1;
    SDL_SetRenderDrawColor(game->sdl->renderer, 50, 50, 50, 255);
    while (game->running) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(game->sdl->renderer);
        checkEvents(game);
        if (game->request.magic != 0) {
            puts("send request\n");
            send_request(game->client_sock, game->player_key, &game->request);
            wait_server = 1;
            game->request.magic = 0;
            game->request.command = 0;
        }
        if (!wait_server) {
            updateBombs(game);
            drawMap(game);
            drawBombs(game);
            drawPlayer(game);
            SDL_RenderPresent(game->sdl->renderer);
        } else {
            if (getServerInfo(game->client_sock, game))
                wait_server = 0;
        }
        frameTime = SDL_GetTicks() - frameStart;
        if (TICKS_PER_FRAME > frameTime)
            SDL_Delay(TICKS_PER_FRAME - frameTime);

    }
    return (EXIT_SUCCESS);
}
