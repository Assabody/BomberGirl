#include "../includes/main.h"

void renderTexture(SDL_Texture *tex, game_t *game, int x, int y, SDL_Rect *clip)
{
  SDL_Rect dst;
  dst.x = x;
  dst.y = y;
  if (clip != NULL){
    dst.w = clip->w;
    dst.h = clip->h;
  }
  else {
    SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
  }
  SDL_RenderCopy(game->sdl->renderer, tex, clip, &dst);
}
