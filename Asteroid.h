#pragma once

struct Asteroid {
    sfVector2f position;
    sfVector2f force;
    float decceleration;
    float angle;
    float speed;
    float angle_speed;
    int dead;
    int size;
    sfFont* font;
    sfText* text;
};

void create_asteroid(WINDOW_X, WINDOW_Y);

void set_asteroid_random_force(i);

void move_asteroids();

void draw_asteroids(window);

void asteroid_oob(limit_x, limit_y);

int asteroid_collision(collider_position, collider_size, lethal);

void asteroid_to_asteroid_collision();

void asteroid_death(i);

int GetAsteroidCount();

void DestroyAllAsteroids();