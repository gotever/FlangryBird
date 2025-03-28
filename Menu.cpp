#include "Menu.h"

Menu::Menu()
{
	buttonSize = 0;
}

Menu::~Menu()
{
	free();
}

void Menu::takeInputMenu()
{
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		quit = true;
	}
}

void Menu::renderBackground()
{
	LTexture image;
	image.Load("sprites/backgroundMenu1.png", 1);
	image.Render(0, 0);
	image.Free();
}

void Menu::renderLogo()
{
	LTexture image;
	image.Load("sprites/logo.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 50);
	image.Free();
}

void Menu::renderButton()
{
	LTexture image;
	image.Load("sprites/playButton.png", 2);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 300);
	image.Load("sprites/exitButton.png", 2);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 400);
	image.Free();
}

bool Menu::playButtonPressed()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - buttonSize) / 2 && x < (SCREEN_WIDTH - buttonSize) / 2 + buttonSize &&
		y > 300 && y < 300 + buttonSize)
	{
		return true;
	}
	
	return false;
}

bool Menu::exitButtonPressed()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - buttonSize) / 2 && x < (SCREEN_WIDTH - buttonSize) / 2 + buttonSize &&
		y > 400 && y < 400 + buttonSize)
	{
		return true;
	}

	return false;
}

void Menu::free()
{
	Free();
}