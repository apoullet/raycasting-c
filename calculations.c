#include <math.h>
#include "sim.h"

void move_entity(entity * e, int x, int y) {
        e->pos.x = x;
        e->pos.y = y;
}

line cast_ray(entity e, float angle, const int WIDTH) {
        vec2d start = { .x = e.pos.x, .y = e.pos.y };

        float cotan = cos(angle) / sin(angle);

        float constant = start.y - cotan * start.x;

        vec2d end;

        end.x = (angle > 4.71239 || angle <= 1.5708) ? WIDTH : 0;
        end.y = cotan * end.x + constant;

        line ray = { .source = start, .destination = end };

        return ray;
}
