/**
 * @file menu_system.c
 * Plik odpowiedzialny za menu gry 
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "menu_system.h"
/**
 * @brief Funkcja inicjalizująca grę
 * 
 * @param menu_system 
 * Pobierany jest stan MENU
 */

void Menu_system_init(Menu_system *menu_system){
    menu_system->done = 1;
    menu_system->clickStartButton = 0;
    menu_system->buttonsOutsideMenu = 0;
    menu_system->clickMuteButton = 0;
}
/**
 * @brief Funkcja pobierająca ilość przycisków
 * 
 * @param menu_system 
 * Pobierany jest stan MENU
 * @param mainBtnNum 
 * Pobierana jest liczba przycisków
 * @param helpBtnNum 
 * Pobierana jest liczba przycisków pomocniczych
 */
void Menu_system_loadButtonNum(Menu_system *menu_system, int mainBtnNum, int helpBtnNum){
    menu_system->mainBtnNum = mainBtnNum;
    menu_system->helpBtnNum = helpBtnNum;
}
/**
 * @brief Funkcja ładująca tło
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 * @param background
 * Pobierane jest tło 
 */
void Menu_system_loadBitmapBackground(Menu_system *menu_system, char *background){
    menu_system->background = al_load_bitmap(background);
}
/**
 * @brief Funkcja łądująca przyciski 
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 * @param mainButton
 *  Pobierany jest obrazek przycisku
 * @param mainHoverButton 
 * Pobierany jest obrazek przycisku
 */
void Menu_system_loadBitmapMainButton(Menu_system *menu_system, char *mainButton, char *mainHoverButton){
    menu_system->mainButton = al_load_bitmap(mainButton);
    menu_system->mainBtnW = al_get_bitmap_width(menu_system->mainButton);
    menu_system->mainBtnH = al_get_bitmap_height(menu_system->mainButton);
    menu_system->mainHoverButton = al_load_bitmap(mainHoverButton);
}
/**
 * @brief Funkcja ładująca jeden przycisk pomocniczy
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 * @param helpButton1 
 * Pobierany jest obrazek przycisku 1 
 * @param helpHoverButton1
 * Pobierany jest obrazek przycisku 1 
 */
void Menu_system_loadBitmapOneHelpButton(Menu_system *menu_system, char *helpButton1, char *helpHoverButton1){
    menu_system->helpButton[0] = al_load_bitmap(helpButton1);
    menu_system->helpHoverButton[0] = al_load_bitmap(helpHoverButton1);
    
    menu_system->helpBtnW = al_get_bitmap_width(menu_system->helpButton[0]);
    menu_system->helpBtnH = al_get_bitmap_height(menu_system->helpButton[0]);

}
/**
 * @brief Funkcja ładująca dwa przyciski
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 * @param helpButton1 
 * Pobierany jest obrazek przycisku 1 
 * @param helpHoverButton1 
 * Pobierany jest obrazek przycisku 1 
 * @param helpButon2 
 * Pobierany jest obrazek przycisku 2 
 * @param helpHoverButton2
 * Pobierany jest obrazek przycisku 1  
 */
void Menu_system_loadBitmapTwoHelpButtons(Menu_system *menu_system, char *helpButton1, char *helpHoverButton1, char *helpButon2, char *helpHoverButton2){
    menu_system->helpButton[0] = al_load_bitmap(helpButton1);
    menu_system->helpHoverButton[0] = al_load_bitmap(helpHoverButton1);

    menu_system->helpButton[1] = al_load_bitmap(helpButon2);
    menu_system->helpHoverButton[1] = al_load_bitmap(helpHoverButton2);
    
    menu_system->helpBtnW = al_get_bitmap_width(menu_system->helpButton[0]);
    menu_system->helpBtnH = al_get_bitmap_height(menu_system->helpButton[0]);

}
/**
 * @brief Funkcja ładująca obrazki z tekstami przycisków
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 * @param START
 * Pobierany jest obrazek z tekstem START 
 * @param CREDITS
 * Pobierany jest obrazek z tekstem CREDITS
 * @param EXIT
 * Pobierany jest obrazek z tekstem EXIT  
 */
void Menu_system_loadBitmapTextMenu(Menu_system *menu_system, char *START, char *CREDITS, char *EXIT){
    menu_system->mainButtonText[0] = al_load_bitmap(START);
    menu_system->mainButtonText[1] = al_load_bitmap(CREDITS);
    menu_system->mainButtonText[2] = al_load_bitmap(EXIT);

    menu_system->mainBtnTxtW[0] = al_get_bitmap_width(menu_system->mainButtonText[0]);
    menu_system->mainBtnTxtH[0] = al_get_bitmap_height(menu_system->mainButtonText[0]);
    menu_system->mainBtnTxtW[1] = al_get_bitmap_width(menu_system->mainButtonText[1]);
    menu_system->mainBtnTxtH[1] = al_get_bitmap_height(menu_system->mainButtonText[1]);
    menu_system->mainBtnTxtW[2] = al_get_bitmap_width(menu_system->mainButtonText[2]);
    menu_system->mainBtnTxtH[2] = al_get_bitmap_height(menu_system->mainButtonText[2]);

}
/**
 * @brief Funkcja odpowiedzialna za załadowania czcionki wyniku 
 * 
 * @param menu_system 
 * Pobierany jest stan MENU
 * @param scoreFont
 * Pobierana jest czcionka wyniku 
 * @param size
 * Pobierany jest rozmiar czcionki 
 */
void Menu_system_loadScoreFont(Menu_system *menu_system, char *scoreFont, int size){
    menu_system->scoreFont = al_load_font(scoreFont, size, 0);
}
/**
 * @brief Funkcja odpowiadająca za piosenki
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 * @param sample
 * Pobierany jest utwór 
 */
void Menu_system_loadSample(Menu_system *menu_system, char *sample){
    menu_system->sample = al_load_sample(sample);
    menu_system->instance = al_create_sample_instance(menu_system->sample);

    al_attach_sample_instance_to_mixer(menu_system->instance, al_get_default_mixer());
}
/**
 * @brief Funkcja odpowiadająca za przycisk muzyki
 * 
 * @param menu_system 
 * Pobierany jest stan MENU
 */
void Menu_system_swapBitmapSoundHelpButton(Menu_system *menu_system){
    menu_system->tmp[0] = menu_system->helpButton[0];
    menu_system->tmp[1] = menu_system->helpHoverButton[0];
    menu_system->helpButton[0] = menu_system->helpButton[1];
    menu_system->helpHoverButton[0] = menu_system->helpHoverButton[1];
    menu_system->helpButton[1] = menu_system->tmp[0];
    menu_system->helpHoverButton[1] = menu_system->tmp[1];
}
/**
 * @brief Funkcja odpowiedzialna za wyświetlnie tła
 * 
 * @param menu_system 
 * Pobierany jest stan MENU
 */
void Menu_system_drawBackground(Menu_system *menu_system){
    al_draw_bitmap(menu_system->background, 0, 0, 0);
}
/**
 * @brief Funkcja odpowiedzialna za wyświetlenie textu MENU
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 */
void Menu_system_drawBitmapTextMenu(Menu_system *menu_system){
    
    for(int i = 0; i < menu_system->mainBtnNum; i++){
        al_draw_bitmap(menu_system->mainButtonText[i], (menu_system->mainBtnX[i] + (menu_system->mainBtnW / 2) - (menu_system->mainBtnTxtW[i] / 2)), (menu_system->mainBtnY[i] + (menu_system->mainBtnH / 2) - (menu_system->mainBtnTxtH[i] / 2)), 0);
    }
}
/**
 * @brief Funkcja odpowiedzialna za wyświetlnie przycisków w MENU
 * 
 * @param menu_system
 * Pobierany jest stan MENU 
 * @param ax 
 * Pobierana jest współrzędna x przyciku głównego
 * @param ay
 *  Pobierana jest współrzędna y przyciku głównego
 * @param mainBtnSpace
 *  Pobierana jest przerwa między przyciskami głównymi
 * @param bx
 *  Pobierana jest współrzędna x przyciku pomocniczego
 * @param by 
 * Pobierana jest współrzędna y przyciku głównego
 * @param helpBtnSpace 
 * Pobierana jest przerwa między przyciskami pomocniczymi
 */
void Menu_system_draw(Menu_system *menu_system, int ax, int ay, int mainBtnSpace, int bx, int by, int helpBtnSpace){
    
    for(int i = 0; i < menu_system->mainBtnNum; i++){
        menu_system->mainBtnX[i] = ax;
        menu_system->mainBtnY[i] = ay;
        ay = menu_system->mainBtnY[i] + menu_system->mainBtnH + mainBtnSpace;

        al_draw_bitmap(menu_system->mainButton, menu_system->mainBtnX[i], menu_system->mainBtnY[i], 0);
    }

    for(int i = 0; i < menu_system->helpBtnNum; i++){
        menu_system->helpBtnX[i] = bx;
        menu_system->helpBtnY[i] = by;
        bx = menu_system->helpBtnX[i] + menu_system->helpBtnW + helpBtnSpace;

        al_draw_bitmap(menu_system->helpButton[i], menu_system->helpBtnX[i], menu_system->helpBtnY[i], 0);
    }

}
/**
 * @brief Funkcja odpowiedzialna za wypisanie wyniku
 * 
 * @param menu_system 
 * Pobierany jest stan MENU
 * @param score
 * Pobierany jest wynik 
 * @param color
 * Pobierany jest stan koloru 
 */
void Menu_system_drawScore(Menu_system *menu_system, int score, Color *color){
    al_draw_textf(menu_system->scoreFont, color->white, gameWidth / 2, gameHeight / 2 - 25, ALLEGRO_ALIGN_CENTER, "Your Score: %d", score);
}
/**
 * @brief Funkcja odpowiadająca za wykrycie najechania kursora na przycisk
 * 
 * @param menu_system
 * Pobrany jest MENU 
 * @param effects
 * Pobierany jest stan efektu 
 * @param curX 
 * Pobierana jest współrzędna x kursora
 * @param curY
 * Pobierana jest współrzędna y kursora 
 */
void Menu_system_detectButtonHover(Menu_system *menu_system, Effects *effects, int curX, int curY){
    for(int i = 0; i < menu_system->mainBtnNum; i++){
        if( (curX >= menu_system->mainBtnX[i]) && (curX <= menu_system->mainBtnX[i] + menu_system->mainBtnW)
         && (curY >= menu_system->mainBtnY[i]) && (curY <= menu_system->mainBtnY[i] + menu_system->mainBtnH)){

            al_draw_bitmap(menu_system->mainHoverButton, menu_system->mainBtnX[i], menu_system->mainBtnY[i], 0);
            menu_system->overMainButton[i] = 1;

            if(!menu_system->playMainHoverSound[i]){
                al_play_sample(effects->overButton, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                menu_system->playMainHoverSound[i] = 1;
            }

        }else {
            menu_system->overMainButton[i] = 0;
            menu_system->playMainHoverSound[i] = 0;
        }
    }
    for(int i = 0; i < menu_system->helpBtnNum; i++){
        if( (curX >= menu_system->helpBtnX[i]) && (curX <= menu_system->helpBtnX[i] + menu_system->helpBtnW)
         && (curY >= menu_system->helpBtnY[i]) && (curY <= menu_system->helpBtnY[i] + menu_system->helpBtnH)){

            al_draw_bitmap(menu_system->helpHoverButton[i], menu_system->helpBtnX[i], menu_system->helpBtnY[i], 0);
            menu_system->overHelpButton[i] = 1;

            if(!menu_system->playHelpHoverSound[i]){
                al_play_sample(effects->overButton, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                menu_system->playHelpHoverSound[i] = 1;
            }

        }else {
            menu_system->overHelpButton[i] = 0;
            menu_system->playHelpHoverSound[i] = 0;
        }
    }
}
/**
 * @brief Funkcja odpowiedzialna za kliknięcie przycisku START
 * 
 * @param menu_system 
 * Pobrany jest stan MENU
 */
void Menu_system_clickStartEvent(Menu_system *menu_system){

    menu_system->mainBtnX[0] += 12;
    menu_system->mainBtnX[1] -= 12;
    menu_system->mainBtnX[2] += 12;

    menu_system->helpBtnY[0] += 15;
    
    al_draw_bitmap(menu_system->mainButton, menu_system->mainBtnX[0], menu_system->mainBtnY[0], 0);
    al_draw_bitmap(menu_system->mainButton, menu_system->mainBtnX[1], menu_system->mainBtnY[1], 0);
    al_draw_bitmap(menu_system->mainButton, menu_system->mainBtnX[2], menu_system->mainBtnY[2], 0);

    al_draw_bitmap(menu_system->helpButton[0], menu_system->helpBtnX[0], menu_system->helpBtnY[0], 0);

    if(menu_system->mainBtnX[0] == 802 && menu_system->mainBtnX[1] == -206 && menu_system->mainBtnX[2] == 802)
        menu_system->buttonsOutsideMenu = 1;

}
/**
 * @brief Funkcja odpowiedzialna za zniszczenie MENU
 * 
 * @param menu_system
 * Pobrany jest stanu MENU 
 */
void Menu_system_destroy(Menu_system *menu_system){
    al_destroy_bitmap(menu_system->background);
    if(menu_system->mainBtnNum != 0){
        al_destroy_bitmap(menu_system->mainButton);
        al_destroy_bitmap(menu_system->mainHoverButton);
        for(int i = 0; i < menu_system->mainBtnNum; i++){
            al_destroy_bitmap(menu_system->mainButtonText[i]);
        }
    }
    for(int i = 0; i < menu_system->helpBtnNum; i++){
        al_destroy_bitmap(menu_system->helpButton[i]);
        al_destroy_bitmap(menu_system->helpHoverButton[i]);
    }
    if(menu_system->sample != NULL)
        al_destroy_sample(menu_system->sample);
}