#include "../includes/main.h"


int drawGame(game_t *game)
{
    if (game == NULL)
        return (EXIT_FAILURE);

    SDL_SetRenderDrawColor(game->sdl->renderer, 50, 50, 50, 255);
    while (game->running) {
        SDL_RenderClear(game->sdl->renderer);
        checkEvents(game);
        send_request(game->client_sock, game->player_key, &game->request);
        usleep(1000);
        getServerInfo(game->client_sock, game);

        SDL_RenderClear(game->sdl->renderer);
        updateBombs(game);
        drawMap(game);
        drawBombs(game);
        drawPlayer(game);
        SDL_RenderPresent(game->sdl->renderer);
        //usleep(10000);
    }
    return (EXIT_SUCCESS);
}
