#include "../includes/main.h"

bombs_t *initBombs(void)
{
    bombs_t* bombs = malloc(sizeof *bombs);

    if (bombs != NULL) {
        bombs->first = NULL;
        bombs->last = NULL;
    }
    return (bombs);
}

void  placeBomb(game_t *game, int x, int y)
{
  bomb_node_t* bomb_node = malloc(sizeof *bomb_node);
  bomb_node->prev = NULL;
  bomb_node->next = NULL;
  bomb_t* bomb = malloc(sizeof *bomb);
  bomb->x = x;
  bomb->y = y;
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
  } else {
    free(bomb_node);
  }
}

void removeBomb(game_t *game, bomb_t *bomb)
{
  bomb_node_t *tmp_node = game->bombs->first;

  while (tmp_node != NULL) {
    if (tmp_node->bomb->x == bomb->x && tmp_node->bomb->y == bomb->y) {
      removeBombNode(game->bombs, tmp_node);
      free(tmp_node);
      break;
    }
    tmp_node = tmp_node->next;
  }
}

void removeBombNode(bombs_t *bombs, bomb_node_t *bomb_node) {
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
}

void updateBombs(game_t *game)
{
    int bombs_count = 0;
    int count = 0;
    bomb_node_t* bomb_node = game->bombs->first;
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