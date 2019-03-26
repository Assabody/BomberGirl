/*
** ETNA PROJECT, 17/01/2019 by *
** Bomberman
** File description:
**      Header file
*/

#ifndef     _PLAYER_H_
#define     _PLAYER_H_

typedef struct player_s
{
  int token;
  int alive;
  int x_pos;
  int y_pos;
  int current_dir;
  int current_speed;
  int max_speed;
  int bombs_left;
  int bombs_capacity;
  int frags;
  int life;
} player_t;

#endif
