#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Vector2_tools.h"
#include "Player.h"
#include "Bullet.h"
#include "Menu.h"
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

void ship_movement(struct Ship ship) {
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

	sfText_setPosition(ship.text, ship.position);
	sfText_setRotation(ship.text, ship.angle + 90);
}

void ship_shotgun(struct Ship ship, struct GameSettings* GSettings) {
	ship.heat += 0.20;
	sfClock_restart(ship.heat_clock);
	ship_add_single_force(&ship, (int)ship.angle, (int)ship.recoil_force);
	int WINDOW_X = sfVideoMode_getDesktopMode().width;
	int WINDOW_Y = sfVideoMode_getDesktopMode().height;
	create_bullet(WINDOW_X, WINDOW_Y, ship.position, (int)(ship.angle), 8, &ship, GSettings);
	create_bullet(WINDOW_X, WINDOW_Y, ship.position, (int)(ship.angle + 25), 8, &ship, GSettings);
	create_bullet(WINDOW_X, WINDOW_Y, ship.position, (int)(ship.angle - 25), 8, &ship, GSettings);
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

	if (ship.overheat == false) {
		sfText_setFillColor(ship.text, sfColor_fromRGB((sfUint8)255, (sfUint8)255 * (1 - ship.heat), (sfUint8)255 * (1 - ship.heat)));
	}
	else {
		sfText_setFillColor(ship.text, sfColor_fromRGB((sfUint8)255,
			(sfUint8)(255.0) - 255.0 * ship.heat * fabs(sinf(sfTime_asMilliseconds(sfClock_getElapsedTime(ship.heat_clock)) / 200.0)),
			(sfUint8)(255.0) - 255.0 * ship.heat * fabs(sinf(sfTime_asMilliseconds(sfClock_getElapsedTime(ship.heat_clock)) / 200.0))));
	}
}

void ship_oob(struct Ship ship, int limit_x, int limit_y) {
	float offset = limit_x * 40.0 / 2560.0;
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

void ship_death(struct Ship ship) {
	int WINDOW_X = sfVideoMode_getDesktopMode().width;
	int WINDOW_Y = sfVideoMode_getDesktopMode().height;
	ship.position.y = WINDOW_Y / 2;
	ship.position.x = WINDOW_X / 2;
	ship.force = (sfVector2f){ 0, 0 };
	ship.heat = 0;
	ship.overheat = false;
	ship.life -= 1;
	ship.angle = -90;
	sfTime time = sfClock_getElapsedTime(ship.alive_clock);
	ship.alive_time = sfTime_asSeconds(time);
	if (ship.life <= 0 && ship.dead != true) {
		ship.dead = true;
	}
}
