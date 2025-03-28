#include "Menu.h"

Menu::Menu()
{
	buttonSizeX = 280;
	buttonSizeY = 159;
	shrinkButtonSize = 266;
	playButtonScale = 1;
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
	image.Load("sprites/backgroundMenu2.png", 1);
	image.Render(0, 0);
	image.Free();
}

void Menu::renderLogo()
{
	LTexture image;
	image.Load("sprites/logo.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2 + 3, 50);
	image.Free();
}

void Menu::renderButton()
{
	LTexture image;
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - buttonSizeX) / 2 && x < (SCREEN_WIDTH - buttonSizeX) / 2 + buttonSizeX &&
		y > 300 && y < 300 + buttonSizeY)
	{
		image.Load("sprites/shrinkPlayButton2-2.png", 1);
		image.Render((SCREEN_WIDTH - shrinkButtonSize) / 2, 300);
	}
	else
	{
		image.Load("sprites/playButton2-2.png", 1);
		image.Render((SCREEN_WIDTH - buttonSizeX) / 2, 300);
	}
	/*image.Load("sprites/exitButton.png", 2);
	image.Render((SCREEN_WIDTH - buttonSize) / 2, 400);*/
	image.Free();
}

bool Menu::playButtonPressed()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - buttonSizeX) / 2 && x < (SCREEN_WIDTH - buttonSizeX) / 2 + buttonSizeX &&
		y > 300 && y < 300 + buttonSizeY)
	{
		return true;
	}
	
	return false;
}

//bool Menu::exitButtonPressed()
//{
//	int x{}, y{};
//	SDL_GetMouseState(&x, &y);
//	if (x > (SCREEN_WIDTH - buttonSize) / 2 && x < (SCREEN_WIDTH - buttonSize) / 2 + buttonSize &&
//		y > 400 && y < 400 + buttonSize)
//	{
//		return true;
//	}
//
//	return false;
//}

void Menu::free()
{
	Free();
}