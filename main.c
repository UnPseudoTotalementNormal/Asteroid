#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Vector2_tools.h"
#include "Player.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Deltatime.h"
#include "ButtonPress.h"
#include "Menu.h"

typedef int bool;
#define true 1
#define false 0

void draw_game(sfRenderWindow* window, struct Ship Player, struct Ship Player2, sfFont* font1, struct GameSettings GSettings) {
    sfText* heat_text = sfText_create();
    sfText_setFont(heat_text, font1);
    char heat_char[12];
    snprintf(heat_char, 12, "Heat: %f", Player.heat);
    sfText_setString(heat_text, heat_char);

    sfRenderWindow_drawText(window, Player.text, NULL);
    if (GSettings.singleplayer == false) {
        sfRenderWindow_drawText(window, Player2.text, NULL);
    }
    sfRenderWindow_drawText(window, heat_text, NULL);

    draw_asteroids(window);
    draw_bullets(window);
}

void player_controller(struct Ship* Player1, struct Ship* Player2) {
    if (sfKeyboard_isKeyPressed(sfKeyUp)) {
        ship_move_toward(Player1);
    }
    if (sfKeyboard_isKeyPressed(sfKeyRight)) {
        Player1 -> angle += Player1 -> angle_speed * delta;
    }
    if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
        Player1 -> angle -= Player1 -> angle_speed * delta;
    }
    if (sfKeyboard_isKeyPressed(sfKeySpace) && Player1 -> heat < 100 && Player1 -> overheat == false) {
        if (IsButtonPressed(sfKeySpace) == false) {
            ship_shotgun(Player1);
        }
    }

    if (Player2 != NULL) {
        if (sfKeyboard_isKeyPressed(sfKeyZ)) {
            ship_move_toward(Player2);
        }
        if (sfKeyboard_isKeyPressed(sfKeyD)) {
            Player2->angle += Player2->angle_speed * delta;
        }
        if (sfKeyboard_isKeyPressed(sfKeyQ)) {
            Player2->angle -= Player2->angle_speed * delta;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLShift) && Player2->heat < 100 && Player2->overheat == false) {
            if (IsButtonPressed(sfKeyLShift) == false) {
                ship_shotgun(Player2);
            }
        }
    }
}

void player_functions(struct Ship* Player1, struct Ship* Player2, int WINDOW_X, int WINDOW_Y, struct GameSettings GSettings) {
    ship_movement(Player1);
    ship_oob(Player1, WINDOW_X, WINDOW_Y);
    ship_heat_system(Player1);

    if (asteroid_collision(Player1->position, sfText_getCharacterSize(Player1->text), false) == true || (bullet_to_ship_collision(Player1)) && GSettings.versusmode == true) {
        ship_death(Player1);
    }

    if (Player2 != NULL) {
        ship_movement(Player2);
        ship_oob(Player2, WINDOW_X, WINDOW_Y);
        ship_heat_system(Player2);

        if (asteroid_collision(Player2->position, sfText_getCharacterSize(Player2->text), false) == true || (bullet_to_ship_collision(Player2)) && GSettings.versusmode == true) {
            ship_death(Player2);
        }
    }
}

void launch_game(struct GameSettings GSettings) {
    for (int i = 0; i < GSettings.Nasteroid; i++) {
        create_asteroid(0, 0, 2);
    }
}

void main() {
    srand(time(0));
    InitDelta();

    sfFont* font1 = sfFont_createFromFile("Font/RetroGaming.ttf");

    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    int WINDOW_Y = sfVideoMode_getDesktopMode().height;
    float ratio_x = (float)WINDOW_X / 2560.0;
    float ratio_y = (float)WINDOW_Y / 1440.0;

    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    sfRenderWindow* window = sfRenderWindow_create(mode, "Shotgunnin' space: It's Shotgunnin' time", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 165);

    sfClock* deltaclock = sfClock_create();
    sfClock* animclock = sfClock_create();

    struct GameSettings GSettings = {
        .menu_states = MAIN_MENU,
        .singleplayer = true,
        .Nasteroid = 15,
        .versusmode = false,
        .difficulty = 1,
    };

    struct Ship Player = {
        .position = (sfVector2f) {WINDOW_X / 2, WINDOW_Y / 2},
        .force = (sfVector2f) {0, 0},
        .decceleration = 0.005 * ratio_x,
        .angle = -90,
        .speed = 0.008 * ratio_x,
        .max_speed = 4.0 * ratio_x,
        .angle_speed = 0.5,
        .recoil_force = 7.0 * ratio_x,
        .heat = 0,
        .unheat_speed = 0.0003,
        .overheat = false,
        .unheat_time = 1000,
        .overheat_time = 2500,
        .heat_clock = sfClock_create(),
        .font = sfFont_createFromFile("Font/Ubuntu.ttf"),
        .text = sfText_create(),
    };

    struct Ship Player2 = {
        .position = (sfVector2f) {WINDOW_X / 1.5, WINDOW_Y / 1.5},
        .force = (sfVector2f) {0, 0},
        .decceleration = 0.005 * ratio_x,
        .angle = -90,
        .speed = 0.008 * ratio_x,
        .max_speed = 4.0 * ratio_x,
        .angle_speed = 0.5,
        .recoil_force = 7.0 * ratio_x,
        .heat = 0,
        .unheat_speed = 0.0003,
        .overheat = false,
        .unheat_time = 1000,
        .overheat_time = 2500,
        .heat_clock = sfClock_create(),
        .font = sfFont_createFromFile("Font/Ubuntu.ttf"),
        .text = sfText_create(),
    };

    sfText_setFont(Player.text, Player.font);
    sfText_setString(Player.text, "A");
    sfText_setCharacterSize(Player.text, ratio_x * 125.0);
    sfText_setOrigin(Player.text, (sfVector2f) { sfText_getLocalBounds(Player.text).width / 2, sfText_getLocalBounds(Player.text).height });

    sfText_setFont(Player2.text, Player2.font);
    sfText_setString(Player2.text, "A");
    sfText_setCharacterSize(Player2.text, ratio_x * 125.0);
    sfText_setOrigin(Player2.text, (sfVector2f) { sfText_getLocalBounds(Player2.text).width / 2, sfText_getLocalBounds(Player2.text).height });
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        DeltaTime();

        if (GSettings.singleplayer) {
            player_controller(&Player, NULL);
            player_functions(&Player, NULL, WINDOW_X, WINDOW_Y, GSettings);
        }
        else {
            player_controller(&Player, &Player2);
            player_functions(&Player, &Player2, WINDOW_X, WINDOW_Y, GSettings);
        }
        

        bullet_oob(WINDOW_X, WINDOW_Y);
        move_bullets();
        check_bullets_lifetime();

        asteroid_to_asteroid_collision();
        move_asteroids();
        asteroid_oob(WINDOW_X, WINDOW_Y);

        ////// DRAW /////
        sfRenderWindow_clear(window, sfTransparent);

        switch (GSettings.menu_states)
        {
        case MAIN_MENU:
            main_menu(window, font1, &GSettings);
            break;
        case GAME_MODE_MENU:
            game_mode_menu(window, font1, &GSettings);
            break;
        case IN_GAME:
            draw_game(window, Player, Player2, font1, GSettings);
            break;
        case LAUNCHING:
            launch_game(GSettings);
            GSettings.menu_states = IN_GAME;
            break;
        default:
            GSettings.menu_states = MAIN_MENU;
            break;
        }
        
        sfRenderWindow_display(window);
        /////////////////

        ButtonCheck();
        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit
    }

    sfClock_destroy(deltaclock);
}