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
    for (it = enemy_bullets.begin(); it != enemy_bullets.end(); it++) (*it)->plot();
    for (it = enemys.begin(); it != enemys.end(); it++) (*it)->plot();
    for (it = players.begin(); it != players.end(); it++) (*it)->plot();
    hud->plot();


    plot_count++;


    if (plot_count % 100 == 0) {

        std::list<Object *>::iterator bullet, enemy;
        for (enemy = enemys.begin(); enemy != enemys.end(); enemy++) {
            auto enemy_ = dynamic_cast<Enemy *>(*enemy);

            enemy_->fire();
        }
    }


}

void View::update_position() {
    backGround->update_position();

    std::list<Object *>::iterator it;
    for (it = bullets.begin(); it != bullets.end(); it++) (*it)->update_position();
    for (it = enemy_bullets.begin(); it != enemy_bullets.end(); it++) (*it)->update_position();
    for (it = enemys.begin(); it != enemys.end(); it++) (*it)->update_position();
    for (it = players.begin(); it != players.end(); it++) (*it)->update_position();

//    printf("%d \n", bullets.size());
}

void View::collect_garbage() {
    bullets.remove_if(is_garbage);
    enemy_bullets.remove_if(is_garbage);
    enemys.remove_if(is_garbage);
//    players.remove_if(is_garbage);

}

void View::add_bullet(Object *bullet) {
    bullets.push_back(bullet);
}

void View::add_enemy_bullets(Object *bullet) {
    enemy_bullets.push_back(bullet);
}


void View::check_hit() {

    std::list<Object *>::iterator bullet, enemy;
    for (bullet = bullets.begin(); bullet != bullets.end(); bullet++) {
        for (enemy = enemys.begin(); enemy != enemys.end(); enemy++) {
            auto bullet_ = dynamic_cast<Bullet *>(*bullet);
            auto enemy_ = dynamic_cast<Enemy *>(*enemy);
            if (!bullet_->is_garbage && !enemy_->is_garbage) {

                int dx = enemy_->x - bullet_->x;
                int dy = enemy_->y - bullet_->y;
                float er = enemy_->collision_radius;
                float br = bullet_->collision_radius;

                double distance = sqrt(pow(dx, 2) + pow(dy, 2));

                if (distance < er + br)enemy_->hit(bullet_);

            }
        }
    }


    std::list<Object *>::iterator enemy_bullet, player;
    for (enemy_bullet = enemy_bullets.begin(); enemy_bullet != enemy_bullets.end(); enemy_bullet++) {
        for (player = players.begin(); player != players.end(); player++) {
            auto enemy_bullet_ = dynamic_cast<Bullet *>(*enemy_bullet);
            auto player_ = dynamic_cast<Player *>(*player);


            if (!enemy_bullet_->is_garbage && !player_->is_garbage) {
                int dx = player_->x - enemy_bullet_->x;
                int dy = player_->y - enemy_bullet_->y;
                float er = player_->collision_radius;
                float br = enemy_bullet_->collision_radius;

                double distance = sqrt(pow(dx, 2) + pow(dy, 2));

                if (distance < er + br)player_->hit(enemy_bullet_);
            }
        }
    }

}