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

    int hp = 10;
    int damage = 10;

    Bullet(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) : Object(view, x, y, bitmap) {
        y_speed = -20;
    }

    ~Bullet() override {
//        al_destroy_bitmap(bitmap);
//        fprintf(stdout, "unexpected msg: gg!! \n");
    }

    bool is_out_of_boundary(int x, int y, int w, int h) {

        if (x < -w || x > SCREEN_WIDTH || y < -h || y > SCREEN_HEIGHT) {


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

        if (this->is_out_of_boundary(x, y, w, h)) this->is_garbage = true;

    }
};


class BackGround : public Object {

public:

    void update_position() override {
        x += x_speed;
        y += y_speed;
    }

    BackGround(View *view, int x, int y, ALLEGRO_BITMAP *image_path) : Object(view, x, y, image_path) {

        y_speed = 1;
    }

    ~BackGround() override = default;


    void plot() override {

        al_draw_bitmap(bitmap, x, y%SCREEN_HEIGHT-h, 0);
        al_draw_bitmap(bitmap, x, y%SCREEN_HEIGHT, 0);
    }
};


class Character : public Object {

public:
    uint8_t is_moving_left = 0;
    uint8_t is_moving_right = 0;
    uint8_t is_moving_up = 0;
    uint8_t is_moving_down = 0;

    int hp = 100;
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
        else {
            al_draw_bitmap(bitmap, x-w/2, y-w/2, 0);
        }
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
    int hp = 100;
    int upgrade_cost =50;
    int level =0;
    float fire_speed = 20.0;
    uint64_t fire_count =0;
    uint8_t is_firing;
    ALLEGRO_TIMER *fire_timer;

    Player(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) : Character(view, x, y, bitmap) {
        this->x = x;
        this->y = y;
        this->bitmap = bitmap;
        this->collision_radius = 45.0;
        bullet_img = al_load_bitmap("img/bullet/laserBlue01.png");
        bullet_img_w = al_get_bitmap_width(bullet_img);
        bullet_img_h = al_get_bitmap_height(bullet_img);
        is_firing = 0;
        fire_timer = al_create_timer(1.0 / fire_speed);
        view->player_hp = hp;
    }
//    void bind_event_queue(ALLEGRO_EVENT_QUEUE* event_queue){
//        al_register_event_source(event_queue, al_get_timer_event_source(fire_timer));
//    }

    ~Player() override = default;

    void upgrade(){
        if(view->player_coin >= upgrade_cost){
            view->player_coin -= upgrade_cost;
            level++;
            this->x_speed+=1;
            this->y_speed+=1;
            view->player_level = level;

        } else{
            printf("insufficient coin!\n");
        }
    }

    void fire() {
        int fire_pos_x = x;
        int fire_pos_y = y - bullet_img_h / 2;

        auto b = new Bullet(this->view, fire_pos_x, fire_pos_y, bullet_img);
        view->add_bullet(b);

        if(level>=1 && fire_count%3 ==0){
            auto b2 = new Bullet(this->view, fire_pos_x, fire_pos_y, bullet_img);
            auto b3 = new Bullet(this->view, fire_pos_x, fire_pos_y, bullet_img);
            b2->x_speed = 2;
            b3->x_speed = -2;
            view->add_bullet(b2);
            view->add_bullet(b3);
        }

        if(level>=2 && fire_count%2 ==0){
            auto b2 = new Bullet(this->view, fire_pos_x, fire_pos_y, bullet_img);
            auto b3 = new Bullet(this->view, fire_pos_x, fire_pos_y, bullet_img);
            b2->x_speed = 2;
            b3->x_speed = -2;
            view->add_bullet(b2);
            view->add_bullet(b3);
        }

        fire_count++;

        if(fire_count>10000){
            fire_count =0;
        }


    }


    void hit(Bullet* b) override{
        printf("hit!");
        hp -= b->damage;
        b->is_garbage = true ;
        view->player_hp = hp;
        if(hp<=0) this->is_garbage = true;
    }



};

class Enemy : public Character {
public:
    int hp = 300;
    bool dir = false;
    ALLEGRO_BITMAP *bullet_img;
    int bullet_img_w;
    int bullet_img_h;
    int score = 1000;
    int coin = 100;

    Enemy(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) : Character(view, x, y, bitmap) {

        this->x = x;
        this->y = y;
        this->collision_radius = 45.0;
        this->bitmap = bitmap;
        x_speed = 3;
        y_speed = 0;

        bullet_img = al_load_bitmap("img/bullet/bullet.png");
        bullet_img_w = al_get_bitmap_width(bullet_img);
        bullet_img_h = al_get_bitmap_height(bullet_img);
    }

    void update_position() override {
        if (x < -150) dir = false;
        else if (x > SCREEN_WIDTH + 50) dir = true;
        if (dir) x -= x_speed;
        else x += x_speed;
        if(view->plot_count % 60==0) fire();

    }

    void fire() {
        int fire_pos_x = x;
        int fire_pos_y = y - bullet_img_h / 2;
        auto b = new Bullet(this->view, fire_pos_x, fire_pos_y, bullet_img);
        b->y_speed = 5;
        view->add_enemy_bullets(b);
    }

    void hit(Bullet* b) override{
        printf("hit!");
        hp -= b->damage;
        b->is_garbage = true ;
        if(hp<=0) this->defeated();
    }

    void defeated(){
        this->is_garbage = true;
        view->player_coin += coin;
        view->player_score += score;
    }

    ~Enemy() override = default;

};


#endif //FINALPORJECT_CHARACTER_H
