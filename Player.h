#pragma once

struct Ship {
    sfVector2f position;
    float angle;
    float speed;
    sfFont *font;
    sfText *text;
};

void player_move_toward(Ship);