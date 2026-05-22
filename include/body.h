#include <stdio.h>
#include <SDL2/SDL.h>
struct Body {

    float x, y;
    float xv, yv;
    float mass;
    float radius;

};

void CreateBody(struct Body *body, float x, float y);

void UpdateBody(struct Body * body, float dt);

void DrawBody(struct Body *body, SDL_Renderer *renderer);