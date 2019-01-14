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
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    int x_speed = 0;
    int y_speed = 0;
    int x_acc = 0;
    int y_acc = 0;
    float collision_radius =0;
    bool is_garbage = false;

    ALLEGRO_BITMAP *bitmap;

    Object(View* view, int x, int y, ALLEGRO_BITMAP *bitmap);
    virtual void plot();
    virtual void update_position() = 0;
    virtual ~Object();
};


#endif //FINALPORJECT_OBJECT_H
