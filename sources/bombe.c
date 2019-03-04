#include "../includes/main.h"

/*void    bombeDraw(game_t *game) {
  bomb->useClips = 0;
  game->bomb = bomb;
  if ( game->bomb->bombTexture )
    {
      SDL_Rect dest = { 640/2 - bombeSurface->w/2,480/2 - bombeSurface->h/2, bombeSurface->w, bombeSurface->h};
      SDL_BlitSurface(bombeSurface,NULL,SDL_GetWindowSurface(game->sdl->window),&dest);
      for (int i = 0; i < 4; ++i){
	game->bomb->clips[i].x = i / 2 * iW;
	game->bomb->clips[i].y = i % 2 * iH;
	game->bomb->clips[i].w = iW;
	game->bomb->clips[i].h = iH;
      }
      renderTexture(game->bomb->bombTexture, game, game->bomb->position.x, game->bomb->position.y, &game->bomb->clips[game->bomb->useClips]);
    }
  else
    {
      fprintf(stdout,"Échec de création de la texture (%s)\n",SDL_GetError());
    }

  SDL_FreeSurface(bombeSurface);
}*/

void  placeBomb(game_t *game, int x, int y)
{
  bomb_node_t* bomb_node = malloc(sizeof *bomb_node);
  bomb_node->prev = NULL;
  bomb_node->next = NULL;
  bomb_t* bomb = malloc(sizeof *bomb);
  bomb->position.x = x;
  bomb->position.y = y;
  bomb->position.w = 40;
  bomb->position.h = 40;
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

void removeBombNode(bombs_t *bombs, bomb_node_t *bomb_node)
{
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

void removeBomb(game_t *game, bomb_t *bomb/*bomb_node_t *bomb_node*/)
{
  bomb_node_t *tmp_node = game->bombs->first;

  while (tmp_node != NULL) {
    if (tmp_node->bomb->position.x == bomb->position.x && tmp_node->bomb->position.y == bomb->position.y) {
      removeBombNode(game->bombs, tmp_node);
      free(tmp_node);
      break;
    }
    tmp_node = tmp_node->next;
  }
}