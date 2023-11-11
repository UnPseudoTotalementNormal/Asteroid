#pragma once

struct Bullet {
    sfVector2f position;
    sfVector2f force;
    float decceleration;
    float angle;
    float speed;
    float angle_speed;
    int dead;
    float maxlifetime;
    sfFont* font;
    sfText* text;
    sfClock* lifetimeclock;
};

void create_bullet(WINDOW_X, WINDOW_Y, position, angle, force);

void move_bullets();

void check_bullets_lifetime();

void draw_bullets(window);