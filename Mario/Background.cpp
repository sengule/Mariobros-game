#include "Background.h"

void BackGround::setPosition(Vector2f pos) 
{
	this->pos = pos;
	sprite.setPosition(pos);
}

void BackGround::draw(RenderWindow* window) 
{
	window->draw(sprite);
}

Brick::Brick() 
{
	texture.loadFromFile("../assets/brick.png");
	sprite.setTexture(texture);
}

PipeBot::PipeBot() 
{
	texture.loadFromFile("../assets/pipe.png");
	sprite.setTexture(texture);
}

PipeTop::PipeTop() 
{
	texture.loadFromFile("../assets/pipeS.png");
	sprite.setTexture(texture);
}

Floor::Floor() 
{
	texture.loadFromFile("../assets/floor.png");
	sprite.setTexture(texture);
}



