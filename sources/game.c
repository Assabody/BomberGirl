#include "../includes/main.h"


int drawGame(game_t *game)
{
    Uint32 frameStart;
    int frameTime;

    if (game == NULL)
        return (EXIT_FAILURE);

    SDL_SetRenderDrawColor(game->sdl->renderer, 50, 50, 50, 255);
    while (game->running) {
        frameStart = SDL_GetTicks();

        SDL_RenderClear(game->sdl->renderer);
        checkEvents(game);
        send_request(game);
        usleep(1000);
        getServerInfo(game->client_sock, game);

        SDL_RenderClear(game->sdl->renderer);
        drawMap(game);
        drawPlayer(game);
	drawHUD(game);
        SDL_RenderPresent(game->sdl->renderer);
        frameTime = SDL_GetTicks() - frameStart;
        if (TICKS_PER_FRAME > frameTime)
            SDL_Delay(TICKS_PER_FRAME - frameTime);
    }
    return (EXIT_SUCCESS);
}
