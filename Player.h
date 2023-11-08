#pragma once

struct Ship {
    sfVector2f position;
    float angle;
    float speed;
    float angle_speed;
    sfFont *font;
    sfText *text;
};

void player_move_toward(Ship);