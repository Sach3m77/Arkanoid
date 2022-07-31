/**
 * @file main.c
 * Plik główny gry 
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_system.h"
#include "menu_system.h"
#include "game_logic.h"
#include "effects.h"
#include "playing.h"
/**
 * @brief Liczba przycisków w MENU
 * 
 */
#define MM_MAIN_BUTTON_NUMBER 3
/**
 * @brief Liczba przycisków pomocniczych w MENU
 * 
 */
#define MM_HELP_BUTTON_NUMBER 1
/**
 * @brief Liczba przycisków Pause w MENU
 * 
 */
#define PAUSE_MAIN_BUTTON_NUMBER 0
/**
 * @brief Liczba przycisków pomocniczych Pause
 * 
 */
#define PAUSE_HELP_BUTTON_NUMBER 2
/**
 * @brief Liczba przycisków Creditów
 * 
 */
#define CREDITS_MAIN_BUTTON_NUMBER 0
/**
 * @brief Liczba przycisków pomocniczych Creditów
 * 
 */
#define CREDITS_HELP_BUTTON_NUMBER 1
/**
 * @brief Liczba przycisków wygranej
 * 
 */

#define WIN_MAIN_BUTTON_NUMBER 0
/**
 * @brief Liczba przycisków pomocniczych wygranej
 * 
 */
#define WIN_HELP_BUTTON_NUMBER 1
/**
 * @brief Liczba przycisków przegranej
 * 
 */
#define GAMEOVER_MAIN_BUTTON_NUMBER 0
/**
 * @brief Liczba przycisków pomocniczych przegranej
 * 
 */
#define GAMEOVER_HELP_BUTTON_NUMBER 1

/**
 * @brief Liczba żyć
 * 
 */
#define LIVES 3
/**
 * @brief Liczba klocków
 * 
 */
#define NUMBOX 50
/**
 * @brief Rozmiar czcionki wyniku podczas gry
 * 
 */
#define PLAYING_scoreFontSize 30
/**
 * @brief Rozmiar czcionki wyniku podczas przegranej
 * 
 */
#define WIN_GAMEOVER_scoreFontSize 40
/**
 * @brief Funkcja główna
 * 
 * @return int
 * Zwraca 0 
 */
int main()
{
    
    Game_system game;

    Menu_system mainmenu; 
    Menu_system pause;
    Menu_system win;
    Menu_system gameover;
    Menu_system credits; 

    Playing playing;

    Color color;
    Effects effects;

    Platform platform;
    Ball balls[3];
    Box boxes[NUMBOX];

    Game_system_init(&game);

    Menu_system_init(&mainmenu);
    Menu_system_loadButtonNum(&mainmenu, MM_MAIN_BUTTON_NUMBER, MM_HELP_BUTTON_NUMBER);
    Menu_system_loadBitmapBackground(&mainmenu, "image/background/main_menu_bg.jpg");
    Menu_system_loadBitmapMainButton(&mainmenu, "image/button/main_button.png", "image/button/main_hover_button.png");
    Menu_system_loadBitmapTwoHelpButtons(&mainmenu, "image/button/mute.png", "image/button/hover_mute.png", "image/button/unmute.png", "image/button/hover_unmute.png");
    Menu_system_loadSample(&mainmenu, "audio/music/main_menu.mp3");
    Menu_system_loadBitmapTextMenu(&mainmenu, "fonts/START.png", "fonts/CREDITS.png", "fonts/EXIT.png");

    Menu_system_init(&pause);
    Menu_system_loadButtonNum(&pause, PAUSE_MAIN_BUTTON_NUMBER, PAUSE_HELP_BUTTON_NUMBER);
    Menu_system_loadBitmapBackground(&pause, "image/background/pause_bg.png");
    Menu_system_loadBitmapTwoHelpButtons(&pause, "image/button/quit.png", "image/button/hover_quit.png", "image/button/play.png", "image/button/hover_play.png");
    Menu_system_loadSample(&pause, "audio/music/pause.mp3");

    Menu_system_init(&credits);
    Menu_system_loadButtonNum(&credits, CREDITS_MAIN_BUTTON_NUMBER, CREDITS_HELP_BUTTON_NUMBER);
    Menu_system_loadBitmapBackground(&credits, "image/background/credits_bg.png");
    Menu_system_loadBitmapOneHelpButton(&credits, "image/button/back.png", "image/button/hover_back.png");

    Menu_system_init(&win);
    Menu_system_loadButtonNum(&win, WIN_MAIN_BUTTON_NUMBER, WIN_HELP_BUTTON_NUMBER);
    Menu_system_loadBitmapBackground(&win, "image/background/win_bg.png");
    Menu_system_loadBitmapOneHelpButton(&win, "image/button/back.png", "image/button/hover_back.png");
    Menu_system_loadScoreFont(&win, "fonts/karma.ttf", WIN_GAMEOVER_scoreFontSize);
    Menu_system_loadSample(&win, "audio/music/win.wav");

    Menu_system_init(&gameover);
    Menu_system_loadButtonNum(&gameover, GAMEOVER_MAIN_BUTTON_NUMBER, GAMEOVER_HELP_BUTTON_NUMBER);
    Menu_system_loadBitmapBackground(&gameover, "image/background/game_over_bg.jpg");
    Menu_system_loadBitmapOneHelpButton(&gameover, "image/button/back.png", "image/button/hover_back.png");
    Menu_system_loadScoreFont(&gameover, "fonts/karma.ttf", WIN_GAMEOVER_scoreFontSize);
    Menu_system_loadSample(&gameover, "audio/music/game_over.mp3");

    Playing_init(&game, &playing, "image/background/playing_bg.jpg", "image/other/heart.png", "fonts/karma.ttf", PLAYING_scoreFontSize, "audio/music/playing.mp3", "audio/effects/poolsplash.wav");
    Playing_openHighScoreFile(&game, &playing, "high_score.txt", "r+");
    
    Color_init(&color);
    Effects_init(&effects, "audio/effects/over_button.wav", "audio/effects/click_button.wav");
    
    initPlatform(&platform, "image/other/paletka.png");
    initBall(balls, &platform, LIVES);
    initBox(boxes, NUMBOX);

    Game_loop(&game, &mainmenu, &pause, &credits, &win, &gameover, &playing, &color, &effects, &platform, balls, boxes, LIVES, NUMBOX);

    Menu_system_destroy(&mainmenu);
    Menu_system_destroy(&pause);
    Menu_system_drawBitmapTextMenu(&credits);
    Menu_system_destroy(&win);
    Menu_system_destroy(&gameover);
    Playing_destroy(&playing, &platform);
    Effects_destroy(&effects);
    Game_system_destroy(&game);

    return 0;
}