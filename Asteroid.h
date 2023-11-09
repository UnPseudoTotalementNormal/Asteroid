#pragma once

struct Asteroid {
    sfVector2f position;
    sfVector2f force;
    float decceleration;
    float angle;
    float speed;
    float angle_speed;
    sfFont* font;
    sfText* text;
};