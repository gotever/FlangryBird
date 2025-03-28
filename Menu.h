#pragma once
#include "Texture.h"

class Menu : LTexture
{
public:
	Menu();

	~Menu();

	void renderBackground();

	bool init();

	void renderLogo();

	void renderButton();

	void checkButton(bool& isExit);

	void free();

private:
	int buttonSize{};
	int menuSizeX{};
	int menuSizeY{};
};