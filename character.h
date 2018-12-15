//
// Created by cswu on 2018/12/15.
//

#ifndef FINALPORJECT_CHARACTER_H
#define FINALPORJECT_CHARACTER_H

#include <allegro5/allegro.h>

//class character {
//
//};

class Object{

    public:
        int x;
        int y;
        int move_speed_x = 0;
        int move_speed_y = 0;
        int move_acc_x = 0;
        int move_acc_y = 0;
        ALLEGRO_BITMAP *image_path;

        Object(int x, int y, ALLEGRO_BITMAP *image_path){
            this->x = x;
            this->y = y;
            this->image_path = image_path;
    }
};

class Bullet : public Object{

    void update_position(){
        x+=move_speed_x;
        y+=move_speed_y;
        move_speed_x += move_acc_x;
        move_speed_y += move_acc_y;
    }

};


class Character : public Object{


    public:
        uint8_t is_moving_left=0;
        uint8_t is_moving_right=0;
        uint8_t is_moving_up=0;
        uint8_t is_moving_down=0;

        int move_speed_x = 5;
        int move_speed_y = 5;

        Character() : Object(0 ,0, nullptr){};

        Character(int x, int y, ALLEGRO_BITMAP *image_path) : Object(x ,y, image_path){
            this->x = x;
            this->y = y;
            this->image_path = image_path;
        }

    void update_position(){
        x+=move_speed_x*(-1*is_moving_left+is_moving_right);
        y+=move_speed_y*(-1*is_moving_up+is_moving_down);
    }

};



#endif //FINALPORJECT_CHARACTER_H
