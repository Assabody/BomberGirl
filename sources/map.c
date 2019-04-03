#include "../includes/main.h"
#include "../network/server.h"

void mapInit(game_infos_t *game_infos)
{
  for (int y = 0; y <= Y_MAP_SIZE; y++)
  {
    for (int x = 0; x <= X_MAP_SIZE; x++)
    {
      game_infos->map[y][x].cell = 0;
      game_infos->map[y][x].duration = 0;
      if (x == X_MAP_SIZE - 1 || y == Y_MAP_SIZE - 1 || x == 0 || y == 0)
      {
        // borders
        game_infos->map[y][x].cell = unbreakable_wall_cell(0);
      }
      else if (x % 2 == 0 && y % 2 == 0)
      {
        // every two lines and rows
        game_infos->map[y][x].cell = unbreakable_wall_cell(0);
      }
      else if (
          (x >= 1 && x <= 2 && y >= 1 && y <= 2) ||
          (x >= X_MAP_SIZE - 3 && x <= X_MAP_SIZE - 2 && y >= Y_MAP_SIZE - 3 && y <= Y_MAP_SIZE - 2) ||
          (x >= 1 && x <= 2 && y >= Y_MAP_SIZE - 3 && y <= Y_MAP_SIZE - 2) ||
          (x >= X_MAP_SIZE - 3 && x <= X_MAP_SIZE - 2 && y >= 1 && y <= 2))
      {
        // Put grass where the players spawn
        game_infos->map[y][x].cell = grass_cell(0);
      }
      else
      {
        game_infos->map[y][x].cell = breakable_wall_cell(0);
        /* if (randomNumber(1, 3) == 3)
        { */
          printf("Setting bomb bonus on x%d y%d\n", x, y);
          set_bonus(&game_infos->map[y][x], BOMB_NUMBER_BONUS);
        /* } */
      }
    }
  }
}

void print_map(game_t *game)
{
  for (int y = 0; y < Y_MAP_SIZE; y++)
  {
    for (int x = 0; x < X_MAP_SIZE; x++)
    {
      switch (get_cell_type(game->map[y][x].cell))
      {
      case MAP_WALL_UNBREAKABLE:
        printf("u");
        break;
      case MAP_WALL_BREAKABLE:
        printf("b");
        break;
      case MAP_GRASS:
        printf("g");
        break;
      default:
        printf("\nother: %d\n", get_cell_type(game->map[y][x].cell));
      }
      putchar(' ');
    }
    putchar('\n');
  }
}
