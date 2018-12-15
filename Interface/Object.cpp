//
// Created by cswu on 2018/12/16.
//

#include "Object.h"
#include "View.h"


    Object::Object(View* view, int x, int y, ALLEGRO_BITMAP *image_path){
        this->x = x;
        this->y = y;
        this->image_path = image_path;
        this->view = view;
    }

    void Object::plot() {
        al_draw_bitmap(image_path, x, y, 0);
    }

