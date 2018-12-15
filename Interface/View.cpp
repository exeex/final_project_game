//
// Created by cswu on 2018/12/15.
//

#include "View.h"
#include "Object.h"
#include <list>


bool is_garbage(Object *object)
{
    return object->is_garbage != 0;
}

void View::plot() {
    backGround->plot();
    std::list<Object *>::iterator it;
    for (it = bullets.begin(); it != bullets.end(); it++) (*it)->plot();
    for (it = enemys.begin(); it != enemys.end(); it++) (*it)->plot();
    for (it = players.begin(); it != players.end(); it++) (*it)->plot();
}

void View::update_position() {
    backGround->update_position();

    std::list<Object *>::iterator it;
    for (it = bullets.begin(); it != bullets.end(); it++) (*it)->update_position();
    for (it = enemys.begin(); it != enemys.end(); it++) (*it)->update_position();
    for (it = players.begin(); it != players.end(); it++) (*it)->update_position();
}

void View::collect_garbage() {
    backGround->update_position();
    bullets.remove_if(is_garbage);
    enemys.remove_if(is_garbage);
    players.remove_if(is_garbage);

}

void View::add_bullet(Object *bullet) {
    bullets.push_back(bullet);
}