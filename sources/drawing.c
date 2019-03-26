#include "../includes/main.h"

void drawMap(game_t *game) {
  breakablewall_t *breakable = malloc(sizeof *breakable);
  breakable->life = WALL_LIFE;
  SDL_Rect position;
    int x = 0;
    int y = 0;
    position.x = 0;
    position.y = 0;
    position.w = 40;
    position.h = 40;
    while (y < Y_MAP_SIZE) {
        while (x < X_MAP_SIZE) {
            switch (get_cell_type(game->map[y][x].cell)) {
                case MAP_BOMB:
                    SDL_RenderCopy(game->sdl->renderer, game->textures->bomb, NULL, &position);
                    break;
                case MAP_WALL_UNBREAKABLE:
                    SDL_RenderCopy(game->sdl->renderer, game->textures->stone, NULL, &position);
                    break;
                case MAP_WALL_BREAKABLE:
                    SDL_RenderCopy(game->sdl->renderer, game->textures->brick, NULL, &position);
                    break;
                case MAP_GRASS:
                    SDL_RenderCopy(game->sdl->renderer, game->textures->grass, NULL, &position);
                    break;
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
      if (bomb_node->bomb->duration == 0) {
      	bombExplosion(bomb_node->bomb, game);
	break;
      }
      renderTexture(
		    game->textures->bomb,
		    game->sdl,
		    bomb_node->bomb->x,
		    bomb_node->bomb->y,
		    &game->textures->bomb_clips[bomb_node->bomb->clip]);
      bomb_node = bomb_node->next;
    }
}

void drawPlayer(game_t *game) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        renderTexture(
                game->textures->player,
                game->sdl,
                game->player[i].x_pos,
                game->player[i].y_pos - 20,
                &game->textures->player_clips[game->player[i].current_dir]);
    }
}
