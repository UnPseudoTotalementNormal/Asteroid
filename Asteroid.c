#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Deltatime.h"
#include "Vector2_tools.h"
#include "Asteroid.h"

typedef int bool;
#define true 1
#define false 0

struct Asteroid asteroid_list[1000];
int max_asteroid = 1000;

void create_asteroid(int WINDOW_X, int WINDOW_Y) {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text == NULL || asteroid_list[i].dead == true) {
			asteroid_list[i].dead = false;
			asteroid_list[i].position.x = (rand() % WINDOW_X);
			asteroid_list[i].position.y = (rand() % WINDOW_Y);
			asteroid_list[i].font = sfFont_createFromFile("Font/Ubuntu.ttf");
			asteroid_list[i].text = sfText_create();
			sfText_setFont(asteroid_list[i].text, asteroid_list[i].font);
			sfText_setString(asteroid_list[i].text, "O");
			sfText_setCharacterSize(asteroid_list[i].text, (float)WINDOW_X * 150.0 / 2560.0);
			sfText_setOrigin(asteroid_list[i].text, (sfVector2f) { sfText_getLocalBounds(asteroid_list[i].text).width / 2, sfText_getLocalBounds(asteroid_list[i].text).height - (WINDOW_X * 12/ 2560) });
			break;
		}
	}
}

void set_asteroid_random_force(int i) {
	float rand_angle = rand() % 360;
	float direction_x = cosf(rand_angle * 3.1415 / 180.0);
	float direction_y = sinf(rand_angle * 3.1415 / 180.0);
	float rand_force = (float)(rand() % 3 + 2) /10.0;
	float rand_angle_speed = (float)(rand() % 6 + 1) / 10.0;
	asteroid_list[i].force = (sfVector2f){ rand_force * direction_x, rand_force * direction_y };
	asteroid_list[i].angle_speed = rand_angle_speed;
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
		if (asteroid_list[i].text != NULL && asteroid_list[i].dead == false) {
			sfText_setRotation(asteroid_list[i].text, asteroid_list[i].angle);
			sfText_setPosition(asteroid_list[i].text, asteroid_list[i].position);
			sfRenderWindow_drawText(window, asteroid_list[i].text, NULL);
		}
	}
}

void asteroid_oob(int limit_x, int limit_y) {
	int offset = 40;
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].position.x + asteroid_list[i].force.x > limit_x + offset) {
			asteroid_list[i].position.x = 0 - offset;
		}
		if (asteroid_list[i].position.y + asteroid_list[i].force.y > limit_y + offset) {
			asteroid_list[i].position.y = 0 - offset;
		}
		if (asteroid_list[i].position.x + asteroid_list[i].force.x < 0 - offset) {
			asteroid_list[i].position.x = limit_x + offset;
		}
		if (asteroid_list[i].position.y + asteroid_list[i].force.y < 0 - offset) {
			asteroid_list[i].position.y = limit_y + offset;
		}
	}
}

int asteroid_collision(sfVector2f collider_position, int collider_size, int lethal) {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text != NULL && asteroid_list[i].dead == false) {
			float distance_x = asteroid_list[i].position.x - collider_position.x;
			float distance_y = asteroid_list[i].position.y - collider_position.y;
			float distance = Vector2_length((sfVector2f) { distance_x, distance_y });
			float asteroid_size = sfText_getLocalBounds(asteroid_list[i].text).width;
			if (distance < (collider_size + asteroid_size) /3) {
				if (lethal == true) {
					asteroid_list[i].dead = false;
				}
				return 1;
			}
		}
	}
	return 0;
}

void asteroid_to_asteroid_collision() {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text != NULL && asteroid_list[i].dead == false) {
			for (int j = 0; j < max_asteroid; j++) {
				if (asteroid_list[j].text != NULL && asteroid_list[j].dead == false && i != j) {
					float distance1_x = (asteroid_list[i].position.x + (asteroid_list[i].force.x * delta)) - (asteroid_list[j].position.x + (asteroid_list[j].force.x * delta));
					float distance1_y = (asteroid_list[i].position.y + (asteroid_list[i].force.y * delta)) - (asteroid_list[j].position.y + (asteroid_list[j].force.y * delta));
					float distance = Vector2_length((sfVector2f) { distance1_x, distance1_y });
					float asteroid1_size = sfText_getLocalBounds(asteroid_list[i].text).width;
					float asteroid2_size = sfText_getLocalBounds(asteroid_list[j].text).width;
					if (distance < (asteroid1_size + asteroid2_size) / 2 ) {
						float distance2_x = (asteroid_list[j].position.x + (asteroid_list[j].force.x * delta)) - (asteroid_list[i].position.x + (asteroid_list[i].force.x * delta));
						float distance2_y = (asteroid_list[j].position.y + (asteroid_list[j].force.y * delta)) - (asteroid_list[i].position.y + (asteroid_list[i].force.y * delta));

						asteroid_list[i].force = (sfVector2f){ 
							Vector2_normalized((sfVector2f) { distance1_x, distance1_y }).x * Vector2_length(asteroid_list[j].force),
							Vector2_normalized((sfVector2f) { distance1_x, distance1_y }).y * Vector2_length(asteroid_list[j].force) };

						asteroid_list[j].force = (sfVector2f){
							Vector2_normalized((sfVector2f) { distance2_x, distance2_y }).x * Vector2_length(asteroid_list[i].force),
							Vector2_normalized((sfVector2f) { distance2_x, distance2_y }).y * Vector2_length(asteroid_list[i].force) };
					}
				}
			}
		}
	}
}