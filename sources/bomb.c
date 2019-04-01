#include "../includes/main.h"

bombs_t *initBombs(void) {
    bombs_t *bombs = malloc(sizeof *bombs);

    if (bombs != NULL) {
        bombs->first = NULL;
        bombs->last = NULL;
    }
    return bombs;
}

void placeBomb(game_t *game, int x, int y) {
    bomb_node_t *bomb_node = malloc(sizeof *bomb_node);
    bomb_node->prev = NULL;
    bomb_node->next = NULL;
    bomb_t *bomb = malloc(sizeof *bomb);
    bomb->x = x;
    bomb->y = y;
    bomb->damages = DAMAGES;
    bomb->duration = 2 * FPS;
    bomb->clip = 0;
    if (game->bombs != NULL && bomb_node != NULL) {
        bomb_node->bomb = bomb;
        bomb_node->next = NULL;
        if (game->bombs->last == NULL) {
            bomb_node->prev = NULL;
            game->bombs->first = bomb_node;
            game->bombs->last = bomb_node;
        } else {
            bomb_node->prev = game->bombs->last;
            game->bombs->last->next = bomb_node;
            game->bombs->last = bomb_node;
        }
        printf("placeBomb()\n");
        game->request.command = 1;
        //game->request.magic = game->player[game->player_key].token ? game->player[game->player_key].token + 1 : 0;
    } else {
        free(bomb);
        free(bomb_node);
    }
}

void removeBomb(game_t *game, bomb_t *bomb) {
    bomb_node_t *tmp_node = game->bombs->first;

    while (tmp_node != NULL) {
        if (tmp_node->bomb->x == bomb->x && tmp_node->bomb->y == bomb->y) {
            removeBombNode(game->bombs, tmp_node);
            break;
        }
        tmp_node = tmp_node->next;
    }
}

void removeBombNode(bombs_t *bombs, bomb_node_t *bomb_node) {
    bomb_node_t *tmp_bomb = bomb_node;
    if (bomb_node->next == NULL && bomb_node->prev == NULL) { // element unique
        bombs->last = NULL;
        bombs->first = NULL;
    } else if (bomb_node->next == NULL) { // dernier element
        bombs->last = bomb_node->prev;
        bombs->last->next = NULL;
    } else if (bomb_node->prev == NULL) { // premier element
        bombs->first = bomb_node->next;
        bombs->first->prev = NULL;
    } else { // milieu
        bomb_node->next->prev = bomb_node->prev;
        bomb_node->prev->next = bomb_node->next;
    }
    free(tmp_bomb->bomb);
    free(tmp_bomb);
}

void updateBombs(game_t *game) {
    int bombs_count = 0;
    int count = 0;
    bomb_node_t *bomb_node = game->bombs->first;
    while (bomb_node != NULL) {
        count++;
        if (bomb_node->bomb != NULL) {
            bombs_count++;
            if (bomb_node->bomb->duration > 0) {
                if (bomb_node->bomb->duration > 80 && bomb_node->bomb->duration < 110) {
                    bomb_node->bomb->clip = 2;
                }
                if (bomb_node->bomb->duration > 15 && bomb_node->bomb->duration < 50) {
                    bomb_node->bomb->clip = 1;
                }
                if (bomb_node->bomb->duration > 0 && bomb_node->bomb->duration < 15) {
                    bomb_node->bomb->clip = 3;
                }
                bomb_node->bomb->duration--;
            } else {
                bomb_node->bomb = NULL;
            }
        }
        bomb_node = bomb_node->next;
    }
}

void bombCheckObjectRadius(game_t *game, bomb_t *bomb)
{
  if (get_cell_type(game->map[bomb->y / 40 ][bomb->x / 40 + RADIUS].cell) == MAP_WALL_BREAKABLE) {
    game->map[bomb->y / 40][bomb->x / 40 + RADIUS].cell = grass_cell(0);
  } else if (get_cell_type(game->map[bomb->y / 40 ][bomb->x / 40 - RADIUS].cell) == MAP_WALL_BREAKABLE) {
    game->map[bomb->y / 40][bomb->x / 40 - RADIUS].cell = grass_cell(0);
  } else if (get_cell_type(game->map[bomb->y / 40 - RADIUS][bomb->x / 40].cell) == MAP_WALL_BREAKABLE) {
    game->map[bomb->y / 40 - RADIUS][bomb->x / 40].cell = grass_cell(0);
  } else if (get_cell_type(game->map[bomb->y / 40 + RADIUS][bomb->x / 40].cell) == MAP_WALL_BREAKABLE) {
    game->map[bomb->y / 40 + RADIUS][bomb->x / 40].cell = grass_cell(0);
  }
  checkPlayerDamagesFromBombs(game, bomb);
}

void	checkPlayerDamagesFromBombs(game_t *game, bomb_t *bomb)
{ 
  if (bomb->y == game->player->y_pos && bomb->x == game->player->x_pos) {
      puts("Player ON BOMB");
  } else if (bomb->y / 40 + RADIUS == game->player->y_pos / 40
	     && bomb->x / 40 == game->player->x_pos / 40) {
    puts("Player under bomb");
  } else if (bomb->y / 40 - RADIUS == game->player->y_pos / 40
	     && bomb->x / 40 == game->player->x_pos / 40) {
    puts("Player over bomb");
  } else if (bomb->x / 40 - RADIUS == game->player->x_pos / 40
	     && bomb->y / 40 == game->player->y_pos / 40) {
    puts("Player before bomb");
  } else if (bomb->x / 40 + RADIUS == game->player->x_pos / 40
	     && bomb->y / 40 == game->player->y_pos / 40) {
    puts("Player after bomb");
  }
}

void	bombExplosion(bomb_t *bomb, game_t *game) {
    bombCheckObjectRadius(game, bomb);
}

void clearBombs(bombs_t *bombs) {
    puts("Clearing Bombs");

    bomb_node_t *tmp_node;

    if (bombs && bombs->first && bombs->last) {
        tmp_node = bombs->first;
        while (tmp_node != NULL) {
            bomb_node_t *tmp_delete = tmp_node;
            tmp_node = tmp_node->next;
            free(tmp_delete->bomb);
            free(tmp_delete);
        }
        free(tmp_node->bomb);
        free(bombs);
    }
    bombs = NULL;
    puts("Bombs cleared");
}

char *bombDurationToChar(bomb_t *bomb) {
    return serialize_int(bomb->duration);
}