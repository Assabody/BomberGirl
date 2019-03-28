#include "../includes/main.h"
#include "../network/request.h"

int joinGame(char *address, char *port, game_t *game) {
    if (address == NULL || port == NULL || strlen(address) <= 1 || strlen(port) <= 1) {
        return 0;
    }
    printf("Connecting to %s:%s...\n", address, port);
    game->client_sock = initClient(address, port, game);
    if (game->client_sock > 0) {
        return 1;
    }
    return 0;
}

int menuWindow(game_t *game) {
    int quit = 0;
    int counter = 0;
    SDL_Event event;
    int menu_size = 4;
    menu_t *menus = malloc(sizeof(menu_t) * 4);

    SDL_Color white = { 255, 255, 255, 255 };

    SDL_Rect text_pos;
    text_pos.y = 80;
    text_pos.x = 80;

    char *address = NULL;
    char *port = NULL;
    menus[0].text = strdup("Se connecter a une partie");
    menus[0].enabled = 0;
    menus[1].text = strdup("Heberger une partie");
    menus[1].enabled = 1;
    menus[2].text = strdup("Local");
    menus[2].enabled = 1;
    menus[3].text = strdup("Quitter");
    menus[3].enabled = 1;

    showMenu(game, menus, menu_size, counter);
    do {
        SDL_RenderClear(game->sdl->renderer);

        int update = 0;
        game->running = 1;
        SDL_WaitEvent(&event);
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN && counter < menu_size - 1) {
                update = 1;
                counter++;
            } else if (event.key.keysym.scancode == SDL_SCANCODE_UP && counter > 0) {
                update = 1;
                counter--;
            } else if (event.key.keysym.scancode == SDL_SCANCODE_SPACE || event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                update = 1;
                switch (counter) {
                    case 0:
                        if (menus[counter].enabled) {
                            address = showInputTextMenu(game, "addresse ip");
                            port = showInputTextMenu(game, "port");
                            if (joinGame(address, port, game)) {
                                drawGame(game);
                            } else {
                                showPromptMessage(game, "Cannot connect to the server", text_pos, white);
                            }
                            if (address && port) {
                                free(address);
                                free(port);
                            }
                        }

                        break;
                    case 1:
                        if (menus[counter].enabled) {
                            if (hostGame(game)) {
                                if (waitingLobby(game)) {
                                    drawGame(game);
                                } else {
                                    showPromptMessage(game, "Stopping server...", text_pos, white);
                                    //stopServer(game);
                                }
                            }
                        }
                        break;
                    case 2:
                        if (menus[counter].enabled) {
                            if (joinGame("127.0.0.1", "1234", game)) {
                                drawGame(game);
                            } else {
                                showPromptMessage(game, "Cannot connect to the server", text_pos, white);
                            }
                            if (address && port) {
                                free(address);
                                free(port);
                            }
                        }
                        break;
                    case 3:
                        quit = 1;
                        break;
                }
            }
        }
        if (event.type == SDL_QUIT)
            quit = 1;
        if (update) {
            showMenu(game, menus, menu_size, counter);
        }
    } while (!quit);
    game->running = 0;
    free(menus[0].text);
    free(menus[1].text);
    free(menus[2].text);
    free(menus[3].text);
    free(menus);
    return 1;
}

int hostGame(game_t *game) {
    SDL_Color white = { 255, 255, 255, 255 };
    char *input_port;
    char message[30];

    SDL_Rect pos;
    pos.x = 80;
    pos.y = 80;
    SDL_RenderClear(game->sdl->renderer);
    SDL_RenderPresent(game->sdl->renderer);
    input_port = showInputNumberMenu(game, "Host a game - Choose port (0-99999)");

    //startServer(game, input_port);

    if (!joinGame("127.0.0.1", input_port, game)) {
        showPromptMessage(game, "Failed to host a game", pos, white);
        //stopServer();
        return 0;
    } else if (game->client_sock  <= 0) {
        sprintf(message, "Cannot connect to localhost:%s", input_port);
        showPromptMessage(game, message, pos, white);
        //stopServer();
        return 0;
    }
    return 1;
}

int get_clients_number() {
    return 2;
}

int waitingLobby(game_t *game)
{
    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Rect pos;
    SDL_Event event;

    char message[30];
    pos.x = 80;
    pos.y = 80;
    SDL_RenderClear(game->sdl->renderer);
    showText(game, "Waiting for server to start...", pos, white);
    sprintf(message, "%d/%d players", get_clients_number(), MAX_PLAYERS);
    pos.y += 30;
    showText(game, message, pos, white);
    SDL_RenderPresent(game->sdl->renderer);
    while (1) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                return 0;
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
                    return 0;
                } else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN || event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                    return 1;
                }
                break;
        }
    }
}

void    showMenu(game_t *game, menu_t *menus, int menu_number, int current_menu)
{
    int width;
    int height;
    int texW = 0;
    int texH = 0;
    int menuHeight = 30;
    SDL_Rect bgDstrect = { 0, 0, 600, 520 };
    SDL_Color disabled = { 150, 150, 150, 255 };
    SDL_Color enabled = { 255, 255, 255, 255 };
    SDL_GetRendererOutputSize(game->sdl->renderer, &width, &height);
    SDL_RenderClear(game->sdl->renderer);
    SDL_RenderCopy(game->sdl->renderer, game->textures->menu, NULL, &bgDstrect);
    SDL_Texture *texture;
    SDL_Surface *surface;
    SDL_Rect text_pos;
    for (int i = menu_number - 1; i >= 0; i--) {
      text_pos.y = height / 2 - menu_number * menuHeight / 2 + menuHeight * i;
      text_pos.x = 80;
      surface = TTF_RenderText_Solid(game->sdl->font, menus[i].text, menus[i].enabled ? enabled : disabled);
      texture = SDL_CreateTextureFromSurface(game->sdl->renderer, surface);
      SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
      SDL_Rect dstrect = { text_pos.x, text_pos.y, texW, texH };
      SDL_RenderCopy(game->sdl->renderer, texture, NULL, &dstrect);
      SDL_DestroyTexture(texture);
      SDL_FreeSurface(surface);
    }
    showSelection(game, current_menu);
    SDL_RenderPresent(game->sdl->renderer);
}

void    showSelection(game_t *game, int menu_selected_number)
{
    int width;
    int height;
    SDL_Rect selection_pos;

    SDL_GetRendererOutputSize(game->sdl->renderer, &width, &height);
    selection_pos.x = 40;
    selection_pos.y = height / 2 - 3 * 25 / 2 + 30 * menu_selected_number - 25  ;
    selection_pos.w = 30;
    selection_pos.h = 30;

    SDL_Rect texture_pos;

    texture_pos.x = 0;
    texture_pos.y = 0;
    texture_pos.w = 40;
    texture_pos.h = 40;

    SDL_RenderCopy(game->sdl->renderer, game->textures->bomb, &texture_pos, &selection_pos);
}

char    *showInputNumberMenu(game_t *game, const char *placeholder)
{
    int width;
    int height;
    int texW = 0;
    int texH = 0;

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color gray = { 170, 170, 170, 255 };

    SDL_Rect text_pos;
    text_pos.y = 80;
    text_pos.x = 80;
    SDL_Rect placeholder_pos;
    placeholder_pos.y = 50;
    placeholder_pos.x = 80;

    char *text = NULL;

    text = strdup("");
    int done = 0;

    SDL_GetRendererOutputSize(game->sdl->renderer, &width, &height);
    SDL_StartTextInput();
    while (!done) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_TEXTINPUT:
                if ((strcmp(event.text.text, "0") == 0 ||
                    strcmp(event.text.text, "1") == 0 ||
                    strcmp(event.text.text, "2") == 0 ||
                    strcmp(event.text.text, "3") == 0 ||
                    strcmp(event.text.text, "4") == 0 ||
                    strcmp(event.text.text, "5") == 0 ||
                    strcmp(event.text.text, "6") == 0 ||
                    strcmp(event.text.text, "7") == 0 ||
                    strcmp(event.text.text, "8") == 0 ||
                    strcmp(event.text.text, "9") == 0)
                && strlen(text) / sizeof(*text) < 5) {
                    strcat(text, event.text.text);
                }
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                    if (strlen(text) > 1) {
                        text[strlen(text) - 1] = '\0';
                    } else {
                        text = strdup("");
                    }
                } else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    done = 1;
                }
                break;
        }

        SDL_Surface *surface;
        if(text && strcmp("", text) != 0)
            surface = TTF_RenderText_Solid(game->sdl->font, text, white);
        else
            surface = TTF_RenderText_Solid(game->sdl->font, "_", gray);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(game->sdl->renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = { text_pos.x, text_pos.y, texW, texH };
        SDL_RenderClear(game->sdl->renderer);
        showText(game, placeholder, placeholder_pos, white);
        SDL_RenderCopy(game->sdl->renderer, texture, NULL, &dstrect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(game->sdl->renderer);
    }
    SDL_StopTextInput();
    return text;
}

char    *showInputTextMenu(game_t *game, const char *placeholder)
{
    int width;
    int height;
    int texW = 0;
    int texH = 0;

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Color gray = { 170, 170, 170, 255 };

    SDL_Rect text_pos;
    text_pos.y = 80;
    text_pos.x = 80;
    SDL_Rect placeholder_pos;
    placeholder_pos.y = 50;
    placeholder_pos.x = 80;

    char *text = NULL;

    text = strdup("");
    int done = 0;

    SDL_GetRendererOutputSize(game->sdl->renderer, &width, &height);
    SDL_StartTextInput();
    while (!done) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_TEXTINPUT:
                if (strlen(text) / sizeof(*text) < 20)
                    strcat(text, event.text.text);
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                    if (strlen(text) > 1) {
                        text[strlen(text) - 1] = '\0';
                    } else {
                        text = strdup("");
                    }
                } else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    done = 1;
                }
                break;
        }

        SDL_Surface *surface;
        if(text && strcmp("", text) != 0)
            surface = TTF_RenderText_Solid(game->sdl->font, text, white);
        else
            surface = TTF_RenderText_Solid(game->sdl->font, "_", gray);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(game->sdl->renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = { text_pos.x, text_pos.y, texW, texH };
        SDL_RenderClear(game->sdl->renderer);
        showText(game, placeholder, placeholder_pos, white);
        SDL_RenderCopy(game->sdl->renderer, texture, NULL, &dstrect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(game->sdl->renderer);
    }
    SDL_StopTextInput();
    return text;
}

void showText(game_t *game, const char* text, SDL_Rect text_pos, SDL_Color color)
{
    int width;
    int height;
    int texW = 0;
    int texH = 0;

    printf("# Display Text: %s\n", text);
    SDL_GetRendererOutputSize(game->sdl->renderer, &width, &height);
    SDL_Surface *surface;
    surface = TTF_RenderText_Solid(game->sdl->font, text, color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(game->sdl->renderer, surface);
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { text_pos.x, text_pos.y, texW, texH };
    SDL_RenderCopy(game->sdl->renderer, texture, NULL, &dstrect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}


void showPromptMessage(game_t *game, const char* text, SDL_Rect text_pos, SDL_Color color)
{
    int width;
    int height;
    int texW = 0;
    int texH = 0;

    int done = 0;
    printf("# Display PromptMessage: %s\n", text);
    SDL_GetRendererOutputSize(game->sdl->renderer, &width, &height);
    while (!done) {
        SDL_RenderClear(game->sdl->renderer);
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                done = 1;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                    done = 1;
                }
                break;
        }
        SDL_Surface *surface;
        surface = TTF_RenderText_Solid(game->sdl->font, text, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(game->sdl->renderer, surface);
        SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
        SDL_Rect dstrect = { text_pos.x, text_pos.y, texW, texH };
        SDL_RenderCopy(game->sdl->renderer, texture, NULL, &dstrect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        SDL_RenderPresent(game->sdl->renderer);
    }
}
