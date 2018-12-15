//
// Created by cswu on 2018/12/15.
//

#ifndef FINALPORJECT_VIEW_H
#define FINALPORJECT_VIEW_H

#include <vector>

class Object;

class View{

public:
    Object* backGround;
    std::vector<Object*> players;
    std::vector<Object*> enemys;
    std::vector<Object*> bullets;

    void plot();
    void update_position();
    void add_bullet(Object* bullet);

};


#endif //FINALPORJECT_VIEW_H
