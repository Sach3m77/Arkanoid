/**
 * @file color.c
 * Plik zawierający inicjacje kolorów
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "color.h"
/**
 * @brief Funkcja inicjalizująca kolory w grze
 * 
 * @param color 
 * Pobierany jest stan koloru
 */
void Color_init(Color *color){

    color->black = al_map_rgb(0, 0, 0);
    color->white = al_map_rgb(255, 255, 255);
    color->red = al_map_rgb(255, 0, 0);
    color->green = al_map_rgb(0, 255, 0);
    color->blue = al_map_rgb(0, 0, 255);
    color->yellow = al_map_rgb(255, 255, 0);

}