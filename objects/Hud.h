//
// Created by Chi-Sheng Wu on 2019/1/14.
//

#ifndef FINALPORJECT_HUD_H
#define FINALPORJECT_HUD_H


#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "../config.h"
#include "../Interface/View.h"
#include "../Interface/Object.h"

class Hud : public Object {

public:
    Hud(View * view);
    ~Hud() override = default;

    void plot() override;

    void update_position() override ;

};



#endif //FINALPORJECT_HUD_H
