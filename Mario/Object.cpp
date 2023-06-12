#include "Object.h"

Object::Object(sf::RenderWindow* window) 
{
	state = 0;
	heading = 0;
	next = NULL;
}

//setter for pos attribute
void Object::setPosition(sf::Vector2f pos) 
{
	this->pos = pos;
	sprite.setPosition(pos);
}

//getter for pos attribute
Vector2f Object::getPosition() 
{
	return sprite.getPosition();
}

//bounding box of an object
IntRect Object::boundingBox(void) 
{
	IntRect boundingBox = (IntRect) sprite.getGlobalBounds();
	return boundingBox;
}

void Object::draw(sf::RenderWindow& window) 
{
	window.draw(sprite);
}

void Object::move(void) 
{

}

void Object::fall(void) 
{

}

void Object::jump(bool down) 
{

}

//setter for y-axis speed
void Object::setSpeedY(float vy) 
{

}

//setter for x-axis speed
void Object::setSpeedX(float vx) 
{

}

void Object::reset_ATR() 
{

}

void Object::surprise() 
{

}
