#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Vector2_tools.h"
#include "Player.h"
#include "Bullet.h"
#include "Deltatime.h"

typedef int bool;
#define true 1
#define false 0

void ship_move_toward(struct Ship ship) {
	float direction_x = cosf(ship.angle * 3.1415 / 180);
	float direction_y = sinf(ship.angle * 3.1415 / 180);
	if (fabs(ship.force.x + ship.speed * direction_x * delta) < fabs(ship.max_speed * direction_x)) {
		ship.force.x += ship.speed * direction_x * delta;
	}
	if (fabs(ship.force.y + ship.speed * direction_y * delta) < fabs(ship.max_speed * direction_y)) {
		ship.force.y += ship.speed * direction_y * delta;
	}
}

void ship_add_single_force(struct Ship *ship, int angle, int force) {
	float direction_x = cosf((angle + 180) * 3.1415 / 180);
	float direction_y = sinf((angle + 180) * 3.1415 / 180);
	ship -> force.x += force * direction_x;
	ship -> force.y += force * direction_y;
 }

void ship_velocity(struct Ship ship) {
	ship.position.x += ship.force.x;
	ship.position.y += ship.force.y;

	float a_length = Vector2_length(ship.force);
	if (a_length != 0) {
		float normalized_x = Vector2_normalized(ship.force).x;
		float normalized_y = Vector2_normalized(ship.force).y;
		if (fabs(ship.force.x) - fabs(ship.decceleration * normalized_x) > 0) {
			ship.force.x -= (ship.decceleration * delta) * normalized_x;
		}
		else { ship.force.x = 0; }
		if (fabs(ship.force.y) - fabs(ship.decceleration * normalized_y) > 0) {
			ship.force.y -= (ship.decceleration * delta) * normalized_y;
		}
		else { ship.force.y = 0; }
	}
	else
	{
		ship.force.x = 0;
		ship.force.y = 0;
	}
}

void ship_shotgun(struct Ship ship) {
	ship.heat += 0.25;
	sfClock_restart(ship.heat_clock);
	ship_add_single_force(&ship, (int)ship.angle, (int)ship.recoil_force);
	int WINDOW_X = sfVideoMode_getDesktopMode().width;
	int WINDOW_Y = sfVideoMode_getDesktopMode().height;
	create_bullet(WINDOW_X, WINDOW_Y, ship.position, (int)(ship.angle + 90), 1);
}

void ship_heat_system(struct Ship ship) {
	sfTime heat_time = sfClock_getElapsedTime(ship.heat_clock);
	int heat_milliseconds = sfTime_asMilliseconds(heat_time);
	if ((heat_milliseconds >= ship.unheat_time && !ship.overheat) || (heat_milliseconds >= ship.overheat_time && ship.overheat)) {
		if (ship.heat > 0) {
			ship.heat -= ship.unheat_speed * delta;
		}
		else {
			ship.heat = 0;
			ship.overheat = false;
		}
	}

	if (ship.heat >= 1) {
		ship.heat = 1;
		ship.overheat = true;
	}

}

void ship_oob(struct Ship ship, int limit_x, int limit_y) {
	int offset = 40;
	if (ship.position.x + ship.force.x > limit_x + offset) {
		ship.position.x = 0 - offset;
	}
	if (ship.position.y + ship.force.y > limit_y + offset) {
		ship.position.y = 0 - offset;
	}
	if (ship.position.x + ship.force.x < 0 - offset) {
		ship.position.x = limit_x + offset;
	}
	if (ship.position.y + ship.force.y < 0 - offset) {
		ship.position.y = limit_y + offset;
	}
}