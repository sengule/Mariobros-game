#include "Menu.h"

Menu::Menu()
{
	if (!font.loadFromFile("../assets/font.ttf"))
	{
		//error
	}

	option[0].setFont(font);
	option[0].setString("Play");
	option[0].setFillColor(Color::Green);
	option[0].setStyle(Text::Bold | Text::Italic);
	option[0].setPosition(Vector2f(WINDOW_WIDTH * 0.4 , WINDOW_HEIGHT/2));

	option[1].setFont(font);
	option[1].setString("Exit");
	option[1].setFillColor(Color::White);
	option[1].setStyle(Text::Bold | Text::Italic);
	option[1].setPosition(Vector2f(WINDOW_WIDTH * 0.4 , 2 * WINDOW_HEIGHT/3)); 

	select = 0;
}


void Menu::draw(RenderWindow& window)
{
	for (int i = 0; i < 2; i++)
	{
		window.draw(option[i]); //Draw texts of two options
	}
}

void Menu::up()
{
	if (select >= 1)
	{
		option[select].setFillColor(Color::White);
		select--;
		option[select].setFillColor(Color::Green); //Play will be selected if exit was selected and it will display as green
	}
}

void Menu::down()
{
	if (select < 1)
	{
		option[select].setFillColor(Color::White);
		select++;
		option[select].setFillColor(Color::Green); //Exit will be selected if play was selected and it will display as green
	}
}

int Menu::press() 
{
	return select; //Basic encapsulation
}

