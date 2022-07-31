/**
 * @file playing.h
 * Flik nagłówkowy zawierający elementy związane z rozgrywką 
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_system.h"
#include "menu_system.h"
#include "color.h"

#pragma once
/**
 * @brief Typ wyliczeniowy zawierający nazwy
 * 
 */
enum IDS {PLAYER, BALL, BOX};
/**
 * @brief Struktura zawięrająca elementy rozgrywki
 * 
 */
typedef struct{

    ALLEGRO_BITMAP *background;
    ALLEGRO_BITMAP *heart;

    ALLEGRO_FONT *scoreFont;

    ALLEGRO_SAMPLE *sample;
    ALLEGRO_SAMPLE_INSTANCE *instance;
    ALLEGRO_SAMPLE *splash;

    ALLEGRO_FILE *highScoreFile;

    ALLEGRO_TIMER *timer;

    int done;
    int w, h;
    char highScore[8];
    int time;

}Playing;
/**
 * @brief Struktura zawierająca elementy platformy
 * 
 */
typedef struct{

    ALLEGRO_BITMAP *platform;

    int ID;
    int x, y;
    int w, h;
    int speed;
    int score;

}Platform;
/**
 * @brief Struktura zawierająca elementy piłeczki
 * 
 */
typedef struct{

    int ID;
    int x;
    int y;
    int live;
    int speed_x;
    int speed_y;
    int r;
    int kicked;
    int touchbox;
    int touchroof;
    int bouncedleft;
    int bouncedright;
    int touchleftwall;
    int touchrightwall;
    int playSound;

}Ball;
/**
 * @brief Struktura zawierająca elementy klocków
 * 
 */
typedef struct{

    int ID;
    int x;
    int y;
    int live;
    int width;
    int height;

}Box;

void Playing_init(Game_system *game_system, Playing *playing, char *background, char *heart, char *scoreFont, int size, char *sample, char *splash);

int Playing_openHighScoreFile(Game_system *game_system, Playing *playing, char *path, char *mode);
int Playing_saveHighScoreFile(Game_system *game_system, Playing *playing, Platform *platform);

void Playing_draw(Playing *playing, Platform *platform, Color *color);
void drawHeart(Playing *playing, int ax, int ay, int numBall, int count);
void Playing_draw_Reset(Game_system *game_system, Playing *playing, Platform *platform, Ball *ball, Box *box, int numBall, int numBox, int *count);

void initPlatform(Platform *platform, char *platform_src);
void drawPlatform(Platform *platform);
void movePlatformLeft(Platform *platform, Menu_system *mainmenu, Menu_system *pause, Menu_system *win, Menu_system *gameover);
void movePlatformRight(Platform *platform, Menu_system *mainmenu, Menu_system *pause, Menu_system *win, Menu_system *gameover);

void initBall(Ball *ball, Platform *platform, int lives);
void physicsBall(Ball *ball, Platform *platform, int *keys, int i);
void updateBall(Ball *ball, Platform *platform, Playing *playing, Menu_system *mainmenu, Menu_system *pause, Menu_system *win, Menu_system *gameover, int *keys, int i);
void drawBall(Ball *ball, Color *color, int i);
void collideBall(Platform *platform, Ball *ball, int i, Box *box, int size);

void initBox(Box *box, int size);
void drawBox(Box *box, int size);

void Playing_destroy(Playing *playing, Platform *platform);