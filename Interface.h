//
// Created by cswu on 2018/12/15.
//

#ifndef FINALPORJECT_INTERFACE_H
#define FINALPORJECT_INTERFACE_H

#include <allegro5/allegro.h>
#include <vector>

class ObjectInterface {

public:
    int x;
    int y;
    int move_speed_x = 0;
    int move_speed_y = 0;
    int move_acc_x = 0;
    int move_acc_y = 0;

    ALLEGRO_BITMAP *image_path;

    ObjectInterface(int x, int y, ALLEGRO_BITMAP *image_path){
        this->x = x;
        this->y = y;
        this->image_path = image_path;
    }
    virtual void plot() {
        al_draw_bitmap(image_path, x, y, 0);
    }

    virtual void update_position() = 0;
};

class ViewInterface{

public:
    ObjectInterface* backGround;
    std::vector<ObjectInterface*> players;
    std::vector<ObjectInterface*> enemys;
    std::vector<ObjectInterface*> bullets;

    void plot() {
        backGround->plot();
        for(int i=0; i<players.size(); i++) players[i]->plot();
        for(int i=0; i<players.size(); i++) enemys[i]->plot();
//        for(int i=0; i<players.size(); i++) bullets[i]->plot();
    }

    void update_position(){
        backGround->update_position();
        for(int i=0; i<players.size(); i++) players[i]->update_position();
        for(int i=0; i<players.size(); i++) enemys[i]->update_position();
//        for(int i=0; i<players.size(); i++) bullets[i]->update_position();
    }

};





#endif //FINALPORJECT_INTERFACE_H

