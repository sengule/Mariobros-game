#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define WINDOW_WIDTH			1024
#define WINDOW_HEIGHT			768

#define ELAPSED_TIME			0.040F		//AVERAGE ELAPSED TIME
#define ANIMATION_TIME			0.02F		//TO GENERATE ANIMATION
#define GRAVITY					9.8F
#define RUN_SPEED				22.0F
#define JUMP_SPEED				0.12F
#define TURTLE_ACC				0.04F
#define TURTLE_SPEED			0.8F
#define TURTLE_MAX_SPEED		2.1F
#define TURTLE_MASS				0.006F //FOR FALL
#define TURTLE_NUM				5

#define MARIO_LIVES				3
#define MARIO_SPEED				2.50F
#define MARIO_ANIMATION			MARIO_SPEED * 0.05F
#define MARIO_WEIGHT			0.8F;
#define MARIO_SCALE				0.8F
#define MARIO_FALL_SPEED		0.6F
#define MARIO_JUMP_SPEED		8.5F
#define MARIO_MAX_FALL_SPEED	6.0F
#define MARIO_SLIDE_TIME		0.3F
#define MARIO_SLIDE_SPEED		1.5F
#define RESPAWN_TIME			3.0F

#define FLOOR_HEIGHT			WINDOW_HEIGHT * 0.90322
#define TURTLE_SCALE			0.7F
#define FLOOR_START				int(FLOOR_HEIGHT - 74 * (float)WINDOW_HEIGHT / 1024)

#define TOP_SIDE				1
	
#define scale_WW				float(float(WINDOW_WIDTH)/1024)
#define scale_WH				float(float(WINDOW_HEIGHT)/1024)