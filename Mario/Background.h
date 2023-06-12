#pragma once
#include "Common.h"

class BackGround 
{
// All background object are inherited from this class. They have same attributes and methods except sprite texture
protected:
	Vector2f pos;
	Texture texture;
public:
	Sprite sprite; //I need to use sprite.setscale etc. easily. So i made sprite public
	void setPosition(Vector2f);
	void draw(RenderWindow*);
};

class Brick:public BackGround
{

public:
	Brick(); //All background objects have different constructors because sprite texture loads in constructor
};

class PipeBot:public BackGround 
{

public:
	PipeBot();
};

class PipeTop:public BackGround
{

public:
	PipeTop();
};

class Floor :public BackGround 
{

public:
	Floor();
};




