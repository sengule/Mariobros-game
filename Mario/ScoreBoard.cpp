#include "ScoreBoard.h"
#include <sstream>
#include <iomanip>

ScoreBoard::ScoreBoard() 
{
	score = "000000";
    lives = MARIO_LIVES;

    if (!font.loadFromFile("../assets/font.ttf"))
    {
        //error
    }
    
    score_text.setFont(font);
    score_text.setString(score);
    score_text.setFillColor(Color::White);
    score_text.setStyle(Text::Bold);
    score_text.setPosition(Vector2f(WINDOW_WIDTH * 0.2,  0));

    char buffer[32];
    sprintf(buffer, "../assets/mariohead.png");
    if (!texture.loadFromFile(buffer)) 
    {
        cout << "mariohead image is not found!" << endl;
        return;
    }
    sprite.setTexture(texture);
}

void ScoreBoard::setScore(int score) 
{
    //Since the score comes as an int, it is kept as a string in the class, so here is a string to int, int to string conversion.
    int score_int;
    stringstream ss(getScore());
    ss >> score_int;
    score_int += score; //If +=, every score I entered is added directly to the old score (addScore instead of setScore), if =, the score I entered is set.
    ostringstream oss;
    oss << std::setw(6) << std::setfill('0') << score_int; 
    string result = oss.str();
	this->score = result;
    score_text.setString(this->score);
}

void ScoreBoard::setLives(int lives) 
{
	this->lives = lives;
}

int  ScoreBoard::getLives(void) 
{
	return lives;
}

string  ScoreBoard::getScore(void) 
{
    return score;
}


void ScoreBoard::draw(RenderWindow& window)
{
    window.draw(score_text);

    int j = lives;
    while (j > 0) 
    { 
        //Draws current lives
        sprite.setPosition(WINDOW_WIDTH * (0.2 + (j-1)*0.04), sprite.getTexture()->getSize().y * 1.5);
        window.draw(sprite);
        j--;
    }


}

void ScoreBoard::reset_ATR() 
{
    lives = MARIO_LIVES;
    score = "000000";

     if (!font.loadFromFile("../assets/font.ttf"))
     {
            //error
     }

    score_text.setFont(font);
    score_text.setString(score);
    score_text.setFillColor(Color::White);
    score_text.setStyle(Text::Bold);
    score_text.setPosition(Vector2f(WINDOW_WIDTH * 0.2, 0));

    char buffer[32];
    sprintf(buffer, "../assets/mariohead.png");
    if (!texture.loadFromFile(buffer)) {
        cout << "mariohead image is not found!" << endl;
        return;
    }
    sprite.setTexture(texture);
}