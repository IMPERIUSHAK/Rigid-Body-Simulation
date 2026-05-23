#include "window.h"
#include <stdio.h>
#include <stdbool.h>
#include  "body.h"

#define MAX_BODY 1000

int main(void){

    struct InitWindow wind = {.SCREEN_HEIGHT = 600, .SCREEN_WIDTH = 800};

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    CreateWindow(&wind);

    SDL_SetRenderDrawBlendMode(wind.renderer, SDL_BLENDMODE_BLEND);
    SDL_Event event;

    struct Body body[MAX_BODY];
    memset(body, 0, sizeof(body));
    
    while (true){
        
        while(SDL_PollEvent(&event)){

            if ( event.type == SDL_QUIT  || event.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                return 0;
            
            }else if (event.type == SDL_MOUSEBUTTONDOWN){

                for (int i = 0; i < MAX_BODY; i++){
                    if (!body[i].isalive){
                        CreateBody(&body[i], event.button.x, event.button.y);
                        break;
                    }
                }

            }

        }

        
        // int mx, my;
        // Uint32 buttons  = SDL_GetMouseState(&mx, &my);
        // if (buttons){

        //     for (int i = 0; i < MAX_BODY; i++){
        //         if (!body[i].isalive){
        //             CreateBody(&body[i], mx, my);
        //             break;
        //         }   
        //     }

        // }

        SDL_SetRenderDrawColor(wind.renderer, 0, 0, 0, 255);
        SDL_RenderClear(wind.renderer);


        for (int i = 0; i < MAX_BODY; i++){

            if (body[i].isalive){    
                UpdateBody(&body[i], 0.016f, wind.SCREEN_HEIGHT, wind.SCREEN_WIDTH);
            }

        }

        for (int i = 0; i < MAX_BODY; i++){
            for (int j = i+1; j < MAX_BODY; j++){
                if (body[i].isalive && body[j].isalive){
                    if (CheckCollision(&body[i], &body[j])){
                       ResolveCollision(&body[i], &body[j]);
                    }
                }
            }
        }


        for (int i = 0; i < MAX_BODY; i++){

            if (body[i].isalive){    
               DrawBody(&body[i], wind.renderer);
            }

        }

        SDL_RenderPresent(wind.renderer);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(wind.renderer);
    SDL_DestroyWindow(wind.window);
    SDL_Quit();
}   