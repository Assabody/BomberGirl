#include "../includes/main.h"

int showMenu(game_t *game, TTF_Font *font)
{
    Uint32 time;
    int x, y;
    int menuSize = 2;
    char* labels[menuSize];
    labels[0] = strdup("New Game");
    labels[1] = strdup("Exit Game");
    SDL_Surface* menus[menuSize];
    int selected[] = {0, 0};
    SDL_Color color[] = {{255, 255, 255, 0}, {255, 0, 0, 0}};

    menus[0] = TTF_RenderText_Solid(font, labels[0], color[0]);
    menus[1] = TTF_RenderText_Solid(font, labels[1], color[0]);

    SDL_Rect pos[menuSize];
    pos[0].x = game->screenSize.x / 2;
    pos[0].y = game->screenSize.y / 2;
    pos[1].x = game->screenSize.x / 2;
    pos[1].y = game->screenSize.y / 2;

    //SDL_FillRect(screen, &screen->clip_rect, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    SDL_Event event;
    while (1) {
        time=SDL_GetTicks();
        while (SDL_PollEvent(&event)) {
            switch (event.type)
            {
                case SDL_QUIT:
                    for (int i = 0; i < menuSize; i++) {
                        SDL_FreeSurface(menus[i]);
                    }
                    return 1;
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                    for (int i = 0; i < menuSize; i++) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            if (!selected[i]) {
                                selected[i] = 1;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(font, labels[i], color[1]);
                            }
                        } else {
                            if (selected[i]) {
                                selected[i] = 0;
                                SDL_FreeSurface(menus[i]);
                                menus[i] = TTF_RenderText_Solid(font, labels[i], color[0]);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = event.button.x;
                    y = event.button.y;
                    for (int i = 0; i < menuSize; i++) {
                        if (x >= pos[i].x && x <= pos[i].x + pos[i].w && y >= pos[i].y && y <= pos[i].y + pos[i].h) {
                            for (int j = 0; j < menuSize; j++) {
                                SDL_FreeSurface(menus[i]);
                            }
                        }
                            return i;
                        }
                    break;
            }
        }
        for (int i = 0; i < menuSize; i++) {
            SDL_Texture *text_texture = SDL_CreateTextureFromSurface(game->renderer, menus[i]);
            SDL_RenderCopy(game->renderer, text_texture, NULL, &pos[i]);
            SDL_DestroyTexture(text_texture);
        }
        SDL_RenderPresent(game->renderer);
        if (1000 / 30> (SDL_GetTicks() - time)) {
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
        }
    }
}