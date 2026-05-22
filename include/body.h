#include <stdio.h>

struct Body {

    float x, y;
    float xv, yv;
    float mass;
    float radius;

};

void CreateBody(struct Body *body, float x, float y);
