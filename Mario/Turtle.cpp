#include "Turtle.h"

Turtle::Turtle(sf::RenderWindow* window) : Object(window) 
{
	char buffer[32];

	for (int i = 0; i < 5; i++) 
	{
		sprintf(buffer, "../assets/turtle%d.png", i + 1);
		if (!textures[i].loadFromFile(buffer))
		{
			cout << "turtle " << i << " is not found!" << endl;
			return;
		}
	}

	pos.x = -100 * ((float)WINDOW_WIDTH / 1024); //Turtles start from negative x coordinates and enter the game every few seconds.
	pos.y = 0;
	state = 0;
	vx = 0.0f;
	vy = 0.0f;
	heading = -1;
	sprite.setTexture(textures[state]);
	dieflag = 0; 
	surprise_flag = 0;
	immune_flag = 0;

}

void Turtle::move() 
{


	if (dieflag == 1) 
	{ 
		//If it is 1 , turtle is dead and Turtle::move behaves like Turtle::fall
		fall();
		return;
	}
	if (surprise_flag == 1) 
	{
		surprise();
		return;
	}

	static float anim ; //Used for generate animations in time	
	Time elapsed_time = clock.getElapsedTime(); //Used for accelerate turtle and randomizing

	if (pos.x >= WINDOW_WIDTH) 
	{ 
		//Simple border check, if pos.x >= WW head to left, if if pos.x <= WW head to right
		heading = 1; //Head to left
	}
	if (pos.x <= 0)
	{
		heading = -1; //Head to right
	}

	if (heading == -1) 
	{
		vx = TURTLE_SPEED + elapsed_time.asSeconds()* TURTLE_ACC; // V = V0 + a.t
		if (vx > TURTLE_MAX_SPEED)
		{ 
			//Turtles must have a maximum speed, otherwise the game may become unbeatable as time goes on.
			vx = TURTLE_MAX_SPEED;
		}
	}
	else 
	{
		vx = -TURTLE_SPEED - elapsed_time.asSeconds() * TURTLE_ACC; // V = V0 + a.t
		if (vx < -TURTLE_MAX_SPEED) 
		{ 
			//Turtles must have a maximum speed, otherwise the game may become unbeatable as time goes on.
			vx = -TURTLE_MAX_SPEED;
		}
	}

	if (vx > 0 || vx < 0) 
	{	
		if (anim == 0 || (anim<1 && anim>0)) 
		{ 
			//if 0<=anim<1
			sprite.setTexture(textures[0]);
			sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
			sprite.setScale(-heading * TURTLE_SCALE, TURTLE_SCALE);
			anim+= ANIMATION_TIME;
		}
		else if (anim == 1 || (anim < 2 && anim>1)) 
		{ 
			//if 1<=anim<2
			sprite.setTexture(textures[1]);
			sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
			sprite.setScale(-heading * TURTLE_SCALE, TURTLE_SCALE);
			anim+=ANIMATION_TIME;
		}
		else if (anim >= 2) 
		{ 
			//if anim becames >=2 , sets anim to -1  
			sprite.setTexture(textures[2]); 
			sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
			sprite.setScale(-heading * TURTLE_SCALE, TURTLE_SCALE);
			anim = -1; 

		}
		else
		{ 
			//if  -1<=anim<0, stay with textures[2] (upper loop's texture)
			anim += ANIMATION_TIME;
		}

	}

	pos.x = sprite.getPosition().x; //update pos.x
	pos.y = sprite.getPosition().y; //update pos.y

	/*I use big if else statements for moving turtle
	States in order:
	1-Entering the window and going out of top pipes first time
	2-Dead
	3-Entering and exiting from left pipes
	4-Entering and exiting from right pipes
	5-Walking
	6-In negative coordinates and waiting to enter the game window
	*/

	if (pos.x <= -30 && pos.x >= -40) 
	{ 
		//state = Entering the window 
		//If it's this close to entering the window, come out of the left or right pipetop (random).
		if ((elapsed_time.asMilliseconds()) % 2 == 0) 
		{ 
			//randomizing with elapsed time
			heading = -1;
			sprite.move(vx - pos.x + (scale_WW * 192), (122 * scale_WH) - pos.y); //location of left pipetop
			pos.x = vx + (scale_WW * 192);
		}
		else if ((elapsed_time.asMilliseconds()) % 2 == 1) 
		{
			heading = 1;
			sprite.move(WINDOW_WIDTH - vx - pos.x - (scale_WW * 192), (122 * scale_WH) - pos.y); //location of left pipebot
			pos.x = vx + (scale_WW * 192);		
		}
	}
	else if (pos.y >= WINDOW_HEIGHT + 100) { 
		//turtle is dead, stuck in pos.x=2000 and not on screen
		//With the fall() method the turtle's coordinate is more than 2000 and it gets stuck here
	}
	else if ((pos.x <= 130 * scale_WW && pos.y >= FLOOR_START)) 
	{ 
		//Checking for left pipebot collision, entering it and exiting from left popetop
		heading = -1;
		sprite.move(vx - pos.x + (scale_WW * 192), (122 * scale_WH) - pos.y);
	}
	else if (pos.x >= (WINDOW_WIDTH - 130 * scale_WW) && pos.y >= FLOOR_START) 
	{ 
		//Checking for right pipebot collision, entering it and exiting from right popetop
		heading = 1;
		sprite.move(WINDOW_WIDTH - vx - pos.x - (scale_WW * 192), (122 * scale_WH) - pos.y);
	}
	else if(pos.x>0)
	{ 
		//Standard walking
		jump(down);
		sprite.move(vx, -vy);

	}	
	else 
	{ 
		//There shouldn't be jump() in the negative coordinates
		sprite.move(vx, -vy);
	}
	
	if (immune_flag == 1) 
	{
		static Clock clock3;
		Time time3 = clock3.getElapsedTime();
		if (time3.asSeconds() >= 1.5) 
		{
			clock3.restart();
			immune_flag = 0;
		}
	}
	
}

void Turtle::jump(bool down) 
{
	if (down) 
	{ 
		//If on the floor/brick
		vy = 0.0f;
	}
	else 
	{ 
		//Not on the floor/brick ,falling to down floor/brick
		vy -= GRAVITY * TURTLE_MASS;
	}
}

void Turtle::fall(void) 
{

	if (sprite.getPosition().y >= WINDOW_HEIGHT + 100) 
	{
		//If the pos.y has dropped to 100 pixels below the WINDOW_HEIGHT, it doesn't need to drop any further. It can get stuck at this coordinate.
		return;
	}

	sprite.setTexture(textures[4]); //Fall texture
	sprite.setScale(-heading * TURTLE_SCALE, TURTLE_SCALE);
	vx = 0;
	vy = 3.0f; //Fall speed
	sprite.move(vx,vy);
}

void Turtle::surprise(void) 
{
	cout << "SURPRISE" << endl;
	static 	Clock clock2;
	static bool turtle1_out_flag;
	static bool turtle2_out_flag;

	if (turtle2_out_flag == 1)
	{
		turtle2_out_flag = 0;
		clock2.restart();
	}

	Time time = clock2.getElapsedTime();
	cout << time.asSeconds() <<endl;

	if (turtle1_out_flag==1)
	{
		surprise_flag = 0;
		heading = -heading;
		immune_flag = 1;
		clock2.restart();
		turtle1_out_flag = 0;
		turtle2_out_flag = 1;
	}
	else if (time.asSeconds() >= 2) 
	{
		surprise_flag = 0;
		heading = -heading;
		immune_flag = 1;
		clock2.restart();
		turtle1_out_flag = 1;
	}
	else
	{
		sprite.setTexture(textures[3]);
		sprite.setScale(-heading * TURTLE_SCALE, TURTLE_SCALE);
		vx = 0;
		vy = 0;
		surprise_flag = 1;
	}

}

void Turtle::setSpeedY(float vy) 
{
	this->vy = vy;	//For onfloor function to reset and set speed
}

void Turtle::reset_ATR() 
{
	//Resets attributes and clock
	clock.restart();
	pos.x = -100 * ((float)WINDOW_WIDTH / 1024);
	pos.y = 0;
	state = 0;
	vx = 0.0f;
	vy = 0.0f;
	heading = -1;
	sprite.setTexture(textures[state]);
	dieflag = 0;
	surprise_flag = 0;
	immune_flag = 0;
}
