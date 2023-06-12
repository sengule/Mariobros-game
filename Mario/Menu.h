#pragma once
#include "Common.h"

class Menu
{
	Text option[2];							//Play and exit options
	Font font;
	int select;

public:
	Menu();
	void draw(RenderWindow& window);
	void up();								//Used after up keypress
	void down();							//Used after down keypress
	int press();							//Returns select
};
