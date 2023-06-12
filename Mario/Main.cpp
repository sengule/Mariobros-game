#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Common.h"

using namespace std;

int main()
{
    Game game;
    game.window = new RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Mario");

     while (1) 
     {
         game.update();
     }
     
    return 0;
}

