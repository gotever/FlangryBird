#include "Grass.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

bool Grass::init()
{
	grassPos.setPos(0, SCREEN_HEIGHT - LAND_HEIGHT - GRASS_HEIGHT);
	std::string grass_path{ "sprites/grass.png" };

	if (isNULL())
	{
		if (!Load(grass_path.c_str(), 1))
		{
			return false;
		}
	}

	return true;
}

void Grass::render()
{
	if (grassPos.x > 0)
	{
		Render(grassPos.x, grassPos.y);
	}
	else if (grassPos.x > -SCREEN_WIDTH && grassPos.x <= 0)
	{
		Render(grassPos.x, grassPos.y);
		Render(grassPos.x + SCREEN_WIDTH, grassPos.y);
	}
	else
	{
		grassPos.setPos(0, SCREEN_HEIGHT - LAND_HEIGHT - GRASS_HEIGHT);
		Render(grassPos.x, grassPos.y);
	}
}

void Grass::update()
{
	grassPos.x -= 3;
}

void Grass::free()
{
	Free();
}