//
// Created by cswu on 2018/12/15.
//

#include "View.h"
#include "Object.h"
#include "../objects/character.h"
#include <list>
#include <cstdio>
#include <cmath>


bool is_garbage(Object *object) {
    if (object->is_garbage != 0) {
        delete (object);
        return true;
    }
    return false;
}

void View::plot() {

    backGround->plot();
    std::list<Object *>::iterator it;
    for (it = bullets.begin(); it != bullets.end(); it++) (*it)->plot();
    for (it = enemys.begin(); it != enemys.end(); it++) (*it)->plot();
    for (it = players.begin(); it != players.end(); it++) (*it)->plot();
    hud->plot();


    plot_count++;
}

void View::update_position() {
    backGround->update_position();

    std::list<Object *>::iterator it;
    for (it = bullets.begin(); it != bullets.end(); it++) (*it)->update_position();
    for (it = enemys.begin(); it != enemys.end(); it++) (*it)->update_position();
    for (it = players.begin(); it != players.end(); it++) (*it)->update_position();

//    printf("%d \n", bullets.size());
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

void View::check_hit() {

    std::list<Object *>::iterator bullet, enemy;
    for (bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
        for (enemy = enemys.begin(); enemy != enemys.end(); enemy++) {
            auto bullet_ = dynamic_cast<Bullet *>(*bullet);
            auto enemy_ = dynamic_cast<Enemy *>(*enemy);

            int dx = enemy_->x - bullet_->x;
            int dy = enemy_->y - bullet_->y;
            float er = enemy_->collision_radius;
            float br = bullet_->collision_radius;

            double distance = sqrt(pow(dx, 2) + pow(dy, 2));

            if (distance < er + br)enemy_->hit(bullet_);
        }
    }

}