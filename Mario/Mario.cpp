#include "Mario.h"
#include "Object.h"

Mario::Mario(sf::RenderWindow* window) : Object(window) 
{
	
	//Set textures to texture array
	char buffer[64];
	for (int i = 0; i < 7; i++) 
	{
		sprintf(buffer, "../assets/mario%d.png", i + 1);
		if (!textures[i].loadFromFile(buffer)) 
		{
			cout << "mario " << i << " is not found!" << endl;
			return;
		}
	}

	//Initializing some attributes
	pos.x = WINDOW_WIDTH/2;
	pos.y = 470;
	state = 0;
	heading = -1;
	vx = 0.0f;
	vy = 0.0f;
	marioState = Standing;
	down = true;
	canPassLeft = true;
	canPassRight = true;
	canJump = true;
	sprite.setTexture(textures[state]);
	elapsedTime = clock.restart();
}

void Mario::move() 
{

	if (marioState == Sliding) return;
	else clock.restart();

	if (vx < 0) 
	{
		//left movement
		heading = -1;

		//State machine for left movement
		if (marioState == Standing) 
		{
			marioState = MovingLeft;
		}
		else if (marioState == MovingLeft) 
		{
			marioState = RunningLeft;
		}
		else if (marioState == MovingRight) 
		{
			marioState = Standing;
		}
		else if (marioState == RunningRight) 
		{
			marioState = Sliding;
			heading = 1;
		}

	}
	else if (vx > 0) 
	{
		//right movement
		heading = +1;

		//State machine for right movement
		if (marioState == Standing) 
		{
			marioState = MovingRight;
		}
		else if (marioState == MovingRight) 
		{
			marioState = RunningRight;
		}
		else if (marioState == MovingLeft) 
		{
			marioState = Standing;
		}
		else if (marioState == RunningLeft) 
		{
			marioState = Sliding;
			heading = -1;
		}

	}
	else if (down && marioState != Sliding) 
	{
		marioState = Standing;
	}

	sprite.move(vx, -vy);
	if (down) vx = 0.0f;
}

void Mario::animateMario(MarioState s) 
{

	//Mario is always in jumping state when y-axis speed is not zero if he is not in dying state 
	if (vy != 0 && this->marioState != Dying) 
	{
		marioState = Jumping;
	}

	static float anim_gen = 1; // to create run animation

	//Switch case statement to decide state corresponding marioState
	switch (s) 
	{
	case Standing:
		state = 0;
		break;
	case MovingRight:
		state = 1;
		break;
	case MovingLeft:
		state = 1;
		break;
	case RunningRight:
		anim_gen += 0.1 * ELAPSED_TIME + MARIO_ANIMATION;
		state = anim_gen;
		if (state > 3) 
		{
			state = 1;
			anim_gen = 1;
		}
		break;
	case RunningLeft:
		anim_gen += 0.1 * ELAPSED_TIME + MARIO_ANIMATION;
		state = anim_gen;
		if (state > 3) 
		{
			state = 1;
			anim_gen = 1;
		}
		break;
	case Jumping:
		state = 5;
		break;
	case Sliding:
		state = 4;
		elapsedTime = clock.getElapsedTime();

		if (heading == -1) vx = -MARIO_SLIDE_SPEED;
		else if (heading == 1) vx = MARIO_SLIDE_SPEED;

		if (elapsedTime.asSeconds() > MARIO_SLIDE_TIME) 
		{
			marioState = Standing;
			clock.restart();
		}
		else 
		{
			sprite.move(vx, -vy);
		}

		break;
	case Dying:
		state = 6;
		break;
	}

	//set textures, origins, and scaling
	sprite.setTexture(textures[state]);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
	sprite.setScale(-heading * MARIO_SCALE, MARIO_SCALE);
}

void Mario::jump(bool down) 
{

	if (down) 
	{
		//mario falling

		if (vy < 0) vy -= GRAVITY * MARIO_FALL_SPEED * ELAPSED_TIME * 30;
		
		//When mario hits floor first time, his state switches to standing
		if (marioState == Jumping)
			marioState = Standing;
	}
	else 
	{
		//mario jumping
		vy -= GRAVITY * MARIO_FALL_SPEED * ELAPSED_TIME;
	}

	//max fall speed
	if (vy < -MARIO_MAX_FALL_SPEED && marioState != Dying) vy = -MARIO_MAX_FALL_SPEED; 
}

void Mario::respawnMario(void) 
{
	
	//When mario pass WINDOW_HEIGHT * RESPAWN_TIME then respawn mario top of the screen
	if (sprite.getPosition().y >= WINDOW_HEIGHT * RESPAWN_TIME) 
	{
		sprite.setPosition(WINDOW_WIDTH / 2, 0);
		vy = 1;
		marioState = Jumping;
	}

}

void Mario::fall(void) 
{
	//Mari die state
	marioState = Dying;
	vy = 8.0f;				//for falling animation. first jumping and then falling
	vx = 0;
	down = false;

	if (sprite.getPosition().y >= WINDOW_HEIGHT * 1.1) 
	{
		sprite.setPosition(WINDOW_WIDTH / 2, 0);
		vy = 0;
	}
}

void Mario::setSpeedX(float vx) 
{
	this->vx = vx;
}

void Mario::setSpeedY(float vy) 
{
	this->vy = vy;
}

MarioState Mario::getMarioState(void) 
{
	return marioState;
}

void Mario::setMarioState(MarioState s) 
{
	this->marioState = s;
}

void Mario::reset_ATR() 
{
	//Reset mario in game
	pos.x = WINDOW_WIDTH / 2;
	pos.y = FLOOR_START-15;
	state = 0;
	heading = -1;
	vx = 0.0f;
	vy = 0.0f;
	marioState = Standing;
	down = true;
	dieflag = 0;
	sprite.setTexture(textures[state]);
	sprite.setPosition(pos.x, pos.y);
	sprite.setOrigin(sprite.getLocalBounds().width / 2, 0);
	sprite.setScale(-heading * MARIO_SCALE, MARIO_SCALE);
}