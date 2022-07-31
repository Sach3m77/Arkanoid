/**
 * @file game_system.c
 * Plik inicjalizujący grę 
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_system.h"
/**
 * @brief Funkcja inicjalizująca grę
 * 
 * @param game_system
 * Pobierany jest stan systemu 
 * @return int 
 * Funkcja zwraca -1 jeśli są błedy w przeciwnym przypadku zwraca 0
 */
int Game_system_init(Game_system *game_system){

    game_system->done = 0;
    game_system->FPS = 60;
    game_system->redraw = 1;

    if(!al_init()){
        al_show_native_message_box(game_system->display, gameTitle, "Blad", "Nie udalo sie zainicjowac allegro5! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    game_system->display = al_create_display(gameWidth, gameHeight);

    if(!game_system->display){
        al_show_native_message_box(game_system->display, gameTitle, "Blad", "Nie udalo sie zainicjowac ekranu gry! \n Prosze uruchomic ponownie gre", NULL, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    al_install_mouse();
    al_install_keyboard();

    al_init_image_addon();
    al_init_primitives_addon();

    al_init_font_addon();
    al_init_ttf_addon();

    al_install_audio();
    al_init_acodec_addon();

    al_reserve_samples(10);

    game_system->event_queue = al_create_event_queue();
    al_register_event_source(game_system->event_queue, al_get_display_event_source(game_system->display));
    al_register_event_source(game_system->event_queue, al_get_mouse_event_source());
    al_register_event_source(game_system->event_queue, al_get_keyboard_event_source());

    game_system->timer = al_create_timer(1.0 / game_system->FPS);
    al_register_event_source(game_system->event_queue, al_get_timer_event_source(game_system->timer));
    al_start_timer(game_system->timer);

    return 0;

}
/**
 * @brief Funkcja odpowiedzialna za zniszczenie gry
 * 
 * @param game_system 
 * Pobierany jest stan systemu
 */
void Game_system_destroy(Game_system *game_system){

    al_destroy_display(game_system->display);
    al_destroy_event_queue(game_system->event_queue);
    al_destroy_timer(game_system->timer);

}