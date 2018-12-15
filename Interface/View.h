//
// Created by cswu on 2018/12/15.
//

#ifndef FINALPORJECT_VIEW_H
#define FINALPORJECT_VIEW_H

#include <vector>
#include <list>

class Object;

class View{

public:
    Object* backGround;
    std::list<Object*> players;
    std::list<Object*> enemys;
    std::list<Object*> bullets;

    void plot();
    void update_position();
    void collect_garbage();
    void add_bullet(Object* bullet);

};


#endif //FINALPORJECT_VIEW_H
