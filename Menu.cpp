#include "Menu.h"

Menu::Menu()
{
	buttonSize = 0;
}

Menu::~Menu()
{
	free();
}

void Menu::renderBackground()
{
	LTexture image;
	image.Load("sprites/backgroundMenu.png", 1);
	image.Render(0, 0);
	image.Free();
}

bool Menu::init()
{
	bool success = true;
	if (!Load("sprites/menu.png"))
	{
		success = false;
	}
	else
	{
		buttonSize = getWidth() / 2;
	}
	return success;
}

void Menu::renderLogo()
{
	LTexture image;
	image.Load("sprites/logo.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 80);
	image.Free();
}

void Menu::renderButton()
{
	LTexture image;
	image.Load("sprites/playButton.png", 1);
	image.Render((SCREEN_WIDTH - buttonSize) / 2, 300);
	image.Load("sprites/exitButton.png", 1);
	image.Render((SCREEN_WIDTH - buttonSize) / 2, 400);
	image.Free();
}

void Menu::checkButton(bool& isExit)
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - buttonSize) / 2 && x < (SCREEN_WIDTH - buttonSize) / 2 + buttonSize &&
		y > 300 && y < 300 + buttonSize)
	{
		isExit = false;
	}
	else if (x > (SCREEN_WIDTH - buttonSize) / 2 && x < (SCREEN_WIDTH - buttonSize) / 2 + buttonSize &&
		y > 400 && y < 400 + buttonSize)
	{
		isExit = true;
	}
}	

void Menu::renderMenu()
{
	LTexture image;
	image.Load("sprites/menu.png", 1);
	image.Render((SCREEN_WIDTH - menuSizeX) / 2, (SCREEN_HEIGHT - menuSizeY) / 2 - menuSizeY / 2);
	image.Free();
}

void Menu::free()
{
	Free();
}