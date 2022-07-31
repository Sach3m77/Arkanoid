/**
 * @file playing.c
 * Plik odpowiedzialny za rozgrywkę
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "playing.h"
#include "game_logic.h"
/**
 * @brief Funkcja odpowiedzialna za inicjalizację rozgrywki
 * 
 * @param game_system
 * Pobierany jest stan gry 
 * @param playing
 * Pobierany jest stan rozgrywki 
 * @param background
 * Pobierane jest tło 
 * @param heart 
 * Pobierane jest życie  
 * @param scoreFont
 * Pobierana jest czcionka wynkiku 
 * @param size 
 * Pobierany jest rozmiar czcionki
 * @param sample
 * Pobierany jest utwór podczas rozgrywki 
 * @param splash
 *  Pobierany jest utwór spadnięcia piłeczki
 */
void Playing_init(Game_system *game_system, Playing *playing, char *background, char *heart, char *scoreFont, int size, char *sample, char *splash){
    playing->done = 1;
    playing->background = al_load_bitmap(background);
    playing->heart = al_load_bitmap(heart);
    playing->scoreFont = al_load_font(scoreFont, size, 0);
    playing->sample = al_load_sample(sample);
    playing->instance = al_create_sample_instance(playing->sample);
    playing->splash = al_load_sample(splash);

    al_attach_sample_instance_to_mixer(playing->instance, al_get_default_mixer());

    playing->w = al_get_bitmap_width(playing->heart);
    playing->h = al_get_bitmap_height(playing->heart);

    playing->time = 0;
    playing->timer = al_create_timer(1.0);
    al_register_event_source(game_system->event_queue, al_get_timer_event_source(playing->timer));
}
/**
 * @brief Funkcja odpowiedzialna za otwarcie pliku tekstowego zawierającego najwyższy wynik
 * 
 * @param game_system
 * Pobierany jest stan gry 
 * @param playing 
 * Pobierany jest stan rozgrywki
 * @param path 
 * Pobierana jest ścieżka pliku
 * @param mode 
 * Pobierany jest tryb otwarci pliku 
 * @return int 
 * Zwracana jest wartośc -1 jeśli występuje błąd otwarcia lub odczytu gry w przeciwnym wypadku zwracane jest 0
 */
int Playing_openHighScoreFile(Game_system *game_system, Playing *playing, char *path, char *mode){
    
    playing->highScoreFile = al_fopen(path, mode);

    if(playing->highScoreFile == NULL){
        al_show_native_message_box(game_system->display, gameTitle, "Uwaga", "Blad otwarcia pliku gry! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    if(al_fgets(playing->highScoreFile, playing->highScore, 8) == NULL){
        al_show_native_message_box(game_system->display, gameTitle, "Uwaga", "Blad odczytu pliku gry! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    return 0;
}
/**
 * @brief Funkcja odpowiedzialna za zapisanie najwyższego wyniku do pliku tekstowego 
 * 
 * @param game_system
 * Pobierany jest stan gry 
 * @param playing 
 * Pobierany jest stan rozgrywki
 * @param platform
 * Pobierany jest stan platformy 
 * @return int
 * Zracana -1 jeśli zostanie wykryt bład w przeciwnymwypdaku zwraca 0
 */
int Playing_saveHighScoreFile(Game_system *game_system, Playing *playing, Platform *platform){
    if(platform->score > atoi(playing->highScore)){
        char buffer[8];
        itoa(platform->score, buffer, 10);

        if(!al_fseek(playing->highScoreFile, 0, ALLEGRO_SEEK_SET)){
            al_show_native_message_box(game_system->display, gameTitle, "Uwaga", "Blad operacji przesuwania wskaznika pliku gry! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

        if(al_fputs(playing->highScoreFile, buffer) == EOF){
            al_show_native_message_box(game_system->display, gameTitle, "Uwaga", "Blad zapisu pliku gry! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }
        
        if(!al_fseek(playing->highScoreFile, 0, ALLEGRO_SEEK_SET)){
            al_show_native_message_box(game_system->display, gameTitle, "Uwaga", "Blad operacji przesuwania wskaznika pliku gry! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }

        if(al_fgets(playing->highScoreFile, playing->highScore, 8) == NULL){
            al_show_native_message_box(game_system->display, gameTitle, "Uwaga", "Blad odczytu pliku gry! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
            return -1;
        }
    }

    return 0;
}
/**
 * @brief Funkcja odpowiedzialna za rozgrywkę
 * 
 * @param playing
 * Pobierany jest stan rozgrywki 
 * @param platform
 * Pobierany jest stan platformy 
 * @param color
 * Pobierany jest stan koloru 
 */
void Playing_draw(Playing *playing, Platform *platform, Color *color){
    al_draw_bitmap(playing->background, 0, 0, 0);
    al_draw_textf(playing->scoreFont, color->white, 700, 185, ALLEGRO_ALIGN_CENTER, "%d", platform->score);
    al_draw_textf(playing->scoreFont, color->white, 660, 550, 0, "%d s", playing->time);
    al_draw_textf(playing->scoreFont, color->white, 700, 270, ALLEGRO_ALIGN_CENTER, "%s", playing->highScore);
}
/**
 * @brief Funkcja odpowiedzialna za wyświetlenie ilości żyć pod postacią serduszek
 * 
 * @param playing
 * Pobierany jest stan rozgrywki 
 * @param ax
 * Pobierana jest współrzędna x 
 * @param ay 
 * Pobierana jest współrzędna y 
 * @param numBall
 * Pobierana jest liczba piłek 
 * @param count
 * Pobierany licznik 
 */
void drawHeart(Playing *playing, int ax, int ay, int numBall, int count){
    for(int i = 0; i < (numBall-count); i++){
        al_draw_bitmap(playing->heart, ax, ay, 0);
        ax += playing->w + 5;
    }
}
/**
 * @brief Funkcja odpowiedzialna za reset
 * 
 * @param game_system 
 * Pobierny jest stan gry
 * @param playing
 * Pobierany jest stan rozgrywki 
 * @param platform
 * Pobierany jest stan platformy 
 * @param ball
 * Pobierny jest stan piłeczki 
 * @param box
 * Pobierany jest stan  klocka 
 * @param numBall
 * Pobierana jest liczba piłeczek 
 * @param numBox
 * Pobierana jest liczba klocków 
 * @param count
 * Pobierany jest licznik 
 */
void Playing_draw_Reset(Game_system *game_system, Playing *playing, Platform *platform, Ball *ball, Box *box, int numBall, int numBox, int *count){
    Playing_saveHighScoreFile(game_system, playing, platform);
    initPlatform(platform, NULL);
    initBall(ball, platform, numBall);
    initBox(box, numBox);
    al_stop_timer(playing->timer);
    playing->time = 0;
    *count = 0;
}
/**
 * @brief Funkcja odpowiedzialna za inicjalizację paletki 
 * 
 * @param platform
 * Pobierany jest stan platformy 
 * @param platform_src
 *  Pobieran jest ścieżka do platformy
 */
void initPlatform(Platform *platform, char *platform_src){
    platform->ID = PLAYER;
    if(platform_src != NULL)
	    platform->platform = al_load_bitmap(platform_src);
    platform->w = al_get_bitmap_width(platform->platform);
    platform->h = al_get_bitmap_height(platform->platform);
    platform->x = 300 - platform->w / 2;
    platform->y = gameHeight - platform->h;
    platform->speed = 10;
    platform->score = 0;
}
/**
 * @brief Funkcja odpowiedzialna za wyświetlenie paletki
 * 
 * @param platform
 * Pobierany jest stan platformy 
 */
void drawPlatform(Platform *platform){
    al_draw_bitmap(platform->platform, platform->x, platform->y, 0);
}
/**
 * @brief Funkcja odpowiedzialna za ruch paletki w lewo
 * 
 * @param platform
 *  Pobierany jest stan platformy
 * @param mainmenu
 *  Pobierany jest stan MENU
 * @param pause
 * Pobierany jest stan Pause 
 * @param win
 * Pobierany jest stan wygrana 
 * @param gameover
 * Pobierany jest stan przegrana 
 */
void movePlatformLeft(Platform *platform, Menu_system *mainmenu, Menu_system *pause, Menu_system *win, Menu_system *gameover){
    if(mainmenu->done && pause->done && win->done && gameover->done){
        platform->x -= platform->speed;
        if(platform->x <= 20)
            platform->x = 20;
    }
}
/**
 * @brief Funkcja odpowiedzialna za ruch paletki w prawo 
 * 
 * @param platform
 * Pobierany jest stan platformy  
 * @param mainmenu
 * Pobierany jest stan MENU 
 * @param pause
 * Pobierany jest stan Pause
 * @param win 
 * Pobierany jest stan wygrana
 * @param gameover
 * Pobierany jest stan przegrana  
 */
void movePlatformRight(Platform *platform, Menu_system *mainmenu, Menu_system *pause, Menu_system *win, Menu_system *gameover){
    if(mainmenu->done && pause->done && win->done && gameover->done){
        platform->x += platform->speed;
        if(platform->x >= gameWidth - 312)
            platform->x = gameWidth - 312;
    }
}
/**
 * @brief Funkcja odpowiadająca za incjazlizację piłeczki
 * 
 * @param ball
 * Pobierany jest stan piłeczki
 * @param platform
 * Pobierany jest stan platformy 
 * @param lives
 * Pobierane są życia 
 */
void initBall(Ball *ball, Platform *platform, int lives){
    for(int i=0; i<lives; i++){
        ball[i].ID = BALL;
        ball[i].r = 8;
        ball[i].x = platform->x + platform->w / 2; 
        ball[i].y = gameHeight - platform->h - ball[i].r;
        ball[i].speed_x = 6;
        ball[i].speed_y = 8;
        ball[i].live = 1;
        ball[i].kicked = 0;
        ball[i].touchroof = 0;
        ball[i].touchbox = 0;
        ball[i].bouncedleft = 0;
        ball[i].bouncedright = 0;
        ball[i].touchleftwall = 0;
        ball[i].touchrightwall = 0;
        ball[i].playSound = 0;
    }
}
/**
 * @brief Funkcja odpowiadająca za fizykę gry 
 * 
 * @param ball
 * Pobierany jest stan piłeczki 
 * @param platform
 * Pobierny jest stan platformy 
 * @param keys
 * Pobierane są przyciski 
 * @param i
 *  Pobierany jest numer piłeczki
 */
void physicsBall(Ball *ball, Platform *platform, int *keys, int i){
    if(ball[i].x >= platform->x && ball[i].x <= (platform->x + platform->w) && ball[i].y == (platform->y - ball[i].r)){

        if(keys[LEFT])
            ball[i].bouncedleft = 1;
        else if(keys[RIGHT])
            ball[i].bouncedright = 1;
    }

    if(ball[i].x <= 20 + ball[i].r){
        ball[i].touchleftwall = 1;
        ball[i].bouncedleft = 0;
        ball[i].touchrightwall = 0;
    }else if(ball[i].x >= 585 - ball[i].r){
        ball[i].touchrightwall = 1; 
        ball[i].bouncedright = 0;
        ball[i].touchleftwall = 0;
    }

    if(ball[i].bouncedleft || ball[i].touchrightwall)
        ball[i].x -= ball[i].speed_x;
    else if(ball[i].bouncedright || ball[i].touchleftwall)
        ball[i].x += ball[i].speed_x;
    
}
/**
 * @brief Funkcja odpowiedzialna za zaktualizowanie piłeczki
 * 
 * @param ball
 * Pobierany jest stan piłeczki 
 * @param platform
 * Pobierany jest stan platformy 
 * @param playing
 * Pobierany jest stan gry 
 * @param mainmenu
 * Pobierny jest stan MENU
 * @param pause
 * Pobierany jest stan Pause 
 * @param win
 * Pobierany jest stan wygrana 
 * @param gameover
 * Pobierany jest stan przegrana  
 * @param keys
 * Pobierane są przyciski 
 * @param i
 * Pobierany jest numer piłeczki 
 */
void updateBall(Ball *ball, Platform *platform, Playing *playing, Menu_system *mainmenu, Menu_system *pause, Menu_system *win, Menu_system *gameover, int *keys, int i){
    if(mainmenu->done && pause->done && win->done && gameover->done){
        if(!ball[i].kicked)
            ball[i].x = platform->x + platform->w / 2;

        else if(ball[i].kicked){   

            if(!ball[i].touchbox && !ball[i].touchroof){

                physicsBall(ball, platform, keys, i); 
                ball[i].y -= ball[i].speed_y;

                if(ball[i].y <= 28)
                    ball[i].touchroof = 1;

            }else if(ball[i].touchroof && !ball[i].touchbox){

                physicsBall(ball, platform, keys, i);
                ball[i].y += ball[i].speed_y;

            }else if(!ball[i].touchroof && ball[i].touchbox){

                physicsBall(ball, platform, keys, i);
                ball[i].y += ball[i].speed_y;

            }else if(ball[i].touchroof && ball[i].touchbox){

                physicsBall(ball, platform, keys, i);
                ball[i].y -= ball[i].speed_y;

                if(ball[i].y <= 28)
                    ball[i].touchbox = 0;
                    
            }

            if(ball[i].y == (platform->y - ball[i].r) && ball[i].x >= platform->x - 10 && ball[i].x <= (platform->x + platform->w + 10)){
                ball[i].touchroof = 0;
                ball[i].touchbox = 0;
            }else if(ball[i].y > gameHeight){
                ball[i].live = 0;
                if(!ball[i].playSound){
                    al_play_sample(playing->splash, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                    ball[i].playSound = 1;
                }
            }  
        }
    }
}
/**
 * @brief Funkcja odpowiedzialna za wyświetlenie  piłeczki
 * 
 * @param ball
 * Pobierany jest stan piłeczki 
 * @param color 
 * Pobierany jest stan koloru
 * @param i
 * Pobierany jest numer piłeczki 
 */
void drawBall(Ball *ball, Color *color, int i){
    if(ball[i].live)
        al_draw_filled_circle(ball[i].x, ball[i].y, ball[i].r, color->yellow);
}
/**
 * @brief Funkcja odpowiedzialna za kolizje piłeczki
 * 
 * @param platform
 * Pobierany jest stan platformy
 * @param ball
 * Pobierany jest stan piłeczki 
 * @param i
 * Pobierany jest numer piłeczki 
 * @param box
 * Pobierany jest stan klocka 
 * @param size 
 * Pobiernay jest rozmiar
 */
void collideBall(Platform *platform, Ball *ball, int i, Box *box, int size){
    if(ball[i].live){
        for(int j=0; j<size; j++){
            if(box[j].live){
                if((ball[i].x+ball[i].r) > box[j].x && (ball[i].x-ball[i].r) < (box[j].x+box[j].width) &&
                    ball[i].y-ball[i].r < (box[j].y+box[j].height) && (ball[i].y+ball[i].r) > box[j].y){
                        ball[i].touchbox = 1;
                        box[j].live = 0;
                        platform->score += 1;
                    }
            }
        }
    } 
}
/**
 * @brief Funkcja inicjalizująca klocki
 * 
 * @param box
 * Pobierany jest stan klocka 
 * @param size
 * Pobierany jest rozmiar 
 */
void initBox(Box *box, int size){
    int j=0, l=0;
    for(int i=0; i<size; i++){
        box[i].ID = BOX;
        box[i].width = 50;
        box[i].height = 25;
        box[i].live = 0;

        if(!box[i].live){
            box[i].live = 1;
            box[i].x = 30 + (j * (box[i].width + 5));
            box[i].y = 30 + (l * (box[i].height + 5));
            
            if(box[i].x+55 >= 580){
                j = -1;
                l++;
            }
            j++;
        }
    }
}
/**
 * @brief Funkcja odpowiedzialna za wyświetlenie klocków
 * 
 * @param box
 * Pobiernay jest stan klocka 
 * @param size
 * Pobierany jest rozmiar 
 */
void drawBox(Box *box, int size){
    for(int i=0; i<size; i++){
        if(box[i].live)
            al_draw_filled_rectangle(box[i].x, box[i].y, box[i].x+box[i].width, box[i].y+box[i].height, al_map_rgb(0, 255, 255));
    }
}
/**
 * @brief Funkcja odpowiedzialna za zniszczenie rozgrywki
 * 
 * @param playing
 * Pobierany jest stan rozgrywki 
 * @param platform
 * Pobierany jest stan platformy 
 */
void Playing_destroy(Playing *playing, Platform *platform){
    al_destroy_bitmap(playing->background);
    al_destroy_bitmap(platform->platform);
    al_destroy_bitmap(playing->heart);
    al_destroy_font(playing->scoreFont);
    al_destroy_sample(playing->sample);
    al_destroy_sample(playing->splash);
    al_destroy_timer(playing->timer);
    al_fclose(playing->highScoreFile);
}