#pragma once
#include "Common.h"

class Object
{
	Object* next;
	friend class Game;

protected:
	Texture textures[8];						//Textures of Object (there are 8 textures total for Mario and 6 textures for Turtle)	
	Sprite sprite;								//Sprite for the object
	Vector2f pos;								//Current position of object on screen
	RenderWindow* window;						//Pointer to render window
	int state;									//Current animation state of the object (one of animation states)
	int heading;								//Facing direction of object

	//Additional attributes
	bool down;									//to check object is jumping or not

	bool dieflag;
	bool surprise_flag;
	bool immune_flag;

public:
	Object(sf::RenderWindow* window);			//Constructor
	void setPosition(sf::Vector2f pos);			//Sets position of the object
	Vector2f getPosition();					    //Gets position of the object
	IntRect boundingBox(void);				    //Returns the bounding rectangle of the object texture
	void draw(sf::RenderWindow& window);		//Draws current the object texture to screen
	virtual void move(void);					//Abstract method that will be overridden
	void fall(void);							//Abstract method that will be overridden
	virtual void jump(bool down);				//Abstract method that will be overridden

	//Additional attributes
	virtual void setSpeedY(float);				//Abstract method to set y-axis speed of object
	virtual void setSpeedX(float);				//Abstract method to set x-axis speed of object
	virtual void reset_ATR();
	virtual void surprise(void);
};

