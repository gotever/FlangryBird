#pragma once
#include "Texture.h"
#include <vector>

class Land : LTexture
{
public:
	bool init();

	void render();

	void update();

	void free();

private:
	Position landPos{};
};