#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Vector2_tools.h"
#include "Deltatime.h"
#include "Asteroid.h"
#include "Bullet.h"

typedef int bool;
#define true 1
#define false 0

struct Bullet bullet_list[100];
int max_bullet = 100;

void create_bullet(int WINDOW_X, int WINDOW_Y, sfVector2f position, int angle, int force) {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text == NULL || bullet_list[i].dead == true) {
			bullet_list[i].dead = false;
			bullet_list[i].font = sfFont_createFromFile("Font/Ubuntu.ttf");
			bullet_list[i].text = sfText_create();
			bullet_list[i].position = position;
			bullet_list[i].angle = angle + 90;
			bullet_list[i].maxlifetime = 600;
			bullet_list[i].lifetimeclock = sfClock_create();
			float direction_x = cosf(angle * 3.1415 / 180);
			float direction_y = sinf(angle * 3.1415 / 180);
			float bullet_force = (WINDOW_X * (float)force / 2560) / 10;
			bullet_list[i].force = (sfVector2f){ bullet_force * direction_x, bullet_force * direction_y };
			sfText_setFont(bullet_list[i].text, bullet_list[i].font);
			sfText_setString(bullet_list[i].text, "I");
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
			if (asteroid_collision(bullet_list[i].position, sfText_getCharacterSize(bullet_list[i].text), true)) {
				bullet_list[i].dead = true;
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

void draw_bullets(sfRenderWindow *window) {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text != NULL && bullet_list[i].dead == false) {
			sfText_setRotation(bullet_list[i].text, bullet_list[i].angle);
			sfText_setPosition(bullet_list[i].text, bullet_list[i].position);
			sfTime lifetime = sfClock_getElapsedTime(bullet_list[i].lifetimeclock);
			int lifetimemilli = sfTime_asMilliseconds(lifetime);
			sfText_setFillColor(bullet_list[i].text, sfColor_fromRGBA((sfUint8)255, (sfUint8)255, (sfUint8)255, (sfUint8)255 * (1 - (lifetimemilli / bullet_list[i].maxlifetime )) ));
			sfRenderWindow_drawText(window, bullet_list[i].text, NULL);
		}
	}
}

void bullet_oob(limit_x, limit_y) {

}