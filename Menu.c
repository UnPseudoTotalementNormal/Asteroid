#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Deltatime.h"
#include "Vector2_tools.h"
#include "Menu.h"

typedef int bool;
#define true 1
#define false 0

void main_menu(sfRenderWindow* window, sfFont* font, struct GameSettings* Gsettings) {
    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    float ratio_x = WINDOW_X / 2560;

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

    sfRenderWindow_drawText(window, singleplayer_text, NULL);
    sfRenderWindow_drawText(window, multiplayer_text, NULL);
    sfRenderWindow_drawText(window, quit_text, NULL);
    sfRenderWindow_drawText(window, title_text, NULL);

    input_main_menu(window, singleplayer_text, multiplayer_text, quit_text, Gsettings);
}

void input_main_menu(sfRenderWindow* window, sfText* singlebutton, sfText* multibutton, sfText* quitbutton, struct GameSettings* Gsettings) {
    sfFloatRect singlerect = sfText_getGlobalBounds(singlebutton);
    sfFloatRect multirect = sfText_getGlobalBounds(multibutton);
    sfFloatRect quitrect = sfText_getGlobalBounds(quitbutton);
    sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
    if (sfFloatRect_intersects(&singlerect, &mouserect, NULL) && sfMouse_isButtonPressed(sfMouseLeft)) {
        Gsettings->menu_states = GAME_MODE_MENU;
        Gsettings->singleplayer = true;
    }
    if (sfFloatRect_intersects(&multirect, &mouserect, NULL) && sfMouse_isButtonPressed(sfMouseLeft)) {
        Gsettings->menu_states = GAME_MODE_MENU;
        Gsettings->singleplayer = false;
    }
    if (sfFloatRect_intersects(&quitrect, &mouserect, NULL) && sfMouse_isButtonPressed(sfMouseLeft)) {
        sfRenderWindow_close(window);
    }
}

void game_mode_menu(sfRenderWindow* window, sfFont* font, struct GameSettings* Gsettings) {
    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    float ratio_x = WINDOW_X / 2560;

    sfText* title_text = sfText_create();
    sfText_setFont(title_text, font);
    sfText_setString(title_text, "Shotgunnin' Space");
    sfText_setCharacterSize(title_text, 120 * ratio_x);
    sfText_setPosition(title_text, (sfVector2f) { -sfText_getLocalBounds(title_text).width / 2 + WINDOW_X / 2, 50 * ratio_x });

    sfText* subtitle_text = sfText_create();
    sfText_setFont(subtitle_text, font);
    sfText_setString(subtitle_text, "Choose the modifiers");
    sfText_setCharacterSize(subtitle_text, 90 * ratio_x);
    sfText_setPosition(subtitle_text, (sfVector2f) { -sfText_getLocalBounds(subtitle_text).width / 2 + WINDOW_X / 2, 200 * ratio_x });

    sfText* play_text = sfText_create();
    sfText_setFont(play_text, font);
    sfText_setString(play_text, "Play");
    sfText_setCharacterSize(play_text, 80 * ratio_x);
    sfText_setPosition(play_text, (sfVector2f) { -sfText_getLocalBounds(play_text).width / 2 + 900 * ratio_x, 1200 * ratio_x });

    sfText* return_text = sfText_create();
    sfText_setFont(return_text, font);
    sfText_setString(return_text, "Return");
    sfText_setCharacterSize(return_text, 80 * ratio_x);
    sfText_setPosition(return_text, (sfVector2f) { -sfText_getLocalBounds(return_text).width / 2 + WINDOW_X - 900 * ratio_x, 1200 * ratio_x });

    sfRenderWindow_drawText(window, title_text, NULL);
    sfRenderWindow_drawText(window, subtitle_text, NULL);
    sfRenderWindow_drawText(window, play_text, NULL);
    sfRenderWindow_drawText(window, return_text, NULL);

    input_game_mode_menu(window, play_text, return_text, Gsettings);
}

void input_game_mode_menu(sfRenderWindow* window, sfText* playbutton, sfText* returnbutton, struct GameSettings* Gsettings) {
    sfFloatRect playrect = sfText_getGlobalBounds(playbutton);
    sfFloatRect returnrect = sfText_getGlobalBounds(returnbutton);
    sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
    if (sfFloatRect_intersects(&playrect, &mouserect, NULL) && sfMouse_isButtonPressed(sfMouseLeft)) {
        Gsettings->menu_states = LAUNCHING;
    }
    if (sfFloatRect_intersects(&returnrect, &mouserect, NULL) && sfMouse_isButtonPressed(sfMouseLeft)) {
        Gsettings->menu_states = MAIN_MENU;
    }
}