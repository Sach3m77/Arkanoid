/**
 * @file color.h
 * Plik nagłówkowy zawierający elementy związane z kolorami 
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_system.h"

#pragma once
/**
 * @brief Struktura zawierająca kolory wykorzystywane w grze
 * 
 */
typedef struct{

    ALLEGRO_COLOR black;
    ALLEGRO_COLOR white;
    ALLEGRO_COLOR red;
    ALLEGRO_COLOR green;
    ALLEGRO_COLOR blue;
    ALLEGRO_COLOR yellow;

}Color;

void Color_init(Color *color);