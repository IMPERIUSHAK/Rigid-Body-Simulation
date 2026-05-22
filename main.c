#include "window.h"
#include <stdio.h>
#include <stdbool.h>

int main(void){

    struct InitWindow wind = {.SCREEN_HEIGHT = 600, .SCREEN_WIDTH = 800};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    CreateWindow(&wind);

    SDL_SetRenderDrawBlendMode(wind.renderer, SDL_BLENDMODE_BLEND);
    SDL_Event event;

    while (true){
        
        while(SDL_PollEvent(&event)){

            if ( event.type == SDL_QUIT ){
                return 0;
            }

        }

        SDL_SetRenderDrawColor(wind.renderer, 0, 0, 0, 255);
        SDL_RenderClear(wind.renderer);
        SDL_RenderPresent(wind.renderer);

    }

    SDL_DestroyRenderer(wind.renderer);
    SDL_DestroyWindow(wind.window);
    SDL_Quit();
}   