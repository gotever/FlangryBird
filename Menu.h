#pragma once
#include "Texture.h"

class Menu : LTexture
{
public:
	Menu();

	~Menu();

	void takeInputMenu();

	void renderBackground();

	void renderLogo();

	void renderButton();

	bool playButtonPressed();

	/*bool exitButtonPressed();*/

	void free();

private:
	int buttonSizeX;
	int buttonSizeY;
	int shrinkButtonSize;
	int playButtonScale;
};