#include "../includes/main.h"

void drawMap(game_t *game) {
    SDL_Rect position;
    int x = 0;
    int y = 0;
    position.x = 0;
    position.y = 0;
    position.w = 40;
    position.h = 40;

    while (game->map[y]) {
        while (game->map[y][x]) {
            if (game->map[y][x] == 'g') {
                SDL_RenderCopy(game->sdl->renderer, game->textures->grass, NULL, &position);
            } else if (game->map[y][x] == 'b') {
                SDL_RenderCopy(game->sdl->renderer, game->textures->bomb, NULL, &position);
            } else {
                SDL_RenderCopy(game->sdl->renderer, game->textures->stone, NULL, &position);
            }
            x++;
            position.x += 40;
        }
        x = 0;
        y++;
        position.y += 40;
        position.x = 0;
    }
}

void drawBombs(game_t *game) {
    bomb_node_t *bomb_node = game->bombs->first;
    while (bomb_node != NULL) {
        if (bomb_node->bomb->duration <= 0) {
            removeBomb(game, bomb_node->bomb);
            break;
        }
        renderTexture(game->textures->bomb, game, bomb_node->bomb->x, bomb_node->bomb->y,
                      &game->textures->bomb_clips[bomb_node->bomb->clip]);
        bomb_node = bomb_node->next;
    }
}

void drawPlayer(game_t *game) {
    renderTexture(game->textures->player, game, game->player->position.x, game->player->position.y - 20,
                  &game->textures->player_clips[game->player->clip]);
}

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