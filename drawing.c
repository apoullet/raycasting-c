#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "sim.h"

void draw_entity(entity e, int isSource, ALLEGRO_COLOR color) {
        if (isSource) {
                al_draw_filled_circle(e.pos.x, e.pos.y, e.size, color);
        } else {
                al_draw_filled_rectangle(e.pos.x, e.pos.y, e.pos.x+e.size, e.pos.y+e.size, color);
        }
}

void draw_ray(line ray, ALLEGRO_COLOR color) {
        al_draw_line(ray.source.x, ray.source.y, ray.destination.x, ray.destination.y, color, 1);
}
