/**
 * @file game_system.h
 * Plik nagłówkowy zawierający elementy odpowiedzialne za system gry
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/**
 * @brief Nazwa gry
 * 
 */
#define gameTitle "Arcanoid"
/**
 * @brief Szerokośc okna
 * 
 */
#define gameWidth 800
/**
 * @brief Wysokośc okna
 * 
 */
#define gameHeight 600

#pragma once
/**
 * @brief Struktura zawierająca elementy związane z działaniem systemu gry 
 * 
 */
typedef struct{

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_EVENT ev;
    ALLEGRO_TIMER *timer;

    int done;
    int redraw;
    int FPS;
    
}Game_system;

int Game_system_init(Game_system *game_system);
void Game_system_destroy(Game_system *game_system);