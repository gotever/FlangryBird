#pragma once
#include "Texture.h"
#include <vector>

class Grass : LTexture
{
public:
	bool init();

	void render();

	void update();

	void free();

private:
	Position grassPos{};
};