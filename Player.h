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

void ship_move_toward(ship, delta);

void ship_velocity(ship);

void ship_oob(ship, limit_x, limit_y);