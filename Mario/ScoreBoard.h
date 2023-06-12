#pragma once
#include "Common.h"

class ScoreBoard 
{
	Texture texture;						//Mariohead texture
	Sprite sprite;							//Mariohead sprite
	Text score_text;						//Score text
	Font font;
	string score;
	int lives;

public:
	void setScore(int score);				//Sets the score, but i coded this method like addScore to make ++100 score operation easier
	void setLives(int lives);	
	int  getLives(void);		
	string getScore(void);
	void draw(RenderWindow& window);
	ScoreBoard();
	void reset_ATR();						//Reset all attributes after dying/winning game
};

