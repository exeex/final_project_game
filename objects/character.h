//
// Created by cswu on 2018/12/15.
// picture from https://kenney.nl/assets/space-shooter-redux
//

#ifndef FINALPORJECT_CHARACTER_H
#define FINALPORJECT_CHARACTER_H

#include <allegro5/allegro.h>
#include "../Interface/View.h"
#include "../Interface/Object.h"
#include "../config.h"



class Bullet : public Object {

public:
    Bullet(View* view, int x, int y, ALLEGRO_BITMAP *image_path): Object(view, x ,y, image_path){
        move_speed_y = -30;
    }

    void update_position() override{
        x += move_speed_x;
        y += move_speed_y;
        move_speed_x += move_acc_x;
        move_speed_y += move_acc_y;
    }

};


class BackGround : public Object {

public:
    void update_position() override{
        x += move_speed_x;
        y += move_speed_y;
        move_speed_x += move_acc_x;
        move_speed_y += move_acc_y;
    }
    BackGround(View* view, int x, int y, ALLEGRO_BITMAP *image_path) : Object(view, x ,y, image_path){}

};



class Character : public Object {

public:
    uint8_t is_moving_left = 0;
    uint8_t is_moving_right = 0;
    uint8_t is_moving_up = 0;
    uint8_t is_moving_down = 0;

    int move_speed_x = 5;
    int move_speed_y = 5;

    Character(View* view, int x, int y, ALLEGRO_BITMAP *image_path) : Object(view, x, y, image_path) {
        this->x = x;
        this->y = y;
        this->image_path = image_path;
    }

    void update_position() override{
        x += move_speed_x * (-1 * is_moving_left + is_moving_right);
        y += move_speed_y * (-1 * is_moving_up + is_moving_down);
    }



};


class Player : public Character{
public:
    ALLEGRO_BITMAP* bullet_img;
    Player(View* view, int x, int y, ALLEGRO_BITMAP *image_path) : Character(view, x, y, image_path) {
        this->x = x;
        this->y = y;
        this->image_path = image_path;
        bullet_img = al_load_bitmap("laserBlue01.png");
    }

    void fire(){
        auto b = new Bullet(this->view,x,y, bullet_img);
        view->add_bullet(b);
    }
};

class Enemy : public Character{
public:

    bool dir = false;
    Enemy(View* view, int x, int y, ALLEGRO_BITMAP *image_path) : Character(view, x, y, image_path) {
        this->x = x;
        this->y = y;
        this->image_path = image_path;
    }

    void update_position() override{
        if (x < -150) dir = false;
        else if (x > WIDTH + 50) dir = true;

        if (dir) x -= 10;
        else x += 10;

    }

};


#endif //FINALPORJECT_CHARACTER_H
