#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <SFML/Window.h>
#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include "Player.h"
#include "Asteroid.h"
#include "Deltatime.h"
#include "ButtonPress.h"

typedef int bool;
#define true 1
#define false 0

int buttons[80];
int buttonslen = 80;

int IsButtonPressed(int button) {
	if (buttons[button] == true) { 
		return true; 
	}
	else { 
		buttons[button] = true; 
		return false; 
	}
}

int ButtonCheck() {
	for (int i = 0; i < buttonslen; i++) {
		if (buttons[i] == true) {
			if (!sfKeyboard_isKeyPressed(i)) {
				buttons[i] = false;
			}
		}
	}
}