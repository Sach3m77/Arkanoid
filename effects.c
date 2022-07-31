/**
 * @file effects.c
 * Plik zawierający efekty przycisków
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "effects.h"
/**
 * @brief Funkcja inicjalizująca efekty przycisków 
 * 
 * @param effects 
 * Pobierany jest dany efekt
 * @param overButton
 * Pobierany jest efekt najeżdżania kursorem na przycisk 
 * @param clickButton 
 * Pobierany jest efekt kliku na przycisk 
 */
void Effects_init(Effects *effects, char *overButton, char *clickButton){
    effects->overButton = al_load_sample(overButton);
    effects->clickButton = al_load_sample(clickButton);
}
/**
 * @brief Funkcja niszcząca efekty przycisków
 * 
 * @param Effects 
 * Pobierana jest struktura z efektami
 */
void Effects_destroy(Effects *Effects){
    al_destroy_sample(Effects->overButton);
    al_destroy_sample(Effects->clickButton);
}