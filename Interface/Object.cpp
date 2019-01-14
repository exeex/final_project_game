//
// Created by cswu on 2018/12/16.
//

#include "Object.h"
#include "View.h"


Object::Object(View *view, int x, int y, ALLEGRO_BITMAP *bitmap) {
    this->x = x;
    this->y = y;
    if(bitmap){
        w = al_get_bitmap_width(bitmap);
        h = al_get_bitmap_height(bitmap);
    } else{
        this->w=0;
        this->h=0;
    }
    this->bitmap = bitmap;
    this->view = view;
}

Object::~Object() {
}

void Object::plot() {
    if (this->is_garbage) return;
    else al_draw_bitmap(bitmap, x, y, 0);
}



void Object::update_position() {
    x += x_speed;
    y += y_speed;
    x_speed += x_acc;
    y += y_acc;

}