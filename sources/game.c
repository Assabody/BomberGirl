#include "../includes/main.h"

int drawGame(game_t *game) {
    if (game == NULL)
        return (EXIT_FAILURE);
    Uint32 frameStart;
    int frameTime;
    SDL_SetRenderDrawColor(game->sdl->renderer, 50, 50, 50, 255);
    while (game->running) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(game->sdl->renderer);
        updateBombs(game);
        drawMap(game);
        drawBombs(game);
        drawPlayer(game);
        checkEvents(game);
        SDL_RenderPresent(game->sdl->renderer);
        frameTime = SDL_GetTicks() - frameStart;
        if (TICKS_PER_FRAME > frameTime)
            SDL_Delay(TICKS_PER_FRAME - frameTime);
    }
    return (EXIT_SUCCESS);
}