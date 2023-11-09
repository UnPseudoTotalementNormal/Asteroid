#pragma once

struct Ship {
    sfVector2f position;
    sfVector2f velocity;
    sfVector2f acceleration;
    float decceleration;
    float angle;
    float speed;
    float angle_speed;
    sfFont *font;
    sfText *text;
};

void ship_move_toward(ship);

void ship_velocity(ship);