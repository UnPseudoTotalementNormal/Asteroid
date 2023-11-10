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

void create_asteroid(WINDOW_X, WINDOW_Y);

void set_asteroid_random_force(i);

void move_asteroids();

void draw_asteroids(window);