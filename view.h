//
// Created by cswu on 2018/12/15.
//

#ifndef FINALPORJECT_VIEW_H
#define FINALPORJECT_VIEW_H

#include "character.h"

class View {

    public:
        Character *player;
        Character *enemy;
        BackGround *backGround;

        View(){
            return ;
        }

        void plot(){
            player->plot();
            enemy->plot();
        }

};


#endif //FINALPORJECT_VIEW_H
