#pragma once

typedef int bool;
#define true 1
#define false 0

struct GameSettings {
	int menu_states;
	int Nasteroid;
	int versuswinner;
	int difficulty;

	//modifiers//
	bool singleplayer;
	bool versusmode;
	bool autoturn;
	bool no_movement;
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

void input_game_mode_menu(window, playbutton, returnbutton, Gsettings, highlight);

void gameover_menu(window, font, GSettings, ship, ship2);

void input_gameover_menu(window, playbutton, returnbutton, Gsettings, highlight);

void pause_menu(window, font, GSettings);

void input_pause_menu(window, playbutton, menubutton, Gsettings, highlight);