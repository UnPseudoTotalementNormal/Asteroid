#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Deltatime.h"
#include "Asteroid.h"

struct Asteroid asteroid_list[100];
int max_asteroid = 100;

void create_asteroid(int WINDOW_X, int WINDOW_Y) {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text == NULL) {
			asteroid_list[i].position.x = (rand() % WINDOW_X);
			asteroid_list[i].position.y = (rand() % WINDOW_Y);
			asteroid_list[i].font = sfFont_createFromFile("Font/Ubuntu.ttf");
			asteroid_list[i].text = sfText_create();
			sfText_setFont(asteroid_list[i].text, asteroid_list[i].font);
			sfText_setString(asteroid_list[i].text, "O");
			sfText_setCharacterSize(asteroid_list[i].text, WINDOW_X * 150 / 2560);
			sfText_setOrigin(asteroid_list[i].text, (sfVector2f) { sfText_getLocalBounds(asteroid_list[i].text).width / 2, sfText_getLocalBounds(asteroid_list[i].text).height - (WINDOW_X * 10/ 2560) });
			break;
		}
	}
}

void set_asteroid_random_force(int i) {
	float rand_angle = rand() % 360;
	float direction_x = cosf(rand_angle * 3.1415 / 180);
	float direction_y = sinf(rand_angle * 3.1415 / 180);
	float rand_force = (rand() % 5 + 2)/10;
	float rand_angle_speed = (float)(rand() % 6 + 1) / 10.0;
	//asteroid_list[i].force = (sfVector2f){ rand_force * direction_x, rand_force * direction_y };
	asteroid_list[i].angle_speed = 2;
}

void move_asteroids() {
	for (int i = 0; i < max_asteroid; i++) {
		asteroid_list[i].position.x += asteroid_list[i].force.x * delta;
		asteroid_list[i].position.y += asteroid_list[i].force.y * delta;
		asteroid_list[i].angle += asteroid_list[i].angle_speed * delta;
	}
}

void draw_asteroids(sfRenderWindow *window) {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text != NULL) {
			sfText_setRotation(asteroid_list[i].text, asteroid_list[i].angle);
			sfText_setPosition(asteroid_list[i].text, asteroid_list[i].position);
			sfRenderWindow_drawText(window, asteroid_list[i].text, NULL);
		}
	}
}