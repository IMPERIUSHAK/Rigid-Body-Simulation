#include "body.h"

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

void CreateBody(struct Body *body, float x, float y){

    body->x      = x;
    body->y      = y;
    body->radius = 10;//временно
    body->mass   = 20;//временно
    body->xv     = 0;
    body->yv     = 0;
    body->isalive = true;
}

void UpdateBody(struct Body *body, float dt, int screen_height, int screen_width){

    body->yv += 9.86f * dt;
    body->y += body->yv * dt;
    body->x += body->xv * dt;

    if (body->y + body->radius >= screen_height) {
        body->y  = screen_height - body->radius;
        body->yv = -body->yv * 0.8f;  // 0.8 = упругость
    }
   
    if (body->x - body->radius <= 0) {
        body->x = body->radius;
        body->xv = -body->xv * 0.8f;
    }

    if (body->x + body->radius >= screen_width) {
        body->x = screen_width - body->radius;
        body->xv = -body->xv * 0.8f;
    }

}

void DrawBody(struct Body *body, SDL_Renderer *renderer){

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    DrawCircle(renderer, body->x, body->y, body->radius);

    SDL_RenderDrawPoint(renderer, (int)body->x, (int)body->y);

}



void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
    {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
    // Each of the following renders an octant of the circle
    SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
    SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
    SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

      if (error <= 0)
      {
      	++y;
      	error += ty;
      	ty += 2;
      }

      if (error > 0)
      {
      	--x;
      	tx += 2;
      	error += (tx - diameter);
      }

    }
}

bool CheckCollision(struct Body *a, struct Body *b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    float distance = sqrt(dx*dx + dy*dy);
    return distance < (a->radius + b->radius);
}

void ResolveCollision(struct Body *a, struct Body *b) {
    float dx = a->x - b->x;
    float dy = a->y - b->y;
    
    float distance = sqrt(dx*dx + dy*dy);
    float nx = dx / distance;
    float ny = dy / distance;
    
    float overlap = (a->radius + b->radius) - distance;
    
    a->x -= (overlap / 2) * nx;
    a->y -= (overlap / 2) * ny;
    b->x += (overlap / 2) * nx;
    b->y += (overlap / 2) * ny;
    
    float dvx = a->xv - b->xv;
    float dvy = a->yv - b->yv;
    float dot = dvx*nx + dvy*ny;

    if (dot > 0) return;

    float impulse = (2.0f * dot) / (1.0f/a->mass + 1.0f/b->mass);
    
    a->xv -= (impulse / a->mass) * nx;
    a->yv -= (impulse / a->mass) * ny;
    b->xv += (impulse / b->mass) * nx;
    b->yv += (impulse / b->mass) * ny;
}