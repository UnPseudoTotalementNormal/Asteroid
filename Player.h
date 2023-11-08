#pragma once

struct Ship {
    float x;
    float y;
    float angle;
    float speed;
    sfFont *font;
};

void player_move();