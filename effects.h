/**
 * @file effects.h
 * Plik nagłówkowy zawierający elementy związane z efektami przycisków 
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_system.h"

#pragma once
/**
 * @brief Struktura zawierająca efekty przycisków
 * 
 */
typedef struct{

    ALLEGRO_SAMPLE *overButton;
    ALLEGRO_SAMPLE *clickButton;

}Effects;

void Effects_init(Effects *effects, char *overButton, char *clickButton);

void Effects_destroy(Effects *Effects);