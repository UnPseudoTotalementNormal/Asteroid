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

void ship_move_toward(struct Ship ship) {
	float direction_x = cosf(ship.angle * 3.1415 / 180);
	float direction_y = sinf(ship.angle * 3.1415 / 180);
	ship.acceleration.x += ship.speed * direction_x;
	ship.acceleration.y += ship.speed * direction_y;
}

void ship_velocity(struct Ship ship) {
	ship.position.x += ship.acceleration.x;
	ship.position.y += ship.acceleration.y;
	if (ship.acceleration.x > 0) {
		ship.acceleration.x -= ship.decceleration;
	}
	else if (ship.acceleration.x < 0) {
		ship.acceleration.x += ship.decceleration;
	}
	if (ship.acceleration.y > 0) {
		ship.acceleration.y -= ship.decceleration;
	}
	else if (ship.acceleration.y < 0) {
		ship.acceleration.y += ship.decceleration;
	}
}