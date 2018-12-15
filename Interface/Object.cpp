//
// Created by cswu on 2018/12/16.
//

#include "Object.h"
#include "View.h"


    Object::Object(View* view, int x, int y, ALLEGRO_BITMAP *bitmap){
        this->x = x;
        this->y = y;
        w = al_get_bitmap_width(bitmap);
        h = al_get_bitmap_height(bitmap);
        this->bitmap = bitmap;
        this->view = view;
    }

    void Object::plot() {
        al_draw_bitmap(bitmap, x, y, 0);
    }

    void Object::update_position() {
    x += x_speed;
    y += y_speed;
    x_speed += x_acc;
    y+=y_acc;

}