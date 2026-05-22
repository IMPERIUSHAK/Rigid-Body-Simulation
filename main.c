#include "window.h"
#include <stdio.h>
#include <stdbool.h>
#include  "body.h"

int main(void){

    struct InitWindow wind = {.SCREEN_HEIGHT = 600, .SCREEN_WIDTH = 800};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    CreateWindow(&wind);

    SDL_SetRenderDrawBlendMode(wind.renderer, SDL_BLENDMODE_BLEND);
    SDL_Event event;

    struct Body body;

    while (true){
        
        while(SDL_PollEvent(&event)){

            if ( event.type == SDL_QUIT ){
                return 0;
            }

        }

        
        int mx, my;
        Uint32 buttons  = SDL_GetMouseState(&mx, &my);
        if (buttons){
            CreateBody(&body, mx, my);
        }


        SDL_SetRenderDrawColor(wind.renderer, 0, 0, 0, 255);
        SDL_RenderClear(wind.renderer);

        if ( body.y <= wind.SCREEN_HEIGHT){
            UpdateBody(&body, 0.016f);
        }else {
            body.xv = 0;
            body.yv = 0;
        }

        DrawBody(&body, wind.renderer);

        SDL_RenderPresent(wind.renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(wind.renderer);
    SDL_DestroyWindow(wind.window);
    SDL_Quit();
}   