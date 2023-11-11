#pragma once

struct Bullet {
    sfVector2f position;
    sfVector2f force;
    float decceleration;
    float angle;
    float speed;
    float angle_speed;
    int dead;
    sfFont* font;
    sfText* text;
};

void create_bullet(WINDOW_X, WINDOW_Y, position, angle, force);

void draw_bullets(window);