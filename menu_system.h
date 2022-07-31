/**
 * @file menu_system.h
 *Plik nagłówkowy zawierający elemnety związane z MENU
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_system.h"
#include "color.h"
#include "effects.h"

#pragma once
/**
 * @brief Struktura zawierająca elementy MENU
 * 
 */
typedef struct{

    ALLEGRO_BITMAP *background;

    ALLEGRO_BITMAP *mainButton;
    ALLEGRO_BITMAP *mainHoverButton;
    ALLEGRO_BITMAP *mainButtonText[3];

    ALLEGRO_BITMAP *helpButton[2];
    ALLEGRO_BITMAP *helpHoverButton[2];

    ALLEGRO_BITMAP *tmp[2];

    ALLEGRO_FONT *scoreFont;

    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *instance;

    int done;

    int mainBtnNum;
    int helpBtnNum;

    int overMainButton[3];
    int overHelpButton[2];
    int playMainHoverSound[3];
    int playHelpHoverSound[2];
    
    int clickStartButton;
    int buttonsOutsideMenu;
    
    int clickMuteButton;

    int mainBtnX[3], mainBtnY[3];
    int mainBtnTxtW[3], mainBtnTxtH[3];

    int helpBtnX[2], helpBtnY[2];

    int mainBtnW, mainBtnH;
    int helpBtnW, helpBtnH;

}Menu_system;

void Menu_system_init(Menu_system *menu_system);

void Menu_system_loadButtonNum(Menu_system *menu_system, int mainBtnNum, int helpBtnNum);
void Menu_system_loadBitmapBackground(Menu_system *menu_system, char *background);

void Menu_system_loadBitmapMainButton(Menu_system *menu_system, char *mainButton, char *mainHoverButton);
void Menu_system_loadBitmapOneHelpButton(Menu_system *menu_system, char *helpButton1, char *helpHoverButton1);
void Menu_system_loadBitmapTwoHelpButtons(Menu_system *menu_system, char *helpButton1, char *helpHoverButton1, char *helpButon2, char *helpHoverButton2);
void Menu_system_loadBitmapTextMenu(Menu_system *menu_system, char *START, char *CREDITS, char *EXIT);
void Menu_system_loadScoreFont(Menu_system *menu_system, char *scoreFont, int size);

void Menu_system_loadSample(Menu_system *menu_system, char *sample);

void Menu_system_swapBitmapSoundHelpButton(Menu_system *menu_system);

void Menu_system_drawBackground(Menu_system *menu_system);
void Menu_system_drawBitmapTextMenu(Menu_system *menu_system);
void Menu_system_draw(Menu_system *menu_system, int ax, int ay, int mainBtnSpace, int bx, int by, int helpBtnSpace);
void Menu_system_drawScore(Menu_system *menu_system, int score, Color *color);
void Menu_system_detectButtonHover(Menu_system *menu_system, Effects *effects, int curX, int curY);
void Menu_system_clickStartEvent(Menu_system *menu_system);

void Menu_system_destroy(Menu_system *menu_system);