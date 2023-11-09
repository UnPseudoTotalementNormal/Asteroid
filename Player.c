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

void ship_move_toward(struct Ship ship, int delta) {
	float direction_x = cosf(ship.angle * 3.1415 / 180);
	float direction_y = sinf(ship.angle * 3.1415 / 180);
	ship.force.x += ship.speed * direction_x * delta;
	ship.force.y += ship.speed * direction_y * delta;
}

void ship_velocity(struct Ship ship) {
	ship.position.x += ship.force.x;
	ship.position.y += ship.force.y;

	float a_length = sqrt(ship.force.x * ship.force.x + ship.force.y * ship.force.y);
	if (a_length != 0) {
		float normalized_x = ship.force.x / a_length;
		float normalized_y = ship.force.y / a_length;
		if (fabs(ship.force.x) - fabs(ship.decceleration * normalized_x) > 0) {
			ship.force.x -= ship.decceleration * normalized_x;
		}
		else { ship.force.x = 0; }
		if (fabs(ship.force.y) - fabs(ship.decceleration * normalized_y) > 0) {
			ship.force.y -= ship.decceleration * normalized_y;
		}
		else { ship.force.y = 0; }
	}
	else
	{
		ship.force.x = 0;
		ship.force.y = 0;
	}
}