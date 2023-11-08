#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Player.h"

typedef int bool;
#define true 1
#define false 0

void player_move_toward(struct Ship ship) {
	
	float direction_x = cos(ship.angle * 3.1415 / 180);
	float direction_y = sin(ship.angle * 3.1415 / 180);
	ship.position.x += ship.speed * direction_x;
	ship.position.y += ship.speed * direction_y;
}
