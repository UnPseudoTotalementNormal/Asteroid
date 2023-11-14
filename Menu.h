#pragma once

enum MENU_STATES
{
	MAIN_MENU,
	GAME_MODE_MENU,
	IN_GAME
};

int draw_main_menu(window, font);

int input_main_menu(window, singlebutton, multibutton, quitbutton);