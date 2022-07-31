/**
 * @file game_logic.h
 * Plik nagłówkowy zawierający elementy związane z działanie gry
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_system.h"
#include "menu_system.h"
#include "color.h"
#include "playing.h"

#pragma once
/**
 * @brief Typ wyliczeniowy przechowujący przyciski potrzebne do sterowania platformą
 * 
 */
enum KEYS { LEFT, RIGHT, SPACE };

void Game_loop(Game_system *game_system, Menu_system *mainmenu, Menu_system *pause, Menu_system *credits, Menu_system *win, Menu_system *gameover, Playing *playing, Color *color, Effects *effects, Platform *platform, Ball *balls, Box *boxes, int numBall, int numBox);