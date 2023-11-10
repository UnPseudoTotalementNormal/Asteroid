#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Player.h"
#include "Asteroid.h"
#include "Deltatime.h"
#include "ButtonPress.h"

typedef int bool;
#define true 1
#define false 0

void main() {
    srand(time(0));
    InitDelta();

    sfFont* font1 = sfFont_createFromFile("Font/RetroGaming.ttf");

    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    int WINDOW_Y = sfVideoMode_getDesktopMode().height;
    int ratio_x = WINDOW_X * 1 / 2560;
    int ratio_y = WINDOW_Y * 1 / 1440;

    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    sfRenderWindow* window = sfRenderWindow_create(mode, "Shotgunnin' space: It's Shotgunnin' time", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 165);

    sfClock* deltaclock = sfClock_create();
    sfClock* animclock = sfClock_create();

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
    sfText_setCharacterSize(Player.text, ratio_x * 125);
    sfText_setOrigin(Player.text, (sfVector2f) { sfText_getLocalBounds(Player.text).width / 2, sfText_getLocalBounds(Player.text).height });
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        DeltaTime();

        //sfText_rotate(Player.text, 1);

        if (sfKeyboard_isKeyPressed(sfKeyUp)) {
            ship_move_toward(&Player);
        }
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            Player.angle += Player.angle_speed * delta;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            Player.angle -= Player.angle_speed * delta;
        }
        if (sfKeyboard_isKeyPressed(sfKeySpace) && Player.heat < 100 && Player.overheat == false) {
            if (IsButtonPressed(sfKeySpace) == false) {
                ship_shotgun(&Player);
            }
        }

        ship_velocity(&Player);
        ship_oob(&Player, WINDOW_X, WINDOW_Y);
        ship_heat_system(&Player);

        sfText_setPosition(Player.text, Player.position);
        sfText_setRotation(Player.text, Player.angle + 90);
        if (Player.overheat == false) {
            sfText_setFillColor(Player.text, sfColor_fromRGB((sfUint8)255, (sfUint8)255 * (1 - Player.heat), (sfUint8)255 * (1 - Player.heat)));
        }
        else {
            sfText_setFillColor(Player.text, sfColor_fromRGB((sfUint8)255, 
                (sfUint8)(255.0) - 255.0 * Player.heat * fabs(sinf(sfTime_asMilliseconds(sfClock_getElapsedTime(Player.heat_clock)) / 200.0)),
                (sfUint8)(255.0) - 255.0 * Player.heat * fabs(sinf(sfTime_asMilliseconds(sfClock_getElapsedTime(Player.heat_clock)) / 200.0 ))));
        }
        

        sfText* heat_text = sfText_create();
        sfText_setFont(heat_text, font1);
        char heat_char[10];
        snprintf(heat_char, 10, "Heat: %f", Player.heat);
        sfText_setString(heat_text ,heat_char);

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit
        ButtonCheck();

        ////// DRAW /////
        sfRenderWindow_clear(window, sfTransparent);

        sfRenderWindow_drawText(window, Player.text, NULL);
        sfRenderWindow_drawText(window, heat_text, NULL);

        sfRenderWindow_display(window);
        /////////////////
    }

    sfClock_destroy(deltaclock);
}