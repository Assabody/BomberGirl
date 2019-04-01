#include "../includes/main.h"
#include "../network/request.h"

int joinGame(char *address, char *port, game_t *game) {
    printf("%s", address);
    printf("%s", port);
    if (address == NULL || port == NULL || strlen(address) <= 1 || strlen(port) <= 1) {
        return 0;
    }
    printf("Connecting to %s:%s...\n", address, port);
    game->client_sock = initClient(address, port, game);
    printf("initClient() finished\n");
    if (game->client_sock > 0) {
        return 1;
    }
    return 0;
}

int isServerRunning(game_t *game) {
    int ret;
    if( (ret = pthread_kill(game->server.server_thread, 0)) == 0)
    {
        printf("still running\n");
    }
    else
    {
        printf("RIP Thread = %d\n",ret);
    }
    return ret == 0;
}

int menuWindow(game_t *game) {
    int quit = 0;
    int counter = 0;
    int menu_size = 4;
    int update = 1;
    menu_t *menus = malloc(sizeof(menu_t) * 4);
    char *address = malloc(sizeof(char) * 15);
    char *port = malloc(sizeof(char) * 5);

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Rect text_pos;
    SDL_Event event;

    text_pos.y = 80;
    text_pos.x = 80;


    menus[0].text = strdup("Se connecter a une partie");
    menus[0].enabled = 1;
    menus[1].text = strdup("Heberger une partie");
    menus[1].enabled = game->server.started ? 0 : 1;
    menus[2].text = strdup("Local");
    menus[2].enabled = 1;
    menus[3].text = strdup("Quitter");
    menus[3].enabled = 1;

    showMenu(game, menus, menu_size, counter);
    do {
        SDL_RenderClear(game->sdl->renderer);

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
                            ask_for_ip(game->sdl->renderer, game->sdl->font, address);
                            SDL_RenderClear(game->sdl->renderer);
                            ask_for_ip(game->sdl->renderer, game->sdl->font, port);
                            if (joinGame(address, port, game)) {
                                if (waitingLobby(game)) {
                                    drawGame(game);
                                } else {
                                    quit = 1;
                                }
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
                                     disp_text(game->sdl->renderer, "Stopping server...", game->sdl->font, 80, 80);
                                     stopServer(game);
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
        } else if (event.type == SDL_QUIT)
            quit = 1;
        if (update) {
            showMenu(game, menus, menu_size, counter);
            update = 0;
        }
    } while (!quit);
    game->running = 0;
    for (int i = 0; i < menu_size; i++) {
        free(menus[i].text);
    }
    free(menus);
    free(port);
    free(address);
    return 1;
}

int hostGame(game_t *game) {
    printf("== Host Game ==\n");
    SDL_Color white = { 255, 255, 255, 255 };
    char *input_port = malloc(sizeof(char) * 5);
    char message[30];
    int retour = 1;

    SDL_Rect pos;
    pos.x = 80;
    pos.y = 80;
    SDL_RenderClear(game->sdl->renderer);
    SDL_RenderPresent(game->sdl->renderer);
    ask_for_port(game->sdl->renderer, game->sdl->font, input_port);
    printf("Port chosen is %s\n", input_port);
    int port = atoi(input_port);
    startServer(game, &port);

    SDL_Delay(60);
    if (!isServerRunning(game)) {
        showPromptMessage(game, "Server error", pos, white);
        retour = 0;
    } else if (!joinGame("127.0.0.1", input_port, game) || game->client_sock  <= 0) {
        sprintf(message, "Cannot connect to localhost:%s", input_port);
        showPromptMessage(game, message, pos, white);
        stopServer(game);
        retour = 0;
    }
    free(input_port);
    return retour;
}

int get_clients_number(int sock) {
    int players_number = 0;
    char query[4] = {'l','i','s','t'};
    send(sock, &query, sizeof(query), MSG_NOSIGNAL);
    recv(sock, &players_number, sizeof(players_number), 0);
    return players_number;
}

int waitingLobby(game_t *game)
{
    printf("== Waiting Lobby ==\n");
    SDL_Event event;
    unsigned int players = 4;
    unsigned int players_tmp = 0;
    int update = 1;

    char message[30];

    while (1) {
        players_tmp = get_clients_number(game->client_sock);
        if (players_tmp != players) {
            players = players_tmp;
            update = 1;
        }

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    return 0;
                case SDL_KEYDOWN:
                    if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) {
                        return 0;
                    } else if (event.key.keysym.scancode == SDL_SCANCODE_RETURN || event.key.keysym.scancode == SDL_SCANCODE_BACKSPACE) {
                        char query[4] = {'p','l','a','y'};
                        send(game->client_sock, &query, sizeof(query), MSG_NOSIGNAL);
                        return 1;
                    }
            }
        }
        if (players > MAX_PLAYERS) {
            return 1;
        }

        if (update) {
            SDL_RenderClear(game->sdl->renderer);
            disp_text(game->sdl->renderer, "Waiting for server to start...", game->sdl->font, 80, 80);
            sprintf(message, "%d/%d players", players, MAX_PLAYERS);
            disp_text(game->sdl->renderer, message, game->sdl->font, 80, 110);
            SDL_RenderPresent(game->sdl->renderer);
            update = 0;
        }

        usleep(1000);
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

void ask_for_port(SDL_Renderer *renderer, TTF_Font *font, char *port) {
    memset(port, ' ', 5);
    SDL_Event e;
    int position = 0;
    int ok = 0;
    while (!ok) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) {
                    if (position > 4) {
                        position = 4;
                    }
                    port[position] = e.key.keysym.sym;
                    position++;
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    position--;
                    if (position < 0) {
                        position = 0;
                    }
                    port[position] = ' ';
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    port[position] = 0;
                    ok = 1;
                }
            }
        }
        usleep(200);
        SDL_RenderClear(renderer);
        disp_text(renderer, "port", font, 240, 200);
        if (strlen(port)) {
            disp_text(renderer, port, font, 240, 230);
        }
        SDL_RenderPresent(renderer);
    }
}

void ask_for_ip(SDL_Renderer *renderer, TTF_Font *font, char *ip) {
    memset(ip, ' ', 15);
    SDL_Event e;
    int position = 0;
    int ok = 0;
    while (!ok) {
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                if ((e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) || e.key.keysym.sym == SDLK_PERIOD) {
                    if (position > 14) {
                        position = 14;
                    }
                    ip[position] = e.key.keysym.sym;
                    position++;
                }
                if (e.key.keysym.sym == SDLK_BACKSPACE) {
                    position--;
                    if (position < 0) {
                        position = 0;
                    }
                    ip[position] = ' ';
                }
                if (e.key.keysym.sym == SDLK_RETURN) {
                    ip[position] = 0;
                    ok = 1;
                }
            }
        }
        usleep(200);
        SDL_RenderClear(renderer);
        disp_text(renderer, "ip address", font, 240, 200);
        if (strlen(ip)) {
            disp_text(renderer, ip, font, 240, 230);
        }
        SDL_RenderPresent(renderer);
    }
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
