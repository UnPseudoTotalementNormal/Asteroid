#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/System.h>
#include "ButtonPress.h"

typedef int bool;
#define true 1
#define false 0

int buttons[100];
int buttonslen = 100;

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