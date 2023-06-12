#include "Game.h"

Game::Game() 
{
	mario = addMario();			//adding mario
	mario->setPosition(mario->pos);

	for (int i = 0; i < TURTLE_NUM; i++) 
	{
		turtle[i] = addTurtle();		//adding turtle
		turtle[i]->pos.x -= 400 * i; //Initially, each turtle's coordinate will be 400 less than the other, so they will be in the game every few seconds.
		turtle[i]->setPosition(turtle[i]->pos);
	}
	
}

void Game::update() 
{

	//MENU
	Menu menu;
	Texture BgTexture;
	if (!BgTexture.loadFromFile("../assets/menubg.png"))
	{

	}

	Sprite background(BgTexture);
	background.setScale((float)WINDOW_WIDTH / background.getTexture()->getSize().x, (float)WINDOW_HEIGHT / background.getTexture()->getSize().y);

	window->draw(background);//If I don't use them before while once, the screen stays white until I hover over the window with the mouse or press a key from the keyboard.
	menu.draw(*window); 
	window->display(); 

	while (window->isOpen()) 
	{
		Event event;

		while (window->pollEvent(event)) 
		{

			switch (event.type)
			{
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Return:
					switch (menu.press())
					{
					case 0: //If play is selected and entered, goto Play_is_pressed pin (start the game)
						goto Play_is_pressed;
						break;
					case 1: //If exit is selected and pressed, close the window
						window->close();
						break;
					}
					break;
				case Keyboard::Up:
					menu.up();
					break;
				case Keyboard::Down:
					menu.down();
					break;
				}
				break;
			case Event::Closed: //Exiting with top right X button 
				window->close();
				break;
			}

			window->clear();
			window->draw(background); //Draws menu background image (Photoshopped jpg image)
			menu.draw(*window);
			window->display();
			sf::sleep(sf::milliseconds(100));
		}
	}

	Play_is_pressed: //goto pin for play button on menu

	//GAME
		while (window->isOpen()) 
		{
			Event event;
			while (window->pollEvent(event)) 
			{
				if (event.type == Event::Closed)
					window->close();
			}

			window->clear();

			Game::drawBackground(*window);

			drawObjects();

			//if mario is in dying state, handling pipe collision, borders and keyboard input is not accepted
			if (mario->getMarioState() != Dying) 
			{
				handlePipeCollision();
				handleBorders();
				handleKeyboardInput(event, mario->getMarioState());
			}
			else 
			{
				mario->respawnMario();
			}

			moveObjects();

			mario->animateMario(mario->getMarioState());

			scoreboard.draw(*window);

			window->draw(bgSprite);
			
			if (scoreboard.getScore() == "000500") 
			{ 
				//If score is 500, display "You win!", wait for one sec, reset the game and return to main(start from menu)
				Font winfont;
				Text wintext;
				string win_str = "You Win!";
				if (!winfont.loadFromFile("../assets/font.ttf"))
				{

				}
				wintext.setFont(winfont);
				wintext.setString(win_str);
				wintext.setFillColor(Color::Green);
				wintext.setStyle(Text::Bold);
				wintext.setPosition(Vector2f(WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.4));
				window->draw(wintext);
				window->display();
				sf::sleep(sf::milliseconds(1000));
				resetGame();
				return;
			}
			

			if (scoreboard.getLives() == 0) 
			{ 
				//If live is 0, display "Game Over!", wait for one sec,  reset the game and return to main(start from menu)
				Font winfont;
				Text wintext;
				string win_str = "Game Over";
				if (!winfont.loadFromFile("../assets/font.ttf"))
				{

				}
				wintext.setFont(winfont);
				wintext.setString(win_str);
				wintext.setFillColor(Color::Red);
				wintext.setStyle(Text::Bold);
				wintext.setPosition(Vector2f(WINDOW_WIDTH * 0.4, WINDOW_HEIGHT * 0.4));
				window->draw(wintext);
				window->display();
				sf::sleep(sf::milliseconds(1000));
				resetGame();
				return;
			}

			window->display();
			sf::sleep(sf::milliseconds(10));
		}
}

void Game::handleBorders(void) 
{

	if (mario->getPosition().x + mario->boundingBox().width * 0.5 >= WINDOW_WIDTH) 
	{
		//Right border of game
		if (mario->getMarioState() != Jumping) mario->setMarioState(Standing);
		mario->setSpeedX(0.0f);
		mario->canPassRight = false;
	}
	else if (mario->getPosition().x - mario->boundingBox().width * 0.5 <= 0) 
	{
		//Left border of game
		if (mario->getMarioState() != Jumping) mario->setMarioState(Standing);
		mario->setSpeedX(0.0f);
		mario->canPassLeft = false;
	}
}

void Game::handlePipeCollision(void) 
{

	if (mario->getMarioState() == Dying) return; // Control statement for game. If mario is dying and also called this method somehow
 
	if (mario->boundingBox().intersects((IntRect)pipebot[0].sprite.getGlobalBounds())) 
	{
		//Left bot pipe
		mario->setMarioState(Standing);
		if (!mario->down) mario->canPassLeft = true;
		else mario->canPassLeft = false;
		mario->setSpeedX(0.0f);
	}
	else if (mario->boundingBox().intersects((IntRect)pipebot[1].sprite.getGlobalBounds())) 
	{
		//Right bot pipe
		mario->setMarioState(Standing);
		if (!mario->down) mario->canPassRight = true;
		else mario->canPassRight = false;
		mario->setSpeedX(0.0f);
	}
	
	if (mario->getPosition().x + mario->boundingBox().width * 0.5 >= pipetop[1].sprite.getGlobalBounds().left &&
		mario->getPosition().y <= 190.0f) 
	{
		//Right top pipe
		if (mario->getMarioState() != Jumping) mario->setMarioState(Standing);
		mario->canPassRight = false;
		mario->setSpeedX(0.0f);
	}
	
	if (mario->getPosition().x - mario->boundingBox().width * 0.5 <= pipetop[0].sprite.getGlobalBounds().left + pipetop[0].sprite.getGlobalBounds().width &&
		mario->getPosition().y <= 190.0f) 
	{
		//Left top pipe
		if (mario->getMarioState() != Jumping) mario->setMarioState(Standing);
		mario->canPassLeft = false;
		mario->setSpeedX(0.0f);
	}

}

void Game::handleKeyboardInput(Event event, MarioState s) 
{
	if (Keyboard::isKeyPressed(Keyboard::Left) && mario->canPassLeft && s != Sliding) 
	{
		//left move
		mario->canPassRight = true;
		mario->setSpeedX(-MARIO_SPEED);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && mario->canPassRight && s != Sliding) 
	{
		//right move
		mario->canPassLeft = true;
		mario->setSpeedX(MARIO_SPEED);
	}

	if (Keyboard::isKeyPressed(Keyboard::Up) && mario->down && mario->canJump) 
	{
		//jump
		mario->setSpeedY(MARIO_JUMP_SPEED);
		mario->down = false;
		mario->canJump = false;
	}

	//When up arrow key is released, mario can jump.
	if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Up) 
	{
		mario->canJump = true;
	}

}

void Game::drawBackground(sf::RenderWindow& window) 
{

	for (int i = 0; i < 76; i++) 
	{ 
		//Scale all bricks
		bricks[i].sprite.setScale(scale_WW, scale_WH); 
	}

	for (int i = 0; i < 76; i++) 
	{ 
		//Setting positions of all bricks
		if (i < 12) bricks[i].setPosition(Vector2f((WINDOW_WIDTH - (i + 1) * bricks[i].sprite.getTexture()->getSize().x * scale_WW), (WINDOW_HEIGHT * 0.712)));
		else if (i < 24) bricks[i].setPosition(Vector2f((i - 12) * bricks[i].sprite.getTexture()->getSize().x * scale_WW, WINDOW_HEIGHT * 0.712));
		else if (i < 28) bricks[i].setPosition(Vector2f(WINDOW_WIDTH - (i - 24 + 1) * bricks[i].sprite.getTexture()->getSize().x * scale_WW, WINDOW_HEIGHT * 0.5677));
		else if (i < 32) bricks[i].setPosition(Vector2f((i - 28) * bricks[i].sprite.getTexture()->getSize().x * scale_WW, WINDOW_HEIGHT * 0.5677));
		else if (i < 48) bricks[i].setPosition(Vector2f((WINDOW_WIDTH / 4) + (i - 32) * bricks[i].sprite.getTexture()->getSize().x * scale_WW, WINDOW_HEIGHT * 0.5175));
		else if (i < 62) bricks[i].setPosition(Vector2f(WINDOW_WIDTH - (i - 48 + 1) * bricks[i].sprite.getTexture()->getSize().x * scale_WW, WINDOW_HEIGHT * 0.3226));
		else if (i < 76) bricks[i].setPosition(Vector2f((i - 62) * bricks[i].sprite.getTexture()->getSize().x * scale_WW, WINDOW_HEIGHT * 0.3226));
	} 

	for (int i = 0; i < 76; i++)
	{
		//Draw all bricks
		bricks[i].draw(&window);
	}

	//BOT PIPES
	pipebot[0].sprite.setScale(scale_WW, scale_WH);
	pipebot[0].setPosition(Vector2f(pipebot[0].sprite.getTexture()->getSize().x * scale_WW, FLOOR_HEIGHT));
	pipebot[0].sprite.setRotation(180.f);
	pipebot[1].sprite.setScale(scale_WW, scale_WH);
	pipebot[1].setPosition(Vector2f(WINDOW_WIDTH - pipebot[1].sprite.getTexture()->getSize().x * scale_WW, FLOOR_HEIGHT - pipebot[1].sprite.getTexture()->getSize().y * scale_WH)); //saðdaki

	for (int i = 0; i < 2; i++) 
	{
		pipebot[i].draw(&window);
	}

	//TOP PIPES
	pipetop[0].sprite.setScale(scale_WW, scale_WH);
	pipetop[0].setPosition(Vector2f(0, WINDOW_HEIGHT * 0.258 - pipetop[0].sprite.getTexture()->getSize().y * scale_WH)); //sol
	pipetop[1].sprite.setScale(scale_WW, scale_WH);
	pipetop[1].sprite.scale(-1.f, 1.f);
	pipetop[1].setPosition(Vector2f(WINDOW_WIDTH, (WINDOW_HEIGHT * 0.258) - pipetop[1].sprite.getTexture()->getSize().y * scale_WH)); //sað

	for (int i = 0; i < 2; i++) 
	{
		pipetop[i].draw(&window);
	}

	//FLOOR
	floor.sprite.setScale(scale_WW, scale_WH);
	floor.setPosition(Vector2f(0, FLOOR_HEIGHT));
	floor.draw(&window);

}

Turtle* Game::addTurtle(void)
{
	//Adding turtle to linked list
	Turtle* turtle = new Turtle(window);
	turtle->next = objects;
	objects = turtle;
	return turtle;
}

Mario* Game::addMario(void)
{
	//Adding mario to linked list
	Mario* mario = new Mario(window);
	mario->next = objects;
	objects = mario;
	return mario;
}

bool Game::onFloor(Object* obj) 
{
	//Create object bounds
	IntRect bounds = obj->boundingBox();

	//Checks object on bricks
	for (int i = 0; i < 76; i++) 
	{
		if (bounds.intersects((IntRect)bricks[i].sprite.getGlobalBounds())) 
		{
			if (bounds.top + bounds.height - (MARIO_MAX_FALL_SPEED + 1) <= (int)bricks[i].sprite.getGlobalBounds().top) 
			{
				
				if (dynamic_cast<Mario*>(obj) != NULL) 
				{

					if (mario->getMarioState() == Jumping) 
					{
						mario->setMarioState(Sliding);
					}

				}
				
				return true;				
			}

		}
	}


	//Checks object on floor
	if (bounds.intersects((IntRect)floor.sprite.getGlobalBounds())) 
	{
		return true;
	}

	return false;
}

bool Game::checkCollusion(Turtle* t, Mario* m, int& side) 
{

	//Creating turtle and mario bounds
	IntRect turtleBounds = t->boundingBox();
	IntRect marioBounds = m->boundingBox();

	//Cheks turtle and mario bounds are intersecting or not
	if (marioBounds.intersects(turtleBounds)) 
	{

		if (marioBounds.top + marioBounds.height - (MARIO_MAX_FALL_SPEED+1) <= turtleBounds.top) 
		{
			//If mario hits turtle from top side
			side = TOP_SIDE;
		}
		else 
		{
			//If mario hits turtle from other sides
			side = 0;
		}

		return true;
	}

	return false;
}

bool Game::checkCollusionT(Turtle* t,Turtle* next) {

	IntRect turtleBounds = t->boundingBox();
	IntRect turtleBoundsN = next->boundingBox();

	if (turtleBounds.intersects(turtleBoundsN) && t->pos.y == next->pos.y && t->heading != next->heading)
	{
		return true;
	}

	return false;
}

void Game::moveObjects(void) 
{
	//Move all objects

	Object* cur = objects;
	while (cur) 
	{
		cur->move();

		if(dynamic_cast<Mario*>(cur) !=  NULL)
			cur->jump(cur->down);

		cur = cur->next;
	}

}

void Game::drawObjects(void)
{
	//Draw all objects and checks their some situations

	Object* cur = objects;
    int lives = scoreboard.getLives();
	while (cur != NULL) 
	{
		cur->draw(*window);

		//Check current object on floor or not
		if (onFloor(cur)) 
		{

			if (dynamic_cast<Mario*>(cur) != NULL && mario->getMarioState() == Dying) 
			{
				
				cur->down = false;
			}
			else 
			{
				cur->setSpeedY(0.0f);
				cur->down = true;
			}

		}
		else 
		{
			if (dynamic_cast<Mario*>(cur) != NULL) 
			{
				if (cur->down != false) cur->setSpeedY(-2);
			}
			cur->down = false;
		}

		//Checking mario and turtle collision
		if (dynamic_cast<Turtle*>(cur) != NULL && cur->dieflag==0 ) 
		{

			//cur is turtle
			int top_side;
			if (checkCollusion((Turtle*)cur, mario, top_side) && mario->getMarioState() != Dying) 
			{

				if (top_side) 
				{
					//turtle falls
					cur->dieflag = 1;
					cur->fall();
					mario->setSpeedY(2);
					scoreboard.setScore(100);
				}
				else 
				{
					//mario falls
					lives--;
					scoreboard.setLives(lives);
					mario->fall();
				}

			}
		}

		if (dynamic_cast<Turtle*>(cur) != NULL && cur->dieflag == 0 && cur->surprise_flag==0 && cur->immune_flag!=1) 
		{
			
			Object* temp = cur;
			while(temp->next!=NULL)
			{
				temp = temp->next;
				if(dynamic_cast<Turtle*>(temp) != NULL && temp->immune_flag != 1 && cur->immune_flag != 1 && cur->surprise_flag == 0 && temp->surprise_flag == 0)
				{
					if (checkCollusionT((Turtle*)cur, (Turtle*)temp)) 
					{
						cur->surprise();
						temp->surprise();				
					}
				}
			}
		}
		cur = cur->next;
	}

}

void Game::resetGame(void) 
{ 
	//Resets the game with reseting turtles,mario and scoreboard

	for (int i = 0; i < TURTLE_NUM; i++) 
	{
		turtle[i]->reset_ATR();
		turtle[i]->pos.x -= 400 * i;
		turtle[i]->setPosition(turtle[i]->pos);

	}

	mario->reset_ATR();
	scoreboard.reset_ATR();
}
