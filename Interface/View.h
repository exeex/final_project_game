//
// Created by cswu on 2018/12/15.
//

#ifndef FINALPORJECT_VIEW_H
#define FINALPORJECT_VIEW_H

#include <vector>
#include <list>

class Object;

class View{
private:
    long plot_count =0;

public:
    Object* backGround;
    Object* hud;
    std::list<Object*> players;
    std::list<Object*> enemys;
    std::list<Object*> bullets;
    std::list<Object*> enemy_bullets;

    int player_hp;
    int player_score =0;
    int player_coin =0;

    void plot();
    void update_position();
    void collect_garbage();
    void add_bullet(Object* bullet);
    void add_enemy_bullets(Object* bullet);
    void check_hit();

};


#endif //FINALPORJECT_VIEW_H
