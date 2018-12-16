//
// Created by cswu on 2018/12/15.
// picture from https://kenney.nl/assets/space-shooter-redux
//

#ifndef FINALPORJECT_CHARACTER_H
#define FINALPORJECT_CHARACTER_H

#include <allegro5/allegro.h>
#include <cstdio>
#include "../Interface/View.h"
#include "../Interface/Object.h"
#include "../config.h"


class Bullet : public Object {

public:
    Bullet(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) : Object(view, x, y, bitmap) {
        y_speed = -1;
    }

    ~Bullet() override {
//        fprintf(stdout, "unexpected msg: gg!! \n");
    }

    bool is_out_of_boundary(int x, int y, int w, int h) {

        if (x < -w || x > WIDTH || y < -h || y > HEIGHT) {


            return true;
        } else return false;

    }

    void plot() override{
        if (this->is_garbage) return;
        else al_draw_bitmap(bitmap, x-w/2, y, 0);
    }

    void update_position() override {
        x += x_speed;
        y += y_speed;
        x_speed += x_acc;
        y_speed += y_acc;

        if (is_out_of_boundary(x, y, w, h)) this->is_garbage = true;

    }
};


class BackGround : public Object {

public:
    void update_position() override {
        x += x_speed;
        y += y_speed;
    }

    BackGround(View *view, int x, int y, ALLEGRO_BITMAP *image_path) : Object(view, x, y, image_path) {}

    ~BackGround() override = default;
};


class Character : public Object {

public:
    uint8_t is_moving_left = 0;
    uint8_t is_moving_right = 0;
    uint8_t is_moving_up = 0;
    uint8_t is_moving_down = 0;

    int x_speed = 5;
    int y_speed = 5;

    Character(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) : Object(view, x, y, bitmap) {
        this->x = x;
        this->y = y;
        this->bitmap = bitmap;
    }

    ~Character() override = default;

    void plot() override{
        if (this->is_garbage) return;
        else al_draw_bitmap(bitmap, x-w/2, y-w/2, 0);
    }

    void update_position() override {
        x += x_speed * (-1 * is_moving_left + is_moving_right);
        y += y_speed * (-1 * is_moving_up + is_moving_down);
    }

    virtual void hit(Bullet *) {
    }


};


class Player : public Character {
public:
    ALLEGRO_BITMAP *bullet_img;
    int bullet_img_w;
    int bullet_img_h;
    uint8_t is_firing;
    ALLEGRO_TIMER *fire_timer;

    Player(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) : Character(view, x, y, bitmap) {
        this->x = x;
        this->y = y;
        this->bitmap = bitmap;
        bullet_img = al_load_bitmap("laserBlue01.png");
        bullet_img_w = al_get_bitmap_width(bullet_img);
        bullet_img_h = al_get_bitmap_height(bullet_img);
        is_firing = 0;
        fire_timer = al_create_timer(1.0 / 20.0);
    }
//    void bind_event_queue(ALLEGRO_EVENT_QUEUE* event_queue){
//        al_register_event_source(event_queue, al_get_timer_event_source(fire_timer));
//    }

    ~Player() override = default;

    void fire() {
        int fire_pos_x = x;
        int fire_pos_y = y - bullet_img_h / 2;

        auto b = new Bullet(this->view, fire_pos_x, fire_pos_y, bullet_img);
        view->add_bullet(b);
    }


};

class Enemy : public Character {
public:

    bool dir = false;

    Enemy(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) : Character(view, x, y, bitmap) {
        this->x = x;
        this->y = y;
        this->collision_radius = 20.0;
        this->bitmap = bitmap;
        x_speed = 0;
        y_speed = 0;
    }

    void update_position() override {
        if (x < -150) dir = false;
        else if (x > WIDTH + 50) dir = true;
        if (dir) x -= x_speed;
        else x += x_speed;

    }

    void hit(Bullet* b) override{
//        this->is_garbage = true ;
        printf("hit!");
        b->is_garbage = true ;
    }


    ~Enemy() override = default;

};


#endif //FINALPORJECT_CHARACTER_H
