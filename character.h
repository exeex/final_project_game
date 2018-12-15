//
// Created by cswu on 2018/12/15.
// picture from https://kenney.nl/assets/space-shooter-redux
//

#ifndef FINALPORJECT_CHARACTER_H
#define FINALPORJECT_CHARACTER_H

#include <allegro5/allegro.h>
#include "Interface.h"
#include "config.h"

//class character {
//
//};

//class ObjectInterface {
//
//public:
//    int x;
//    int y;
//    int move_speed_x = 0;
//    int move_speed_y = 0;
//    int move_acc_x = 0;
//    int move_acc_y = 0;
//    ALLEGRO_BITMAP *image_path;
//
//    ObjectInterface(int x, int y, ALLEGRO_BITMAP *image_path){
//        this->x = x;
//        this->y = y;
//        this->image_path = image_path;
//    }
//    void plot() {
//        al_draw_bitmap(image_path, x, y, 0);
//    }
//};

class Bullet : public ObjectInterface {

    void update_position() override{
        x += move_speed_x;
        y += move_speed_y;
        move_speed_x += move_acc_x;
        move_speed_y += move_acc_y;
    }

};


class BackGround : public ObjectInterface {

public:
    void update_position() override{
        x += move_speed_x;
        y += move_speed_y;
        move_speed_x += move_acc_x;
        move_speed_y += move_acc_y;
    }
    BackGround(int x, int y, ALLEGRO_BITMAP *image_path) : ObjectInterface(x ,y, image_path){}

};



class Character : public ObjectInterface {

public:
    uint8_t is_moving_left = 0;
    uint8_t is_moving_right = 0;
    uint8_t is_moving_up = 0;
    uint8_t is_moving_down = 0;

    int move_speed_x = 5;
    int move_speed_y = 5;

    Character() : ObjectInterface(0, 0, nullptr) {};

    Character(int x, int y, ALLEGRO_BITMAP *image_path) : ObjectInterface(x, y, image_path) {
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
    Player(int x, int y, ALLEGRO_BITMAP *image_path) : Character(x, y, image_path) {
        this->x = x;
        this->y = y;
        this->image_path = image_path;
    }
};

class Enemy : public Character{
public:

    bool dir = false;
    Enemy(int x, int y, ALLEGRO_BITMAP *image_path) : Character(x, y, image_path) {
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
