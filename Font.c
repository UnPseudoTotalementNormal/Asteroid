#include <stdio.h>
#include <stdlib.h>
#include <SFML/Graphics.h>
#include "Font.h"

void create_fonts() {
	font_ubuntu = sfFont_createFromFile("Font/Ubuntu.ttf");
	font_retrogaming = sfFont_createFromFile("Font/RetroGaming.ttf");
}