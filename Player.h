#pragma once

struct Ship {
    sfVector2f position;
    sfVector2f force;
    float decceleration;
    float angle;
    float speed;
    float max_speed;
    float angle_speed;
    sfFont *font;
    sfText *text;
};

void ship_move_toward(ship);

void ship_velocity(ship);