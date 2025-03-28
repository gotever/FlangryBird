#pragma once

#include "Texture.h"
#include <iostream>
#include <vector>

extern std::vector<Position> pipePos;

class Pipe : LTexture
{
public:
	bool init();

	void render();

	void free();

	void update();

	int width() { return getWidth(); }

	int height() { return getHeight(); }

private:
	int randMin{ -373 + 30 };
	int randMax{ SCREEN_HEIGHT - LAND_HEIGHT - 373 - PIPE_DISTANCE - 30 };
};