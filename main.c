#include <stdio.h>
#include <math.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "sim.h"

int main() {
        ALLEGRO_DISPLAY * display = NULL;

        if (!al_init()) {
                fprintf(stderr, "Failed to initialise Allegro!\n");
                return -1;
        }

        const int WIDTH = 750, HEIGHT = 750;
        const int NUMTILES = 25;
        const int SIZE = WIDTH / NUMTILES;

        display = al_create_display(WIDTH, HEIGHT);

        if (!display) {
                fprintf(stderr, "Failed to create display!\n");
                return -1;
        }

        al_init_primitives_addon();
        al_install_mouse();

        ALLEGRO_EVENT_QUEUE * event_queue = al_create_event_queue();

        ALLEGRO_TIMER * timer = al_create_timer(1.0 / 60);

        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_mouse_event_source());

        al_hide_mouse_cursor(display);

        ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
        ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);

        int done = 0, redraw = 1;

        entity source = { .pos.x = 13 * SIZE - SIZE / 2, .pos.y = 13 * SIZE - SIZE / 2, .size = SIZE / 2 };

        const int NUMRAYS = 36;
        const float ANGLE = 2 * M_PI;
        const float ANGLE_INC = ANGLE / NUMRAYS;

        line rays[NUMRAYS];

        al_start_timer(timer);

        draw_entity(source, 1, white);

        al_flip_display();

        while (!done) {
                ALLEGRO_EVENT ev;

                al_wait_for_event(event_queue, &ev);

                switch(ev.type) {
                        case ALLEGRO_EVENT_DISPLAY_CLOSE:
                                done = 1;
                                break;

                        case ALLEGRO_EVENT_MOUSE_AXES:
                                move_entity(&source, ev.mouse.x, ev.mouse.y);
                                break;

                        case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
                                move_entity(&source, ev.mouse.x, ev.mouse.y);
                                break;

                        case ALLEGRO_EVENT_TIMER:
                                redraw = 1;

                                int index = 0;

                                for (float i = 0; i < ANGLE; i += ANGLE_INC)
                                        rays[index++] = cast_ray(source, i, WIDTH);

                                break;
                }

                if (redraw && al_is_event_queue_empty(event_queue)) {
                        redraw = 0;

                        al_clear_to_color(black);

                        draw_entity(source, 1, white);

                        for (int i = 0; i < NUMRAYS; i++)
                                draw_ray(rays[i], white);

                        al_flip_display();
                }
        }

        al_destroy_display(display);
        al_destroy_event_queue(event_queue);
        al_destroy_timer(timer);

        return 0;
}
