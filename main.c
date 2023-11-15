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

void HUD(sfRenderWindow* window, struct Ship Player, struct Ship Player2, sfFont* font1, struct GameSettings GSettings, float WINDOW_X) {
    sfText* life1_text = sfText_create();
    sfText_setFont(life1_text, font1);
    sfText_setCharacterSize(life1_text, WINDOW_X * 50 / 2560);
    char life1_char[12];
    snprintf(life1_char, 12, "Lives: %d", Player.life);
    sfText_setString(life1_text, life1_char);

    sfText* life2_text = sfText_copy(life1_text);
    char life2_char[12];
    snprintf(life2_char, 12, "Lives: %d", Player2.life);
    sfText_setString(life2_text, life2_char);
    sfText_setPosition(life2_text, (sfVector2f){WINDOW_X - sfText_getLocalBounds(life2_text).width, 0});

    sfRenderWindow_drawText(window, life1_text, NULL);
    if (GSettings.singleplayer == false) {
        sfRenderWindow_drawText(window, life2_text, NULL);
    }
}

void draw_game(sfRenderWindow* window, struct Ship Player, struct Ship Player2, sfFont* font1, struct GameSettings GSettings, float WINDOW_X) {
    sfRenderWindow_drawText(window, Player.text, NULL);
    if (GSettings.singleplayer == false) {
        sfRenderWindow_drawText(window, Player2.text, NULL);
    }

    draw_asteroids(window);
    draw_bullets(window);

    HUD(window, Player, Player2, font1, GSettings, WINDOW_X);
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

void player_functions(struct Ship* Player1, struct Ship* Player2, int WINDOW_X, int WINDOW_Y, struct GameSettings *GSettings) {
    if (Player1->dead == false) {
        ship_movement(Player1);
        ship_oob(Player1, WINDOW_X, WINDOW_Y);
        ship_heat_system(Player1);

        if (asteroid_collision(Player1->position, sfText_getCharacterSize(Player1->text), false) || (bullet_to_ship_collision(Player1)) && GSettings->versusmode) {
            ship_death(Player1);
            if (!GSettings->infinite_respawn && Player1->life <= 0) {
                GSettings->menu_states = GAMEOVER_MENU;
            }
        }
    }

    if (Player2 != NULL && Player2->dead == false) {
        ship_movement(Player2);
        ship_oob(Player2, WINDOW_X, WINDOW_Y);
        ship_heat_system(Player2);

        if (asteroid_collision(Player2->position, sfText_getCharacterSize(Player2->text), false) || (bullet_to_ship_collision(Player2)) && GSettings -> versusmode) {
            ship_death(Player2);
            if (!GSettings->infinite_respawn && Player2->life <= 0) {
                GSettings->menu_states = GAMEOVER_MENU;
            }
        }
    }
}

void launch_game(struct GameSettings* GSettings, struct Ship *Player1, struct Ship *Player2, int *spawntimer, int *maxasteroid, int WINDOW_X, int WINDOW_Y) {
    DestroyAllAsteroids();
    ship_death(Player1);
    ship_death(Player2);
    float ratio = (float)WINDOW_X / 2560.0;
    GSettings -> menu_states = IN_GAME;
    Player1->life = 3;
    Player2->life = 3;
    Player1->dead = false;
    Player2->dead = false;
    Player1->position = (sfVector2f){ (float)WINDOW_X / 2.0 - 200 * ratio, WINDOW_Y / 2 };
    Player2->position = (sfVector2f){ (float)WINDOW_X / 2.0 + 200 * ratio, WINDOW_Y / 2 };
    switch (GSettings -> difficulty)
    {
    case 1: //easy
        *spawntimer = 1500;
        *maxasteroid = 20;
        break;
    case 2: //medium
        *spawntimer = 2000;
        *maxasteroid = 25;
        break;
    case 3: //hard
        *spawntimer = 3000;
        *maxasteroid = 30;
        break;
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

    struct GameSettings GSettings = {
        .menu_states = MAIN_MENU,
        .singleplayer = true,
        .Nasteroid = 15,
        .versusmode = false,
        .difficulty = 1,
        .infinite_respawn = false,
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
        .life = 3,
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
        .life = 3,
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
    
    sfClock* AsteroidSpawnerClock = sfClock_create();
    int AsteroidTimeSpawn = 0; 
    int MaxAsteroid = 0;
    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        DeltaTime();

        if (GSettings.singleplayer) {
            player_controller(&Player, NULL);
            player_functions(&Player, NULL, WINDOW_X, WINDOW_Y, &GSettings);
        }
        else {
            player_controller(&Player, &Player2);
            player_functions(&Player, &Player2, WINDOW_X, WINDOW_Y, &GSettings);
        }
        

        bullet_oob(WINDOW_X, WINDOW_Y);
        move_bullets();
        check_bullets_lifetime();

        asteroid_to_asteroid_collision();
        move_asteroids();
        asteroid_oob(WINDOW_X, WINDOW_Y);

        sfTime Asterotime = sfClock_getElapsedTime(AsteroidSpawnerClock);
        if (sfTime_asMilliseconds(Asterotime) > AsteroidTimeSpawn && GetAsteroidCount() < MaxAsteroid && GSettings.menu_states == IN_GAME) {
            sfClock_restart(AsteroidSpawnerClock);
            create_asteroid(0, 0, GSettings.difficulty);
        }

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
        case GAMEOVER_MENU:
            gameover_menu(window, font1, &GSettings);
            break;
        case IN_GAME:
            draw_game(window, Player, Player2, font1, GSettings, WINDOW_X);
            break;
        case LAUNCHING:
            launch_game(&GSettings, &Player, &Player2, &AsteroidTimeSpawn, &MaxAsteroid, WINDOW_X, WINDOW_Y);
            break;
        default:
            GSettings.menu_states = MAIN_MENU;
            break;
        }
        
        sfRenderWindow_display(window);
        /////////////////

        if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
            if (!IsButtonPressed(sfKeyEscape)) {
                if (GSettings.menu_states == IN_GAME) {
                    GSettings.menu_states = GAMEOVER_MENU;
                }
                else {
                    GSettings.menu_states = MAIN_MENU;
                }
            }
        }
        ButtonCheck();
    }
    DestroyAllAsteroids();
    DestroyAllBullets();
    sfRenderWindow_destroy(window);
    sfText_destroy(Player.text);
    sfText_destroy(Player2.text);
    sfClock_destroy(Player.heat_clock);
    sfClock_destroy(Player2.heat_clock);
    sfFont_destroy(Player.font);
    sfFont_destroy(Player2.font);
    sfClock_destroy(AsteroidSpawnerClock);
    sfClock_destroy(deltaclock);
}