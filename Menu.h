#pragma once

typedef int bool;
#define true 1
#define false 0

struct GameSettings {
	int menu_states;
	int Nasteroid;
	bool singleplayer;
	bool versusmode;
	int versuswinner;
	int difficulty;
	bool infinite_respawn;
};

enum MENU_STATES
{
	MAIN_MENU,
	GAME_MODE_MENU,
	GAMEOVER_MENU,
	IN_GAME,
	LAUNCHING,
	PAUSE,
};

void main_menu(window, font, Gsettings);

void input_main_menu(window, singlebutton, multibutton, quitbutton, Gsettings, highlight);

void game_mode_menu(window, font, Gsettings);

void input_game_mode_menu(window, playbutton, returnbutton, Gsettings);

void gameover_menu(window, font, GSettings, ship, ship2);

void input_gameover_menu(window, playbutton, returnbutton, Gsettings);

void pause_menu(window, font, GSettings);

void input_pause_menu(window, playbutton, menubutton, Gsettings);