#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

struct Body {

    float x, y;
    float xv, yv;
    float mass;
    float radius;
    bool isalive;

};

void CreateBody(struct Body *body, float x, float y);

void UpdateBody(struct Body * body, float dt, int screen_height, int screen_width);

void DrawBody(struct Body *body, SDL_Renderer *renderer);

bool CheckCollision(struct Body *a, struct Body *b);

void ResolveCollision(struct Body *a, struct Body *b);