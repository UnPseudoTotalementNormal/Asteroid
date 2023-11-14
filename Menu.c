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



int draw_main_menu(sfRenderWindow* window, sfFont* font) {
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

    return input_main_menu(window, singleplayer_text, multiplayer_text, quit_text);
}

int input_main_menu(sfRenderWindow* window, sfText* singlebutton, sfText* multibutton, sfText* quitbutton) {
    sfFloatRect singlerect = sfText_getGlobalBounds(singlebutton);
    sfFloatRect multirect = sfText_getGlobalBounds(multibutton);
    sfFloatRect quitrect = sfText_getGlobalBounds(quitbutton);
    sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
    if (sfFloatRect_intersects(&singlerect, &mouserect, NULL) == true) {
        return IN_GAME;
    }
    return MAIN_MENU;
}