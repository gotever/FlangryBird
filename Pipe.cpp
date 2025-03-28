#include "Pipe.h"
#include "Random.h"
#include <stdio.h>

std::vector<Position> pipePos;

bool Pipe::init()
{
	pipePos.clear();

	for (size_t i = 0; i < TOTAL_PIPE; ++i)
	{
		Position temp;
		temp.setPos(SCREEN_WIDTH + i * PIPE_DISTANCE + 350, Random::get(randMin, randMax)); // create a random pipe's hole
		pipePos.push_back(temp);
	}
	if (isNULL())
	{
		if (Load("sprites/pipe.png", 1))
		{
			return true;
		}
	}

	return false;
}

void Pipe::free()
{
	Free();
}

void Pipe::render()
{
	for (size_t i = 0; i < TOTAL_PIPE; ++i)
	{
		if (pipePos[i].x <= SCREEN_WIDTH && pipePos[i].x > -getWidth()) // if x is in the window then render
		{
			Render(pipePos[i].x, pipePos[i].y);
		}

		Render(pipePos[i].x, pipePos[i].y + getHeight() + PIPE_SPACE, 180); // angle = 180 => upside down
	}
}

void Pipe::update()
{
	if (!die)
	{
		for (size_t i = 0; i < TOTAL_PIPE; ++i)
		{
			if (pipePos[i].x < -getWidth())
			{
				pipePos[i].y = Random::get(randMin, randMax);
				pipePos[i].x = pipePos[(i + TOTAL_PIPE - 1) % TOTAL_PIPE].x + PIPE_DISTANCE; // pipe goes out of window => next pipe goes in
			}
			else
			{
				pipePos[i].x -= 3; // else pipe will go backward as the bird goes forward
			}
		}
	}
}