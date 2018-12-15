#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "character.h"
#include "view.h"
#include "config.h"

#define GAME_TERMINATE -1

// ALLEGRO Variables
ALLEGRO_DISPLAY *display = nullptr;
ALLEGRO_EVENT_QUEUE *event_queue = nullptr;
ALLEGRO_BITMAP *image = nullptr;
ALLEGRO_BITMAP *image2 = nullptr;
ALLEGRO_BITMAP *image3 = nullptr;
ALLEGRO_BITMAP *background = nullptr;
ALLEGRO_KEYBOARD_STATE keyState;
ALLEGRO_TIMER *timer = nullptr;
ALLEGRO_TIMER *timer2 = nullptr;
ALLEGRO_TIMER *timer3 = nullptr;
ALLEGRO_SAMPLE *song = nullptr;
ALLEGRO_FONT *font = nullptr;

//Custom Definition
const char *title = "Final Project 106065703";


View view;
Character *player;


int window = 1;
bool judge_next_window = false;

void show_err_msg(int msg);

void game_init();

void game_begin();

int process_event();

int game_run();

void game_destroy();

int main(int argc, char *argv[]) {
    int msg = 0;

    game_init();
    game_begin();

    while (msg != GAME_TERMINATE) {
        msg = game_run();
        if (msg == GAME_TERMINATE)
            printf("Game Over\n");
    }

    game_destroy();
    return 0;
}

void show_err_msg(int msg) {
    fprintf(stderr, "unexpected msg: %d\n", msg);
    game_destroy();
    exit(9);
}

void game_init() {
    if (!al_init()) {
        show_err_msg(-1);
    }
    if (!al_install_audio()) {
        fprintf(stderr, "failed to initialize audio!\n");
        show_err_msg(-1);
    }
    if (!al_init_acodec_addon()) {
        fprintf(stderr, "failed to initialize audio codecs!\n");
        show_err_msg(-1);
    }
    if (!al_reserve_samples(1)) {
        fprintf(stderr, "failed to reserve samples!\n");
        show_err_msg(-1);
    }
    // Create display
    display = al_create_display(WIDTH, HEIGHT);
    event_queue = al_create_event_queue();
    if (display == nullptr || event_queue == nullptr) {
        show_err_msg(-1);
    }
    // Initialize Allegro settings
    al_set_window_position(display, 200, 200);
    al_set_window_title(display, title);
    al_init_primitives_addon();
    al_install_keyboard();
    al_install_audio();
    al_init_image_addon();
    al_init_acodec_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Register event
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
}

void game_begin() {
    // Load sound
    song = al_load_sample("hello.wav");
    if (!song) {
        printf("Audio clip sample not loaded!\n");
        show_err_msg(-1);
    }
    // Loop the song until the display closes
    al_play_sample(song, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, nullptr);
    al_clear_to_color(al_map_rgb(100, 100, 100));
    // Load and draw text
    font = al_load_ttf_font("pirulen.ttf", 12, 0);
    al_draw_text(font, al_map_rgb(255, 255, 255), WIDTH / 2, HEIGHT / 2 + 220, ALLEGRO_ALIGN_CENTRE,
                 "Press 'Enter' to start");
    al_draw_rectangle(WIDTH / 2 - 150, 510, WIDTH / 2 + 150, 550, al_map_rgb(255, 255, 255), 0);
    al_flip_display();
}

int process_event() {
    // Request the event
    ALLEGRO_EVENT event;
    al_wait_for_event(event_queue, &event);

    // Our setting for controlling animation
    if (event.timer.source == timer) {

        view.update_position();
//        player->update_position();

    }


    // Keyboard
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            // Control
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                player->is_moving_up = 1;
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                player->is_moving_down = 1;
                break;
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                player->is_moving_left = 1;
                break;
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D:
                player->is_moving_right = 1;
                break;

                // For Start Menu
            case ALLEGRO_KEY_ENTER:
                judge_next_window = true;
                break;
            default:
                break;
        }
    }

    if (event.type == ALLEGRO_EVENT_KEY_UP) {
        switch (event.keyboard.keycode) {
            // Control
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_W:
                player->is_moving_up = 0;
                break;
            case ALLEGRO_KEY_DOWN:
            case ALLEGRO_KEY_S:
                player->is_moving_down = 0;
                break;
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_A:
                player->is_moving_left = 0;
                break;
            case ALLEGRO_KEY_RIGHT:
            case ALLEGRO_KEY_D:
                player->is_moving_right = 0;
                break;
            default:
                break;

        }
    }

        // Shutdown our program
    else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
        return GAME_TERMINATE;

    return 0;
}

int game_run() {
    int error = 0;
    // First window(Menu)
    if (window == 1) {
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
            if (judge_next_window) {
                window = 2;
                // Setting Character
                view.backGround = new BackGround(0, 0, al_load_bitmap("stage.jpg"));
                player = new Player(WIDTH / 2, HEIGHT / 2 + 150, al_load_bitmap("playerShip1_blue.png"));
                view.players.push_back(player);
                view.enemys.push_back(new Enemy(WIDTH / 2, HEIGHT / 2 - 280, al_load_bitmap("enemyRed3.png")));

                //Initialize Timer
                timer = al_create_timer(1.0 / 30.0);
                timer2 = al_create_timer(1.0);
                timer3 = al_create_timer(1.0 / 10.0);
                al_register_event_source(event_queue, al_get_timer_event_source(timer));
                al_register_event_source(event_queue, al_get_timer_event_source(timer2));
                al_register_event_source(event_queue, al_get_timer_event_source(timer3));
                al_start_timer(timer);
                al_start_timer(timer2);
                al_start_timer(timer3);
            }
        }
    }
        // Second window(Main Game)
    else if (window == 2) {
        // Change Image for animation
//        view.backGround->plot();
        view.plot();

        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // Listening for new event
        if (!al_is_event_queue_empty(event_queue)) {
            error = process_event();
        }
    }
    return error;
}

void game_destroy() {
    // Make sure you destroy all things
    al_destroy_event_queue(event_queue);
    al_destroy_display(display);
    al_destroy_timer(timer);
    al_destroy_timer(timer2);
    al_destroy_bitmap(image);
    al_destroy_sample(song);
}
