#pragma once
#include "Texture.h"

class Menu : LTexture
{
public:
	Menu();

	~Menu();

	void renderBackground();

	void renderLogo();

	void renderButton();

	bool playButtonPressed();

	bool exitButtonPressed();

	void free();

private:
	int buttonSize{};
	int menuSizeX{};
	int menuSizeY{};
};