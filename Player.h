#pragma once

struct Ship {
    sfVector2f position;
    sfVector2f force;
    float decceleration;
    float angle;
    float speed;
    float max_speed;
    float angle_speed;
    float recoil_force;
    float heat;
    float unheat_speed;
    int overheat;
    float unheat_time;
    float overheat_time;
    sfClock* heat_clock;
    sfClock* alive_clock;
    int alive_time;
    int life;
    int dead;
    int score;
    sfFont *font;
    sfText *text;
};

void ship_move_toward(ship);

void ship_add_single_force(ship, angle, force);

void ship_movement(ship);

void ship_shotgun(ship);

void ship_heat_system(ship);

void ship_oob(ship, limit_x, limit_y);

void ship_death(ship);