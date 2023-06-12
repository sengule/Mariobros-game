#pragma once
#include "Object.h"


class Turtle :public Object 
{
	float vx;							//Horizontal speed
	float vy;							//Vertical speed 
	Clock clock;						//Used for accelerate turtle

public:
	Turtle(sf::RenderWindow* window);
	void move();						//Moves turtle
	void jump(bool down);				//Makes turtle jump (if down is true, turtle jumps)
	void reset_ATR();					//Reset all attributes after dying/winning game
	void fall(void);					//Makes turtle fall when it dies 
	void setSpeedY(float);				//For onfloor function to reset and set speed
	void surprise(void);
};

