//
// Created by cswu on 2018/12/15.
//

#include "View.h"
#include "Object.h"


void View::plot() {
    backGround->plot();
    for(int i=0; i<players.size(); i++) players[i]->plot();
    for(int i=0; i<enemys.size(); i++) enemys[i]->plot();
    for(int i=0; i<bullets.size(); i++) bullets[i]->plot();
}

void View::update_position(){
    backGround->update_position();
    for(int i=0; i<players.size(); i++) players[i]->update_position();
    for(int i=0; i<enemys.size(); i++) enemys[i]->update_position();
    for(int i=0; i<bullets.size(); i++) bullets[i]->update_position();
}

void View::add_bullet(Object* bullet){
    bullets.push_back(bullet);
}