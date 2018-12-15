//
// Created by cswu on 2018/12/15.
//

#ifndef FINALPORJECT_CHARACTER_H
#define FINALPORJECT_CHARACTER_H

#include <allegro5/allegro.h>

//class character {
//
//};

typedef struct
{
    int x;
    int y;
    int move_speed = 5;
    bool is_moving_left=false;
    bool is_moving_right=false;
    bool is_moving_up=false;
    bool is_moving_down=false;
    ALLEGRO_BITMAP *image_path;

}Character;


#endif //FINALPORJECT_CHARACTER_H
