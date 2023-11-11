#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Vector2_tools.h"
#include "Deltatime.h"
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
			bullet_list[i].angle = angle;
			//bullet_list[i].force = 
			sfText_setFont(bullet_list[i].text, bullet_list[i].font);
			sfText_setString(bullet_list[i].text, "I");
			sfText_setCharacterSize(bullet_list[i].text, (float)WINDOW_X * 100.0 / 2560.0);
			sfText_setOrigin(bullet_list[i].text, (sfVector2f) { sfText_getLocalBounds(bullet_list[i].text).width / 2, sfText_getLocalBounds(bullet_list[i].text).height - (WINDOW_X * 12 / 2560) });
			break;
		}
	}
}

void draw_bullets(sfRenderWindow *window) {
	for (int i = 0; i < max_bullet; i++) {
		if (bullet_list[i].text != NULL) {
			sfText_setRotation(bullet_list[i].text, bullet_list[i].angle);
			sfText_setPosition(bullet_list[i].text, bullet_list[i].position);
			sfRenderWindow_drawText(window, bullet_list[i].text, NULL);
		}
	}
}