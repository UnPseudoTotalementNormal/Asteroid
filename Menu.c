#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Deltatime.h"
#include "Vector2_tools.h"
#include "ButtonPress.h"
#include "Player.h"
#include "Menu.h"

typedef int bool;
#define true 1
#define false 0

void main_menu(sfRenderWindow* window, sfFont* font, struct GameSettings* Gsettings) {
    float WINDOW_X = sfVideoMode_getDesktopMode().width;
    float ratio_x = WINDOW_X / 2560.0;

    sfRectangleShape* highlight = sfRectangleShape_create();
    sfRectangleShape_setFillColor(highlight, sfColor_fromRGBA((sfUint8) 255, (sfUint8) 255, (sfUint8) 255, (sfUint8) 45));

    sfText* title_text = sfText_create();
    sfText_setFont(title_text, font);
    sfText_setString(title_text, "Shotgunnin' Space");
    sfText_setCharacterSize(title_text, 120 * ratio_x);
    sfText_setPosition(title_text, (sfVector2f) { -sfText_getLocalBounds(title_text).width / 2 + WINDOW_X / 2, 50 * ratio_x });

    sfText* singleplayer_text = sfText_create();
    sfText_setFont(singleplayer_text, font);
    sfText_setString(singleplayer_text, "SinglePlayer");
    sfText_setCharacterSize(singleplayer_text, 80 * ratio_x);
    sfText_setPosition(singleplayer_text, (sfVector2f) { -sfText_getLocalBounds(singleplayer_text).width / 2 + WINDOW_X / 2, 700 * ratio_x });

    sfText* multiplayer_text = sfText_create();
    sfText_setFont(multiplayer_text, font);
    sfText_setString(multiplayer_text, "MultiPlayer");
    sfText_setCharacterSize(multiplayer_text, 80 * ratio_x);
    sfText_setPosition(multiplayer_text, (sfVector2f) { -sfText_getLocalBounds(multiplayer_text).width / 2 + WINDOW_X / 2, 950 * ratio_x });

    sfText* quit_text = sfText_create();
    sfText_setFont(quit_text, font);
    sfText_setString(quit_text, "Quit");
    sfText_setCharacterSize(quit_text, 80 * ratio_x);
    sfText_setPosition(quit_text, (sfVector2f) { -sfText_getLocalBounds(quit_text).width / 2 + WINDOW_X / 2, 1150 * ratio_x });

    input_main_menu(window, singleplayer_text, multiplayer_text, quit_text, Gsettings, highlight);

    sfRenderWindow_drawRectangleShape(window, highlight, NULL);
    sfRenderWindow_drawText(window, singleplayer_text, NULL);
    sfRenderWindow_drawText(window, multiplayer_text, NULL);
    sfRenderWindow_drawText(window, quit_text, NULL);
    sfRenderWindow_drawText(window, title_text, NULL);
}

void input_main_menu(sfRenderWindow* window, sfText* singlebutton, sfText* multibutton, sfText* quitbutton, struct GameSettings* Gsettings, sfRectangleShape* highlight) {
    sfFloatRect singlerect = sfText_getGlobalBounds(singlebutton);
    sfFloatRect multirect = sfText_getGlobalBounds(multibutton);
    sfFloatRect quitrect = sfText_getGlobalBounds(quitbutton);
    sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
    if (sfFloatRect_intersects(&singlerect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) {singlerect.width + 15, singlerect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(singlebutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = GAME_MODE_MENU;
            Gsettings->singleplayer = true;
        }
    }
    if (sfFloatRect_intersects(&multirect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { multirect.width + 15, multirect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(multibutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = GAME_MODE_MENU;
            Gsettings->singleplayer = false;
        }
    }
    if (sfFloatRect_intersects(&quitrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { quitrect.width + 15, quitrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(quitbutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            sfRenderWindow_close(window);
        }
    }
}

void game_mode_menu(sfRenderWindow* window, sfFont* font, struct GameSettings* Gsettings) {
    float WINDOW_X = sfVideoMode_getDesktopMode().width;
    float ratio_x = WINDOW_X / 2560.0;

    sfRectangleShape* highlight = sfRectangleShape_create();
    sfRectangleShape_setFillColor(highlight, sfColor_fromRGBA((sfUint8)255, (sfUint8)255, (sfUint8)255, (sfUint8)45));

    sfText* title_text = sfText_create();
    sfText_setFont(title_text, font);
    sfText_setString(title_text, "Shotgunnin' Space");
    sfText_setCharacterSize(title_text, 120 * ratio_x);
    sfText_setPosition(title_text, (sfVector2f) { -sfText_getLocalBounds(title_text).width / 2 + WINDOW_X / 2, 50 * ratio_x });

    sfText* subtitle_text = sfText_create();
    sfText_setFont(subtitle_text, font);
    sfText_setString(subtitle_text, "Choose the modifiers:");
    sfText_setCharacterSize(subtitle_text, 90 * ratio_x);
    sfText_setPosition(subtitle_text, (sfVector2f) { -sfText_getLocalBounds(subtitle_text).width / 2 + WINDOW_X / 2, 200 * ratio_x });

    sfText* play_text = sfText_create();
    sfText_setFont(play_text, font);
    sfText_setString(play_text, "Play");
    sfText_setCharacterSize(play_text, 80 * ratio_x);
    sfText_setPosition(play_text, (sfVector2f) { -sfText_getLocalBounds(play_text).width / 2 + 900 * ratio_x, 1250 * ratio_x });

    sfText* return_text = sfText_create();
    sfText_setFont(return_text, font);
    sfText_setString(return_text, "Return");
    sfText_setCharacterSize(return_text, 80 * ratio_x);
    sfText_setPosition(return_text, (sfVector2f) { -sfText_getLocalBounds(return_text).width / 2 + WINDOW_X - 900 * ratio_x, 1250 * ratio_x });

    sfText* infinite_respawn_text = sfText_copy(title_text);
    sfText_setString(infinite_respawn_text, "Infinite Respawn");
    sfText_setCharacterSize(infinite_respawn_text, 50 * ratio_x);
    sfText_setPosition(infinite_respawn_text, (sfVector2f) { -sfText_getLocalBounds(infinite_respawn_text).width / 2 + WINDOW_X / 2 * ratio_x, 900 * ratio_x });
    if (Gsettings->infinite_respawn) sfText_setFillColor(infinite_respawn_text, sfColor_fromRGB((sfUint8)255, (sfUint8)0, (sfUint8)0));

    sfText* autoturn_text = sfText_copy(title_text);
    sfText_setString(autoturn_text, "Auto turn");
    sfText_setCharacterSize(autoturn_text, 50 * ratio_x);
    sfText_setPosition(autoturn_text, (sfVector2f) { -sfText_getLocalBounds(autoturn_text).width / 2 + WINDOW_X / 2 * ratio_x, 800 * ratio_x });
    if (Gsettings->autoturn) sfText_setFillColor(autoturn_text, sfColor_fromRGB((sfUint8)255, (sfUint8)0, (sfUint8)0));

    sfText* nomovement_text = sfText_copy(title_text);
    sfText_setString(nomovement_text, "No thruster");
    sfText_setCharacterSize(nomovement_text, 50 * ratio_x);
    sfText_setPosition(nomovement_text, (sfVector2f) { -sfText_getLocalBounds(nomovement_text).width / 2 + WINDOW_X / 2 * ratio_x, 700 * ratio_x });
    if (Gsettings->no_movement) sfText_setFillColor(nomovement_text, sfColor_fromRGB((sfUint8)255, (sfUint8)0, (sfUint8)0));

    sfText* versus_text = sfText_copy(title_text);
    sfText_setString(versus_text, "Multiplayer only: Versus mode");
    sfText_setCharacterSize(versus_text, 50 * ratio_x);
    sfText_setPosition(versus_text, (sfVector2f) { -sfText_getLocalBounds(versus_text).width / 2 + WINDOW_X / 2 * ratio_x, 400 * ratio_x });
    if (Gsettings->versusmode) sfText_setFillColor(versus_text, sfColor_fromRGB((sfUint8)255, (sfUint8)0, (sfUint8)0));

    sfText* difficulty_text = sfText_create();
    sfText_setFont(difficulty_text, font);
    switch (Gsettings->difficulty)
    {
    case 3:
        sfText_setString(difficulty_text, "Difficulty: hard");
        break;
    case 2:
        sfText_setString(difficulty_text, "Difficulty: medium");
        break;
    case 1:
        sfText_setString(difficulty_text, "Difficulty: easy");
        break;
    default:
        sfText_setString(difficulty_text, "Difficulty: ");
        break;
    }
    sfText_setCharacterSize(difficulty_text, 80 * ratio_x);
    sfText_setPosition(difficulty_text, (sfVector2f) { -sfText_getLocalBounds(difficulty_text).width / 2 + WINDOW_X / 2, 1100 * ratio_x });

    input_game_mode_menu(window, play_text, return_text, difficulty_text,
        infinite_respawn_text, autoturn_text, versus_text, nomovement_text,
        Gsettings, highlight);

    sfRenderWindow_drawRectangleShape(window, highlight, NULL);
    sfRenderWindow_drawText(window, title_text, NULL);
    sfRenderWindow_drawText(window, subtitle_text, NULL);
    sfRenderWindow_drawText(window, play_text, NULL);
    sfRenderWindow_drawText(window, return_text, NULL);
    sfRenderWindow_drawText(window, difficulty_text, NULL);

    sfRenderWindow_drawText(window, infinite_respawn_text, NULL);
    sfRenderWindow_drawText(window, autoturn_text, NULL);
    sfRenderWindow_drawText(window, nomovement_text, NULL);
    if (!Gsettings->singleplayer) sfRenderWindow_drawText(window, versus_text, NULL);
}

void input_game_mode_menu(sfRenderWindow* window, sfText* playbutton, sfText* returnbutton, sfText* difficultybutton,
    sfText* infiniteresbutton, sfText* autoturnbutton, sfText* versusbutton, sfText* nomovementbutton,
    struct GameSettings* Gsettings, sfRectangleShape* highlight) {
    sfFloatRect playrect = sfText_getGlobalBounds(playbutton);
    sfFloatRect returnrect = sfText_getGlobalBounds(returnbutton);
    sfFloatRect difficultyrect = sfText_getGlobalBounds(difficultybutton);
    
    sfFloatRect infiniteresrect = sfText_getGlobalBounds(infiniteresbutton);
    sfFloatRect autoturnrect = sfText_getGlobalBounds(autoturnbutton);
    sfFloatRect versusrect = sfText_getGlobalBounds(versusbutton);
    sfFloatRect nomovementrect = sfText_getGlobalBounds(nomovementbutton);

    sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
    if (sfFloatRect_intersects(&playrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { playrect.width + 15, playrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(playbutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = LAUNCHING;
        }
    }
    if (sfFloatRect_intersects(&returnrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { returnrect.width + 15, returnrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(returnbutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = MAIN_MENU;
        }
    }
    if (sfFloatRect_intersects(&difficultyrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { difficultyrect.width + 15, difficultyrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(difficultybutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            if (!IsButtonPressed(sfMouseLeft)) {
                Gsettings->difficulty += 1;
                if (Gsettings->difficulty > 3) Gsettings->difficulty = 1;
            }
        }
    }

    button_switch(infiniteresrect, mouserect, infiniteresbutton, highlight, &Gsettings->infinite_respawn);
    button_switch(autoturnrect, mouserect, autoturnbutton, highlight, &Gsettings->autoturn);
    button_switch(nomovementrect, mouserect, nomovementbutton, highlight, &Gsettings->no_movement);
    if (!Gsettings->singleplayer) button_switch(versusrect, mouserect, versusbutton, highlight, &Gsettings->versusmode);

}

void gameover_menu(sfRenderWindow* window, sfFont* font, struct GameSettings* GSettings, struct Ship ship, struct Ship ship2) {
    float WINDOW_X = sfVideoMode_getDesktopMode().width;
    float ratio_x = WINDOW_X / 2560;

    sfRectangleShape* highlight = sfRectangleShape_create();
    sfRectangleShape_setFillColor(highlight, sfColor_fromRGBA((sfUint8)255, (sfUint8)255, (sfUint8)255, (sfUint8)45));

    sfText* title_text = sfText_create();
    sfText_setFont(title_text, font);
    if (!GSettings->versusmode) sfText_setString(title_text, "GAME OVER");
    else {
        switch (GSettings->versuswinner)
        {
        case 1:
            sfText_setString(title_text, "PLAYER 1 WIN");
            break;
        case 2:
            sfText_setString(title_text, "PLAYER 2 WIN");
            break;
        }
    }
    sfText_setCharacterSize(title_text, 120 * ratio_x);
    sfText_setPosition(title_text, (sfVector2f) { -sfText_getLocalBounds(title_text).width / 2 + WINDOW_X / 2, 50 * ratio_x });

    sfText* play_text = sfText_create();
    sfText_setFont(play_text, font);
    sfText_setString(play_text, "Play");
    sfText_setCharacterSize(play_text, 80 * ratio_x);
    sfText_setPosition(play_text, (sfVector2f) { -sfText_getLocalBounds(play_text).width / 2 + 800 * ratio_x, 1250 * ratio_x });

    sfText* return_text = sfText_create();
    sfText_setFont(return_text, font);
    sfText_setString(return_text, "Menu");
    sfText_setCharacterSize(return_text, 80 * ratio_x);
    sfText_setPosition(return_text, (sfVector2f) { -sfText_getLocalBounds(return_text).width / 2 + WINDOW_X - 800 * ratio_x, 1250 * ratio_x });

    sfText* quit_text = sfText_create();
    sfText_setFont(quit_text, font);
    sfText_setString(quit_text, "Quit");
    sfText_setCharacterSize(quit_text, 80 * ratio_x);
    sfText_setPosition(quit_text, (sfVector2f) { -sfText_getLocalBounds(quit_text).width / 2 + WINDOW_X /2, 1250 * ratio_x });

    sfText* score1_text = sfText_create();
    sfText_setFont(score1_text, font);
    char score1_char[40];
    snprintf(score1_char, 40, "Score: %d", ship.score);
    sfText_setString(score1_text, score1_char);
    sfText_setCharacterSize(score1_text, 70 * ratio_x);
    sfText_setPosition(score1_text, (sfVector2f) { -sfText_getLocalBounds(score1_text).width / 2 + WINDOW_X / 2, 600 * ratio_x });

    sfText* timer1_text = sfText_create();
    sfText_setFont(timer1_text, font);
    char timer1_char[40];
    snprintf(timer1_char, 40, "Timer: %d Sec", ship.alive_time);
    sfText_setString(timer1_text, timer1_char);
    sfText_setCharacterSize(timer1_text, 70 * ratio_x);
    sfText_setPosition(timer1_text, (sfVector2f) { -sfText_getLocalBounds(score1_text).width / 2 + WINDOW_X / 2, 800 * ratio_x });

    if (!GSettings->singleplayer) {
        sfText* score2_text = sfText_create();
        sfText_setFont(score2_text, font);
        char score2_char[40];
        snprintf(score2_char, 40, "Player 2 score: %d", ship2.score);
        sfText_setString(score2_text, score2_char);
        sfText_setCharacterSize(score2_text, 70 * ratio_x);

        sfText* timer2_text = sfText_create();
        sfText_setFont(timer2_text, font);
        char timer2_char[40];
        if (!GSettings->versusmode) snprintf(timer2_char, 40, "Player 2 timer: %d Sec", ship2.alive_time);
        else {
            if (GSettings->versuswinner == 1) snprintf(timer2_char, 40, "Timer: %d", ship2.alive_time);
            else snprintf(timer2_char, 40, "Timer: %d", ship.alive_time);
        }
        sfText_setString(timer2_text, timer2_char);
        sfText_setCharacterSize(timer2_text, 70 * ratio_x);

        snprintf(score1_char, 40, "Player 1 score: %d", ship.score);
        snprintf(timer1_char, 40, "Player 1 timer: %d Sec", ship.alive_time);
        sfText_setString(score1_text, score1_char);
        sfText_setString(timer1_text, timer1_char);

        sfText_setPosition(timer1_text, (sfVector2f) { -sfText_getLocalBounds(timer1_text).width / 2 + WINDOW_X / 2 - 600, 800 * ratio_x });
        if (!GSettings->versusmode ) sfText_setPosition(timer2_text, (sfVector2f) { -sfText_getLocalBounds(timer2_text).width / 2 + WINDOW_X / 2 + 600, 800 * ratio_x });
        else sfText_setPosition(timer2_text, (sfVector2f) { -sfText_getLocalBounds(timer2_text).width / 2 + WINDOW_X / 2, 800 * ratio_x });

        sfText_setPosition(score1_text, (sfVector2f) { -sfText_getLocalBounds(score1_text).width / 2 + WINDOW_X / 2 - 600 * ratio_x, 600 * ratio_x });
        sfText_setPosition(score2_text, (sfVector2f) { -sfText_getLocalBounds(score2_text).width / 2 + WINDOW_X / 2 + 600 * ratio_x, 600 * ratio_x });

        sfRenderWindow_drawText(window, score2_text, NULL);
        sfRenderWindow_drawText(window, timer2_text, NULL);
    }

    input_gameover_menu(window, play_text, return_text, quit_text, GSettings, highlight);

    sfRenderWindow_drawRectangleShape(window, highlight, NULL);
    sfRenderWindow_drawText(window, title_text, NULL);
    sfRenderWindow_drawText(window, play_text, NULL);
    sfRenderWindow_drawText(window, return_text, NULL);
    sfRenderWindow_drawText(window, quit_text, NULL);
    sfRenderWindow_drawText(window, score1_text, NULL);
    if (!GSettings->versusmode) sfRenderWindow_drawText(window, timer1_text, NULL);
}

void input_gameover_menu(sfRenderWindow* window, sfText* playbutton, sfText* returnbutton, sfText* quitbutton, struct GameSettings* Gsettings, sfRectangleShape* highlight) {
    sfFloatRect playrect = sfText_getGlobalBounds(playbutton);
    sfFloatRect returnrect = sfText_getGlobalBounds(returnbutton);
    sfFloatRect quitrect = sfText_getGlobalBounds(quitbutton);
    sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
    if (sfFloatRect_intersects(&playrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) {playrect.width + 15, playrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(playbutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = LAUNCHING;
        }
    }
    if (sfFloatRect_intersects(&returnrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { returnrect.width + 15, returnrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(returnbutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = MAIN_MENU;
        }
    }
    if (sfFloatRect_intersects(&quitrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { quitrect.width + 15, quitrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(quitbutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            sfRenderWindow_close(window);
        }
    }
}

void pause_menu(sfRenderWindow* window, sfFont* font, struct GameSettings* Gsettings) {
    float WINDOW_X = sfVideoMode_getDesktopMode().width;
    float ratio_x = WINDOW_X / 2560.0;

    sfRectangleShape* highlight = sfRectangleShape_create();
    sfRectangleShape_setFillColor(highlight, sfColor_fromRGBA((sfUint8)255, (sfUint8)255, (sfUint8)255, (sfUint8)45));

    sfText* title_text = sfText_create();
    sfText_setFont(title_text, font);
    sfText_setString(title_text, "PAUSE");
    sfText_setCharacterSize(title_text, 120 * ratio_x);
    sfText_setPosition(title_text, (sfVector2f) { -sfText_getLocalBounds(title_text).width / 2 + WINDOW_X / 2, 50 * ratio_x });

    sfText* play_text = sfText_create();
    sfText_setFont(play_text, font);
    sfText_setString(play_text, "Continue");
    sfText_setCharacterSize(play_text, 80 * ratio_x);
    sfText_setPosition(play_text, (sfVector2f) { -sfText_getLocalBounds(play_text).width / 2 + WINDOW_X / 2 - 300 * ratio_x, 1150 * ratio_x });

    sfText* menu_text = sfText_create();
    sfText_setFont(menu_text, font);
    sfText_setString(menu_text, "Menu");
    sfText_setCharacterSize(menu_text, 80 * ratio_x);
    sfText_setPosition(menu_text, (sfVector2f) { -sfText_getLocalBounds(menu_text).width / 2 + WINDOW_X / 2 + 300 * ratio_x, 1150 * ratio_x });

    sfRectangleShape* cover = sfRectangleShape_create();
    sfRectangleShape_setSize(cover, (sfVector2f) { sfVideoMode_getDesktopMode().width, sfVideoMode_getDesktopMode().height});
    sfRectangleShape_setFillColor(cover, sfColor_fromRGBA((sfUint8)0, (sfUint8)0, (sfUint8)0, (sfUint8)200));

    input_pause_menu(window, play_text, menu_text, Gsettings, highlight);

    sfRenderWindow_drawRectangleShape(window, cover, NULL);
    sfRenderWindow_drawRectangleShape(window, highlight, NULL);
    sfRenderWindow_drawText(window, play_text, NULL);
    sfRenderWindow_drawText(window, menu_text, NULL);
    sfRenderWindow_drawText(window, title_text, NULL);
}

void input_pause_menu(sfRenderWindow* window, sfText* playbutton, sfText* menubutton, struct GameSettings* Gsettings, sfRectangleShape* highlight) {
    sfFloatRect playrect = sfText_getGlobalBounds(playbutton);
    sfFloatRect menurect = sfText_getGlobalBounds(menubutton);
    sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
    if (sfFloatRect_intersects(&playrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { playrect.width + 15, playrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(playbutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = IN_GAME;
        }
    }
    if (sfFloatRect_intersects(&menurect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { menurect.width + 15, menurect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(menubutton));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            Gsettings->menu_states = MAIN_MENU;
        }
    }
}

void button_switch(sfFloatRect buttonrect, sfFloatRect mouserect, sfText* button, sfRectangleShape* highlight, bool* setting_switch) {
    if (sfFloatRect_intersects(&buttonrect, &mouserect, NULL)) {
        sfRectangleShape_setSize(highlight, (sfVector2f) { buttonrect.width + 15, buttonrect.height + 30 });
        sfRectangleShape_setPosition(highlight, sfText_getPosition(button));
        if (sfMouse_isButtonPressed(sfMouseLeft)) {
            if (!IsButtonPressed(sfMouseLeft)) {
                *setting_switch = !*setting_switch;
            }
        }
    }
}