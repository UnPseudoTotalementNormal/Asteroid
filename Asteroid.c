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

#define max_asteroid 200
struct Asteroid asteroid_list[max_asteroid];

void create_asteroid(int x, int y, int size) {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text == NULL || asteroid_list[i].dead == true) {
			int WINDOW_X = sfVideoMode_getDesktopMode().width;
			int WINDOW_Y = sfVideoMode_getDesktopMode().height;
			asteroid_list[i].dead = false;
			asteroid_list[i].position.x = x;
			asteroid_list[i].position.y = y;
			if (x == 0 && y == 0) {
				switch (rand() % 2)
				{
				case 0:
					asteroid_list[i].position.x = (rand() % WINDOW_X);
					asteroid_list[i].position.y = -100;
					break;
				case 1:
					asteroid_list[i].position.x = -100;
					asteroid_list[i].position.y = (rand() % WINDOW_Y);
					break;
				}
			}
			asteroid_list[i].font = sfFont_createFromFile("Font/Ubuntu.ttf");
			asteroid_list[i].text = sfText_create();
			sfText_setFont(asteroid_list[i].text, asteroid_list[i].font);
			asteroid_list[i].size = size;
			switch (size)
			{
			case 1:
				sfText_setString(asteroid_list[i].text, "o");
				sfText_setCharacterSize(asteroid_list[i].text, (float)WINDOW_X * 100.0 / 2560.0);
				sfText_setOrigin(asteroid_list[i].text, (sfVector2f) { sfText_getLocalBounds(asteroid_list[i].text).width / 2, sfText_getLocalBounds(asteroid_list[i].text).height - (WINDOW_X * -25 / 2560) });
				break;
			case 2:
				sfText_setString(asteroid_list[i].text, "O");
				sfText_setCharacterSize(asteroid_list[i].text, (float)WINDOW_X * 150.0 / 2560.0);
				sfText_setOrigin(asteroid_list[i].text, (sfVector2f) { sfText_getLocalBounds(asteroid_list[i].text).width / 2, sfText_getLocalBounds(asteroid_list[i].text).height - (WINDOW_X * 15 / 2560) });
				break;
			case 3:
				sfText_setString(asteroid_list[i].text, "O");
				sfText_setCharacterSize(asteroid_list[i].text, (float)WINDOW_X * 200.0 / 2560.0);
				sfText_setOrigin(asteroid_list[i].text, (sfVector2f) { sfText_getLocalBounds(asteroid_list[i].text).width / 2, sfText_getLocalBounds(asteroid_list[i].text).height - (WINDOW_X * 20 / 2560) });
			}
			set_asteroid_random_force(i);
			break;
		}
	}
}

void set_asteroid_random_force(int i) {
	float rand_angle = (rand() % 36000) / 100.0;
	if ((int)rand_angle % 90 < 20) {
		set_asteroid_random_force(i);
		return;
	}
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
	int offset;
	for (int i = 0; i < max_asteroid; i++) {
		switch (asteroid_list[i].size)
		{
		case 3:
			offset = 90;
			break;
		case 2:
			offset = 60;
			break;
		default:
			offset = 80;
			break;
		}
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
					asteroid_death(i);
				}
				return 1;
			}
		}
	}
	return 0;
}

void asteroid_death(int i) {
	asteroid_list[i].dead = true;
	asteroid_list[i].size -= 1;
	
	if (asteroid_list[i].size > 0) {
		create_asteroid(asteroid_list[i].position.x - 50, asteroid_list[i].position.y, asteroid_list[i].size);
		create_asteroid(asteroid_list[i].position.x + 50, asteroid_list[i].position.y, asteroid_list[i].size);
	}
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

int GetAsteroidCount() {
	int count = 0;
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text != NULL && asteroid_list[i].dead == false) {
			count += 1;
		}
	}
	return count;
}

void DestroyAllAsteroids() {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text != NULL) {
			sfText_destroy(asteroid_list[i].text);
			sfFont_destroy(asteroid_list[i].font);
			asteroid_list[i].text = NULL;
		}
	}
}