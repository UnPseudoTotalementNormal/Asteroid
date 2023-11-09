#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Player.h"
#include "Deltatime.h"

typedef int bool;
#define true 1
#define false 0

struct Asteroid {
    float x;
    float y;
};

int nframe = 0;
int anim_time = 75; 

void main() {
    srand(time(0));
    InitDelta();

    sfFont* font1 = sfFont_createFromFile("Font/RetroGaming.ttf");

    int WINDOW_X = sfVideoMode_getDesktopMode().width;
    int WINDOW_Y = sfVideoMode_getDesktopMode().height;
    int ratio_x = WINDOW_X * 1 / 2560;
    int ratio_y = WINDOW_Y * 1 / 1440;

    sfVideoMode mode = { WINDOW_X, WINDOW_Y, 32 };

    sfRenderWindow* window = sfRenderWindow_create(mode, "SPOYO", sfFullscreen, NULL);
    sfRenderWindow_setFramerateLimit(window, 165);

    sfClock* deltaclock = sfClock_create();
    sfClock* animclock = sfClock_create();

    struct Ship Player = {
        .position = (sfVector2f) {WINDOW_X / 2, WINDOW_Y / 2},
        .force = (sfVector2f) {0, 0},
        .decceleration = 0.03,
        .angle = -90,
        .speed = 0.01,
        .angle_speed = 0.5,
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
            ship_move_toward(&Player, delta);
        }
        if (sfKeyboard_isKeyPressed(sfKeyRight)) {
            Player.angle += Player.angle_speed * delta;
        }
        if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
            Player.angle -= Player.angle_speed * delta;
        }
        ship_velocity(&Player);

        sfText_setPosition(Player.text, Player.position);
        sfText_setRotation(Player.text, Player.angle + 90);

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) { sfRenderWindow_close(window); } //quit

        ////// DRAW /////
        sfTime atime = sfClock_getElapsedTime(animclock); //for animated frames
        int amseconds = sfTime_asMilliseconds(atime);
        if (amseconds >= anim_time) {
            nframe += 1;
            sfClock_restart(animclock);
        }
        sfRenderWindow_clear(window, sfTransparent);

        sfRenderWindow_drawText(window, Player.text, NULL);

        sfRenderWindow_display(window);
        /////////////////
    }

    sfClock_destroy(deltaclock);
}