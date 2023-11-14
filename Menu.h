#pragma once

typedef int bool;
#define true 1
#define false 0

struct Game_Settings {
	bool singleplayer;
};

enum MENU_STATES
{
	MAIN_MENU,
	GAME_MODE_MENU,
	IN_GAME
};

int draw_main_menu(window, font);

int input_main_menu(window, singlebutton, multibutton, quitbutton);