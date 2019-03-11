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
            if (game->map[y][x] == MAP_GRASS) {
                SDL_RenderCopy(game->sdl->renderer, game->textures->grass, NULL, &position);
            } else if (game->map[y][x] == MAP_BOMB) {
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
        renderTexture(
                game->textures->bomb,
                game,
                bomb_node->bomb->x,
                bomb_node->bomb->y,
                &game->textures->bomb_clips[bomb_node->bomb->clip]);
        bomb_node = bomb_node->next;
    }
}

void drawPlayer(game_t *game) {
    renderTexture(
            game->textures->player,
            game,
            game->player->x_pos,
            game->player->y_pos - 20,
            &game->textures->player_clips[game->player->current_dir]);
}