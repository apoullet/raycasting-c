#include <allegro5/allegro.h>

typedef struct {
        int x, y;
} vec2d;

typedef struct {
        vec2d pos;
        float size;
} entity;

typedef struct {
        vec2d source;
        vec2d destination;
} line;

void move_entity(entity * e, int x, int y);
line cast_ray(entity e, float angle, const int WIDTH);

void draw_entity(entity e, int isSource, ALLEGRO_COLOR color);
void draw_ray(line ray, ALLEGRO_COLOR color);
