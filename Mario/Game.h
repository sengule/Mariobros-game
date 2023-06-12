#pragma once

#include "Common.h"
#include "Mario.h"
#include "Turtle.h"
#include "Background.h"
#include "Menu.h"
#include "ScoreBoard.h"
class Game 
{
	Texture bgTexture;
	Sprite bgSprite;
	Brick bricks[76];
	PipeBot pipebot[2];
	PipeTop pipetop[2];
	Floor floor;
	Mario* mario;
	Turtle* turtle[TURTLE_NUM];
	Object* objects;
	ScoreBoard scoreboard;
public:
	Game();
	RenderWindow* window;

	void drawBackground(sf::RenderWindow& window);			//Draws the background objects
	bool onFloor(Object* obj);								 //Checks if object is touching a
															//floor surface

	bool checkCollusion(Turtle* t, Mario* m, int& side);	//Checks if Mario has hit a turtle and from which side

	//Additional Methods
	void update();											//Updates game 
	Turtle* addTurtle(void);								//To add turtle to the game
	Mario* addMario(void);									//To add mario to the game
	void drawObjects(void);									//To draw all objects in the game
	void moveObjects(void);									//To move all object in the game
	bool checkCollusionT(Turtle* t, Turtle* next);			// To check turtle-turtle collision
	void handlePipeCollision(void);							//To check mario if hit a pipe or not
	void handleKeyboardInput(Event, MarioState);			//Handling keyboard inputs
	void handleBorders(void);								//To check mario hit a border or not

	void resetGame(void);									//To reset game
};

