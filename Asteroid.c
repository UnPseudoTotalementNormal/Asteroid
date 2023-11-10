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
			break;
		}
	}
}

void draw_all_asteroids(sfRenderWindow *window) {
	for (int i = 0; i < max_asteroid; i++) {
		if (asteroid_list[i].text != NULL) {
			sfText_setPosition(asteroid_list[i].text, asteroid_list[i].position);
			sfRenderWindow_drawText(window, asteroid_list[i].text, NULL);
		}
	}
}