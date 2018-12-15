//
// Created by cswu on 2018/12/16.
//

#ifndef FINALPORJECT_OBJECT_H
#define FINALPORJECT_OBJECT_H

#include <allegro5/allegro.h>

class View;
class Object {

public:
    View* view;
    int x;
    int y;
    int move_speed_x = 0;
    int move_speed_y = 0;
    int move_acc_x = 0;
    int move_acc_y = 0;

    ALLEGRO_BITMAP *image_path;

    Object(View* view, int x, int y, ALLEGRO_BITMAP *image_path);
    virtual void plot();
    virtual void update_position() = 0;
};


#endif //FINALPORJECT_OBJECT_H
