#include "../includes/main.h"


int drawGame(game_t *game)
{
    puts("STARTING GAME\n");
    if (game == NULL)
        return (EXIT_FAILURE);
    Uint32 frameStart;
    int frameTime;
    SDL_SetRenderDrawColor(game->sdl->renderer, 50, 50, 50, 255);
    while (game->running) {
        frameStart = SDL_GetTicks();
        SDL_RenderClear(game->sdl->renderer);
        if (game->request.magic != 0) {
            puts("send request\n");
            send_request(game->client_sock, &game->request);
            getServerInfo(game->client_sock, game);

            game->request.magic = 0;
            game->request.command = 0;
        }
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

/*int sendDataToServer(game_t *game)
{
    puts("sending data to server");
    return 1;
}*/

/*
int fetchDataFromServer(game_t *game)
{
    puts("fetching data from server");
    char *msg = read_message(game->client_sock, 10);
    if (msg != NULL) {
        puts(msg);
    }
    return 1;
}*/
