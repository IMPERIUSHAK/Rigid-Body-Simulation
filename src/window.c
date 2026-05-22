#include "window.h"

void CreateWindow(struct InitWindow *window){
    
    window->window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, window->SCREEN_WIDTH, window->SCREEN_HEIGHT, 0);
    
    
    if (!window->window) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return;
    }

    window->renderer = SDL_CreateRenderer(window->window, -1, 0);

    if (!window->renderer) {
        fprintf(stderr, "Error: %s\n", SDL_GetError());
        return;
    }
}