#include "Bird.h"
#include "Sound.h"
#include <string>
#include <stdio.h>
#include <iostream>

Bird::Bird()
{
	animationTimer = 0;
	angle = 0;
	time = 0;
	x0 = 0;
}

bool Bird::init(bool isRed, bool isBlue, bool isChuck)
{
	std::string bird_path{};
	if (isRed)
		bird_path = "sprites/red-bird.png";
	if (isBlue)
		bird_path = "sprites/blue-bird.png";
	if (isChuck)
		bird_path = "sprites/chuck-bird.png";

	if (saved_path == bird_path)
	{
		birdPos.setPos(75, SCREEN_HEIGHT / 2 - 10);
		ahead = 0;
		angle = 0;
	}

	if (isNULL() || saved_path != bird_path)
	{
		saved_path = bird_path;
		if (Load(bird_path.c_str(), 1))
		{
			return true;
		}
	}

	return false;
}

void Bird::render()
{
	Render(birdPos.x, birdPos.y, angle);
}

void Bird::free()
{
	Free();
}

void Bird::fall() // apply gravity when bird die
{
	if (die && birdPos.y < SCREEN_HEIGHT - LAND_HEIGHT - BIRD_HEIGHT - 5) // bird's y position in from the ground to top of the window
	{
		if (time == 0)
		{
			x0 = birdPos.y; // position when user taps
			angle = -25;
		}
		else if (angle < 70 && time > 30)
		{
			angle += 3;
		}

		if (time >= 0)
		{
			birdPos.y = static_cast<int>(x0 + time * time * 0.18 - 7.3 * time); // using quadratic function to calculate bird's position
			++time;
		}
	}
	else return;
}

bool Bird::update(int pipeWidth, int pipeHeight)
{
	bool pass{ false };
	if (!die)
	{
		if (time == 0)
		{
			x0 = birdPos.y;
			angle = -25;
		}
		else if (angle < 70 && time > 30)
		{
			angle += 3;
		}

		if (time >= 0)
		{
			birdPos.y = static_cast<int>(x0 + time * time * 0.18 - 7.3 * time);
			++time;
		}

		// getWidth(): width of bird
		// 1: touch the frontside of the pipe
		// 2: touch the backside of the pipe
		// 3: touch the upside of the pipe
		// 4: touch the downside of the pipe
		if ((birdPos.x + getWidth() > pipePos[ahead].x + 5) && (birdPos.x + 5 < pipePos[ahead].x + pipeWidth) &&
			(birdPos.y + 5 < pipePos[ahead].y + pipeHeight || birdPos.y + getHeight() > pipePos[ahead].y + pipeHeight + PIPE_SPACE + 5))
		{
			die = true;
		}
		else if (birdPos.x > pipePos[ahead].x + pipeWidth - 40)
		{
			ahead = (ahead + 1) % TOTAL_PIPE;
			++score;
			pass = true; // return true if the bird passes the pipe's space
		}

		if (birdPos.y > SCREEN_HEIGHT - LAND_HEIGHT - BIRD_HEIGHT - 5 || birdPos.y < -10)
		{
			die = true;
		}
	}

	return pass;
}
void Bird::resetTime()
{
	time = 0;
}