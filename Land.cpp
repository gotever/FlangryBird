#include "Land.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

bool Land::init()
{
	landPos.setPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
	std::string land_path{ "sprites/base.png" };

	if (isNULL())
	{
		if (!Load(land_path.c_str(), 1))
		{
			return false;
		}
	}

	return true;
}

void Land::render()
{
	if (landPos.x > 0)
	{
		Render(landPos.x, landPos.y);
	}
	else if (landPos.x > -SCREEN_WIDTH && landPos.x <= 0)
	{
		Render(landPos.x, landPos.y);
		Render(landPos.x + SCREEN_WIDTH, landPos.y);
	}
	else
	{
		landPos.setPos(0, SCREEN_HEIGHT - LAND_HEIGHT);
		Render(landPos.x, landPos.y);
	}
}

void Land::update()
{
	landPos.x -= 3;
}

void Land::free()
{
	Free();
}