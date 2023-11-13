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

typedef int bool;
#define true 1
#define false 0

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

    for (int i = 0; i < 15; i++) {
        create_asteroid(0, 0, 2);
    }
    
    struct Ship Player = {
        .position = (sfVector2f) {WINDOW_X / 2, WINDOW_Y / 2},
        .force = (sfVector2f) {0, 0},
        .decceleration = 0.005 * ratio_x,
        .angle = -90,
        .speed = 0.008 * ratio_x,
        .max_speed = 4.0 * ratio_x,
        .angle_speed = 0.5,
        .recoil_force = 8.0 * ratio_x,
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
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        DeltaTime();

        player_controller(&Player, NULL);
        ship_movement(&Player);
        ship_oob(&Player, WINDOW_X, WINDOW_Y);
        ship_heat_system(&Player);
        if (asteroid_collision(Player.position, sfText_getCharacterSize(Player.text), false) == true) {
            Player.position.y = WINDOW_Y/2;
            Player.position.x = WINDOW_X/2;
            Player.force = (sfVector2f){ 0, 0 };
        }

        bullet_oob(WINDOW_X, WINDOW_Y);
        move_bullets();
        check_bullets_lifetime();

        asteroid_to_asteroid_collision();
        move_asteroids();
        asteroid_oob(WINDOW_X, WINDOW_Y);

        ////// DRAW /////
        sfText* heat_text = sfText_create();
        sfText_setFont(heat_text, font1);
        char heat_char[12];
        snprintf(heat_char, 12, "Heat: %f", Player.heat);
        sfText_setString(heat_text, heat_char);

        sfRenderWindow_clear(window, sfTransparent);

        sfRenderWindow_drawText(window, Player.text, NULL);
        sfRenderWindow_drawText(window, heat_text, NULL);
        
        draw_asteroids(window);
        draw_bullets(window);

        sfRenderWindow_display(window);
        /////////////////

        ButtonCheck();
        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit
    }

    sfClock_destroy(deltaclock);
}