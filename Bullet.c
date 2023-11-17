#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Vector2_tools.h"
#include "Deltatime.h"
#include "Asteroid.h"
#include "Player.h"
#include "Menu.h"
#include "Bullet.h"

typedef int bool;
#define true 1
#define false 0

#define max_bullet 30
struct Bullet bullet_list[max_bullet];  

void create_bullet(int WINDOW_X, int WINDOW_Y, sfVector2f position, int angle, int force, struct Ship from, struct GameSettings* GSettings) {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text == NULL || bullet_list[i].dead == true) {
			bullet_list[i].dead = false;
			bullet_list[i].font = sfFont_createFromFile("Font/Ubuntu.ttf");
			bullet_list[i].text = sfText_create();
			bullet_list[i].position = position;
			bullet_list[i].angle = angle + 90;
			bullet_list[i].maxlifetime = 600;
			bullet_list[i].lifetimeclock = sfClock_create();
			bullet_list[i].from = &from;
			float direction_x = cosf(angle * 3.1415 / 180);
			float direction_y = sinf(angle * 3.1415 / 180);
			float bullet_force = (WINDOW_X * (float)force / 2560) / 10;
			bullet_list[i].force = (sfVector2f){ bullet_force * direction_x, bullet_force * direction_y };
			sfText_setFont(bullet_list[i].text, bullet_list[i].font);
			if (GSettings->BULLET_mode) sfText_setString(bullet_list[i].text, "BULLET");
			else sfText_setString(bullet_list[i].text, "I");
			sfText_setCharacterSize(bullet_list[i].text, (float)WINDOW_X * 85.0 / 2560.0);
			sfText_setOrigin(bullet_list[i].text, (sfVector2f) { sfText_getLocalBounds(bullet_list[i].text).width / 2, sfText_getLocalBounds(bullet_list[i].text).height - (WINDOW_X * 12 / 2560) });
			break;
		}
	}
}

void move_bullets() {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text != NULL && bullet_list[i].dead == false) {
			bullet_list[i].position.x += bullet_list[i].force.x * delta;
			bullet_list[i].position.y += bullet_list[i].force.y * delta;
			bullet_list[i].angle += bullet_list[i].angle_speed * delta;
			int asteroid_size_collided = asteroid_collision(bullet_list[i].position, sfText_getCharacterSize(bullet_list[i].text), true);
			if (asteroid_size_collided != 0) {
				bullet_list[i].dead = true;
				bullet_list[i].from->score += 100 * asteroid_size_collided;
			}
		}
	}
}

void check_bullets_lifetime() {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text != NULL && bullet_list[i].dead == false) {
			sfTime lifetime = sfClock_getElapsedTime(bullet_list[i].lifetimeclock);
			int lifetimemilli = sfTime_asMilliseconds(lifetime);
			if (lifetimemilli >= bullet_list[i].maxlifetime) {
				bullet_list[i].dead = true;
			}
		}
	}
}

void draw_bullets(sfRenderWindow *window, struct GameSettings GSettings) {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text != NULL && bullet_list[i].dead == false) {
			if (GSettings.BULLET_mode) sfText_setRotation(bullet_list[i].text, bullet_list[i].angle + 90);
			else sfText_setRotation(bullet_list[i].text, bullet_list[i].angle);
			sfText_setPosition(bullet_list[i].text, bullet_list[i].position);
			sfTime lifetime = sfClock_getElapsedTime(bullet_list[i].lifetimeclock);
			int lifetimemilli = sfTime_asMilliseconds(lifetime);
			sfText_setFillColor(bullet_list[i].text, sfColor_fromRGBA((sfUint8)255, (sfUint8)255, (sfUint8)255, (sfUint8)255 * (1 - (lifetimemilli / bullet_list[i].maxlifetime )) ));
			sfRenderWindow_drawText(window, bullet_list[i].text, NULL);
		}
	}
}

void bullet_oob(limit_x, limit_y) {
	int offset = 40;
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].position.x + bullet_list[i].force.x > limit_x + offset) {
			bullet_list[i].position.x = 0 - offset;
		}
		if (bullet_list[i].position.y + bullet_list[i].force.y > limit_y + offset) {
			bullet_list[i].position.y = 0 - offset;
		}
		if (bullet_list[i].position.x + bullet_list[i].force.x < 0 - offset) {
			bullet_list[i].position.x = limit_x + offset;
		}
		if (bullet_list[i].position.y + bullet_list[i].force.y < 0 - offset) {
			bullet_list[i].position.y = limit_y + offset;
		}
	}
}

int bullet_to_ship_collision(struct Ship ship) {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text != NULL && bullet_list[i].dead == false) {
			float distance_x = bullet_list[i].position.x - ship.position.x;
			float distance_y = bullet_list[i].position.y - ship.position.y;
			float distance = Vector2_length((sfVector2f) { distance_x, distance_y });
			if (distance <= sfText_getCharacterSize(ship.text) / 3 + sfText_getCharacterSize(bullet_list[i].text) / 3) {
				if (bullet_list[i].from != NULL && bullet_list[i].from != &ship) {
					bullet_list[i].dead = true;
					return true;
				}
			}
		}
	}
	return false;
}

void DestroyAllBullets() {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text != NULL) {
			sfText_destroy(bullet_list[i].text);
			sfFont_destroy(bullet_list[i].font);
			sfClock_destroy(bullet_list[i].lifetimeclock);
			bullet_list[i].text = NULL;
		}
	}
}