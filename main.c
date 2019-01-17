#include "headers/main.h"

int main() {
    system_manager_t system_manager;

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stdout, SDL_GetError());
        return -1;
    }

    /* Création de la fenêtre */
    SDL_Window *pWindow = NULL;
    pWindow = SDL_CreateWindow("Bomberman", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               640,
                               480,
                               SDL_WINDOW_SHOWN);

    if (pWindow != NULL) {
        system_manager.running = 1;
    } else {
        system_manager.running = 0;
    }
    while(system_manager.running) {
        inputManager(&system_manager);
        //renderManager(&system_manager);
    }
    SDL_Quit();
    return 0;
}

void inputManager(system_manager_t *manager) {
    while (SDL_PollEvent(&manager->events)) {
        switch (manager->events.type) {
            case SDL_QUIT:
                manager->running = 0;
                break;
        }
    }
}
