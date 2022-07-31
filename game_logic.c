/**
 * @file game_logic.c
 * Plik odpowiedzialny za działanie mechanizmów gry 
 * @author Pacak Równicki Ryś Sacha Sikora
 * @copyright Copyright (c) 2021
 * 
 */
#include "game_logic.h"
/**
 * @brief Funkcja odpowiedzialna za działanie mechanizmów gry 
 * 
 * @param game_system
 * Pobierany jest stan gry 
 * @param mainmenu
 * Pobierany jest stan MENU 
 * @param pause 
 * Pobierany jest stan Pause
 * @param credits 
 * Pobierany jest stan Credytów
 * @param win
 * Pobierany jest stan wygranej 
 * @param gameover
 * Pobierany jest stan przegranej 
 * @param playing
 * Pobierany jest stan rozgrywki 
 * @param color 
 * Pobierany jest stan koloru
 * @param effects 
 * Pobierany jest stan efektów
 * @param platform
 * Pobierany jest stan platformy 
 * @param balls
 * Pobierany jest stan piłeczek 
 * @param boxes
 * Pobierany jest stan klocków 
 * @param numBall
 * Pobierana jest ilość piłeczek 
 * @param numBox 
 * Pobierana jest ilość klocków
 */
void Game_loop(Game_system *game_system, Menu_system *mainmenu, Menu_system *pause, Menu_system *credits, Menu_system *win, Menu_system *gameover, Playing *playing, Color *color, Effects *effects, Platform *platform, Ball *balls, Box *boxes, int numBall, int numBox){

    mainmenu->done = 0;
    int count = 0;
    int keys[3] = {0, 0, 0};
    int curX, curY;
    int result = 0;


    while(!game_system->done){

        al_wait_for_event(game_system->event_queue, &game_system->ev);

        if(game_system->ev.timer.source == game_system->timer){

            game_system->redraw = 1;

            if(keys[LEFT])
                movePlatformLeft(platform, mainmenu, pause, win, gameover);
            if(keys[RIGHT])
                movePlatformRight(platform, mainmenu, pause, win, gameover);

            updateBall(balls, platform, playing, mainmenu, pause, win, gameover, keys, count);
            collideBall(platform, balls, count, boxes, numBox);

            if(!mainmenu->done){
                al_stop_sample_instance(win->instance);
                al_stop_sample_instance(gameover->instance);
                al_stop_sample_instance(pause->instance);
                if(!mainmenu->clickMuteButton)
                    al_play_sample_instance(mainmenu->instance);
                else if(mainmenu->clickMuteButton)
                    al_stop_sample_instance(mainmenu->instance);
            }else if(!pause->done){
                al_stop_sample_instance(playing->instance);
                al_stop_sample_instance(win->instance);
                al_stop_sample_instance(gameover->instance);
                al_play_sample_instance(pause->instance);
            }else if(!credits->done){
                al_play_sample_instance(mainmenu->instance);
            }else if(platform->score == numBox){
                al_stop_sample_instance(mainmenu->instance);
                al_stop_sample_instance(playing->instance);
                al_stop_sample_instance(pause->instance);
                al_play_sample_instance(win->instance);
            }else if(!balls[count].live && count == numBall - 1){
                al_stop_sample_instance(playing->instance);
                al_stop_sample_instance(pause->instance);
                al_play_sample_instance(mainmenu->instance);
            }else{
                al_stop_sample_instance(mainmenu->instance);
                al_stop_sample_instance(pause->instance);
                al_play_sample_instance(playing->instance);
            }

            if(platform->score == numBox){
                playing->done = 1;
                win->done = 0;
            }else if(!balls[count].live && count == numBall - 1){
                playing->done = 1;
                gameover->done = 0;
            }

        }else if(game_system->ev.type == ALLEGRO_EVENT_MOUSE_AXES){

            curX = game_system->ev.mouse.x;
            curY = game_system->ev.mouse.y;

        }else if(game_system->ev.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(game_system->ev.keyboard.keycode){
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = 1;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = 1;
                    break;
                case ALLEGRO_KEY_SPACE:
                    balls[count].kicked = 1;
                    al_start_timer(playing->timer);
                    break;
            } 
        }else if(game_system->ev.type == ALLEGRO_EVENT_KEY_UP){
            switch(game_system->ev.keyboard.keycode){
                case ALLEGRO_KEY_LEFT:
                    keys[LEFT] = 0;
                    break;
                case ALLEGRO_KEY_RIGHT:
                    keys[RIGHT] = 0;
                    break;
            }
        }else if(game_system->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            result = al_show_native_message_box(game_system->display, gameTitle, "Uwaga", "Zamknięcie gry z poziomu karty kontrolnej może spowodować uszkodzenie danych\nZamknąć?", NULL, ALLEGRO_MESSAGEBOX_WARN | ALLEGRO_MESSAGEBOX_YES_NO);

            if(result == 1) game_system->done = 1;

        }else if(game_system->ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){

            if(!mainmenu->done){

                if(game_system->ev.mouse.button == 1){

                    if(mainmenu->overMainButton[0]){

                        al_play_sample(effects->clickButton, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                        al_rest(0.5);
                        mainmenu->clickStartButton = 1;
                        playing->done = 0;

                    }else if(mainmenu->overMainButton[1]){
                        
                        al_play_sample(effects->clickButton, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                        al_rest(1.0);
                        mainmenu->done = 1;
                        credits->done = 0;

                    }else if(mainmenu->overMainButton[2]){
                        
                        al_play_sample(effects->clickButton, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
                        al_rest(0.75);
                        game_system->done = 1;

                    }else if(mainmenu->overHelpButton[0]){

                        if(!mainmenu->clickMuteButton){
                            mainmenu->clickMuteButton = 1;
                            al_play_sample_instance(mainmenu->instance);
                        }else if(mainmenu->clickMuteButton){
                            mainmenu->clickMuteButton = 0;
                            al_stop_sample_instance(mainmenu->instance);
                        }
                        Menu_system_swapBitmapSoundHelpButton(mainmenu);
                    }
                }

            }else if(!pause->done){

                if(game_system->ev.mouse.button == 1){

                    if(pause->overHelpButton[0]){
                        pause->done = 1;
                        mainmenu->done = 0;
                        Playing_draw_Reset(game_system, playing, platform, balls, boxes, numBall, numBox, &count);
                    }else if(pause->overHelpButton[1]){
                        pause->done = 1;
                    }
                }

            }else if(!credits->done){
                
                if(game_system->ev.mouse.button == 1){
                    
                    if(credits->overHelpButton[0]){
                        al_rest(0.25);
                        credits->done = 1;
                        mainmenu->done = 0;
                    }
                }

            }else if(!win->done){

                if(game_system->ev.mouse.button == 1){
                    
                    if(gameover->overHelpButton[0]){
                        win->done = 1;
                        mainmenu->done = 0;
                        Playing_draw_Reset(game_system, playing, platform, balls, boxes, numBall, numBox, &count);
                    }
                }

            }else if(!gameover->done){
                
                if(game_system->ev.mouse.button == 1){
                    
                    if(gameover->overHelpButton[0]){
                        gameover->done = 1;
                        mainmenu->done = 0;
                        Playing_draw_Reset(game_system, playing, platform, balls, boxes, numBall, numBox, &count);
                    }
                }
            }

        }else if(game_system->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

            if(mainmenu->done && pause->done && credits->done) pause->done = 0;

        }

        if(game_system->redraw && al_is_event_queue_empty(game_system->event_queue)){

            game_system->redraw = 0;

            if(!mainmenu->done){

                Menu_system_drawBackground(mainmenu);

                if(!mainmenu->clickStartButton){
                    Menu_system_draw(mainmenu, gameWidth / 2 - (mainmenu->mainBtnW / 2), 135, 15, 660, 500, 10);
                    Menu_system_detectButtonHover(mainmenu, effects, curX, curY);       
                    Menu_system_drawBitmapTextMenu(mainmenu);
                }else{
                    Menu_system_clickStartEvent(mainmenu);
                    Menu_system_drawBitmapTextMenu(mainmenu);
                }

            }else if(!pause->done){

                Playing_draw(playing, platform, color);
                drawHeart(playing, 655, 110, numBall, count);
                drawPlatform(platform);
                drawBall(balls, color, count);
                drawBox(boxes, numBox);
                Menu_system_drawBackground(pause);
                Menu_system_draw(pause, 0, 0, 0, 240, 260, 80);
                Menu_system_detectButtonHover(pause, effects, curX, curY);

            }else if(!credits->done){

                Menu_system_drawBackground(credits);
                Menu_system_draw(credits, 0, 0, 0, 670, 500, 0);
                Menu_system_detectButtonHover(credits, effects, curX, curY);

            }else if(!win->done){
                
                Menu_system_drawBackground(win);
                Menu_system_draw(win, 0, 0, 0, 350, 350, 10);
                Menu_system_drawScore(win, platform->score, color);
                Menu_system_detectButtonHover(win, effects, curX, curY);

            }else if(!gameover->done){
                
                Menu_system_drawBackground(gameover);
                Menu_system_draw(gameover, 0, 0, 0, 350, 350, 10);
                Menu_system_drawScore(gameover, platform->score, color);
                Menu_system_detectButtonHover(gameover, effects, curX, curY);

            }else if(!playing->done){
                
                Playing_draw(playing, platform, color);
                drawHeart(playing, 655, 110, numBall, count);
                drawPlatform(platform);
                drawBall(balls, color, count);
                drawBox(boxes, numBox);
            }
            al_flip_display();
			al_clear_to_color(color->black);
        }

        if(!balls[count].live && count < numBall-1){
			count++;
		}
        if(mainmenu->buttonsOutsideMenu){
            mainmenu->done = 1;
            mainmenu->clickStartButton = 0;
            mainmenu->buttonsOutsideMenu = 0;
        }
        if(game_system->ev.timer.source == playing->timer && mainmenu->done && pause->done && win->done && gameover->done)
            playing->time ++;

    }
}