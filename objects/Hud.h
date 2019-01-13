//
// Created by Chi-Sheng Wu on 2019/1/14.
//

#ifndef FINALPORJECT_HUD_H
#define FINALPORJECT_HUD_H


#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

class Hud {

    Hud(){

    }

    void plot(){
        font = al_load_ttf_font("font/pirulen.ttf", 30, 0);
        al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 220, ALLEGRO_ALIGN_CENTRE,
                     "Press 'Enter' to start");
    }


};


#endif //FINALPORJECT_HUD_H
