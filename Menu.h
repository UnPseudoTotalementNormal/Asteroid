#pragma once

typedef int bool;
#define true 1
#define false 0

struct GameSettings {
	int menu_states;
	bool singleplayer;
	int Nasteroid;
};

enum MENU_STATES
{
	MAIN_MENU,
	GAME_MODE_MENU,
	IN_GAME,
	LAUNCHING,
};

void main_menu(window, font, Gsettings);

void input_main_menu(window, singlebutton, multibutton, quitbutton, Gsettings);

void game_mode_menu(window, font, Gsettings);

void input_game_mode_menu(window, playbutton, returnbutton, Gsettings);