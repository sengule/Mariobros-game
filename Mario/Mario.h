#pragma once
#include "Object.h"

enum MarioState 
{
	Standing,
	MovingRight,
	MovingLeft,
	RunningRight,
	RunningLeft,
	Jumping,
	Sliding,
	Dying
};


class Mario: public Object
{
	float vx;									//Horizontal speed
	float vy;									//Vertical speed 

	//Additional attributes
	MarioState marioState;						//Holds mario current state
	Clock clock;
	Time elapsedTime;

public:
	bool canPassLeft;							//restriction for left movement for borders and to make easy collision mechanic
	bool canPassRight;							//restriction for right movement for borders and to make easy collision mechanic
	bool canJump;

	Mario(sf::RenderWindow* window);			//Constructor
	void move();								//Moves Mario left or right
	void jump(bool down);						//Makes Mario jump (if down is true, Mario jumps
												//down off the edge of a floor, otherwise he jumps
												//up)
	void fall(void);							//Makes Mario fall straight down when he dies

	//Additional attributes		
	void setSpeedY(float);						//Setter for y-axis speed
	void setSpeedX(float);						//Setter for x-axis speed
	MarioState getMarioState(void);				//Getter for mario state
	void setMarioState(MarioState);				//Setter for mario state
	void animateMario(MarioState);				//To animate the mario
	void respawnMario();						//To respawn the mario
	void reset_ATR();
};
