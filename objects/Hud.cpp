//
// Created by Chi-Sheng Wu on 2019/1/14.
//

#include "Hud.h"
#include <string>


Hud::Hud(View *view) : Object(view, 0, 0, nullptr) {
    font = al_load_ttf_font("font/pirulen.ttf", 30, 0);
}


void Hud::plot() {


    auto str = "HP : " + std::to_string(view->player_hp);

    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH - 200, SCREEN_HEIGHT - 50, ALLEGRO_ALIGN_CENTRE, str.c_str());

    auto str2 = "score : " + std::to_string(view->player_score);

    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH - 200, SCREEN_HEIGHT - 90, ALLEGRO_ALIGN_CENTRE, str2.c_str());

    auto str3 = "coin : " + std::to_string(view->player_coin);

    al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_WIDTH - 200, SCREEN_HEIGHT - 130, ALLEGRO_ALIGN_CENTRE, str3.c_str());

}


void Hud::update_position() {

}


