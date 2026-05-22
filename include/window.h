#include <SDL2/SDL.h>

#define WINDOW_TITLE "Rigid body simulation"

struct InitWindow{
    
    SDL_Window *window;
    SDL_Renderer *renderer;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
};

void CreateWindow(struct InitWindow *window);