#include "GameLoop.h"
#include "Texture.h"
#include <iostream>

GameLoop::GameLoop()
{
	initGame();
	pipe.init();
	land.init();
	grass.init();
	sound.init();
	//menu.init();
	birdType = Type::red;
}

GameLoop::~GameLoop()
{
	bird.free();
	pipe.free();
	land.free();
	grass.free();
	sound.free();
	//menu.free();
	Free();
	releaseGame();
}

bool GameLoop::initGame()
{
	bool success{ true };

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		gWindow = SDL_CreateWindow("Flangry Bird", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

void GameLoop::releaseGame()
{
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameLoop::takeInput()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT)
		{
			userInput.type = Input::QUIT;
			quit = true;
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN &&
			(event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && event.key.repeat == 0))
		{
			userInput.type = Input::PLAY;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE && event.key.repeat == 0)
		{
			userInput.type = Input::PAUSE;
		}
	}
}

void GameLoop::display()
{
	SDL_RenderPresent(gRenderer);
	SDL_RenderClear(gRenderer);
}

void GameLoop::renderScoreSmall()
{
	std::string s{ std::to_string(score) };
	int len{ static_cast<int>(s.length()) };
	LTexture image;

	for (int i = len - 1; i >= 0; --i)
	{
		int number{ static_cast<char>(s[i] - '0') };
		if (number == 1)
		{
			image.Load("sprites/smallangrynumber/1.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("sprites/smallangrynumber/2.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("sprites/smallangrynumber/3.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("sprites/smallangrynumber/4.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("sprites/smallangrynumber/5.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("sprites/smallangrynumber/6.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("sprites/smallangrynumber/7.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("sprites/smallangrynumber/8.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("sprites/smallangrynumber/9.png", scaleNumberS);
		}
		else
		{
			image.Load("sprites/smallangrynumber/0.png", scaleNumberS);
		}
		image.Render(118 - (image.getWidth() * 0.75 * len) / 2 + i * image.getWidth() * 0.75, 376);
	}
	image.Free();
}

void GameLoop::renderScoreLarge()
{
	std::string s{ std::to_string(score) };
	int len{ static_cast<int>(s.length()) };
	LTexture image;

	for (int i = len - 1; i >= 0; --i)
	{
		int number{ static_cast<char>(s[i] - '0') };
		if (number == 1)
		{
			image.Load("sprites/largeangrynumber/1.png", scaleNumberL);
		}
		else if (number == 2)
		{
			image.Load("sprites/largeangrynumber/2.png", scaleNumberL);
		}
		else if (number == 3)
		{
			image.Load("sprites/largeangrynumber/3.png", scaleNumberL);
		}
		else if (number == 4)
		{
			image.Load("sprites/largeangrynumber/4.png", scaleNumberL);
		}
		else if (number == 5)
		{
			image.Load("sprites/largeangrynumber/5.png", scaleNumberL);
		}
		else if (number == 6)
		{
			image.Load("sprites/largeangrynumber/6.png", scaleNumberL);
		}
		else if (number == 7)
		{
			image.Load("sprites/largeangrynumber/7.png", scaleNumberL);
		}
		else if (number == 8)
		{
			image.Load("sprites/largeangrynumber/8.png", scaleNumberL);
		}
		else if (number == 9)
		{
			image.Load("sprites/largeangrynumber/9.png", scaleNumberL);
		}
		else
		{
			image.Load("sprites/largeangrynumber/0.png", scaleNumberL);
		}
		image.Render((SCREEN_WIDTH - (image.getWidth() * len + (len - 1) * 10)) / 2 + (i + 30) * i, 100);
	}
	image.Free();
}

void GameLoop::renderBestScore()
{
	std::ifstream fileIn{ "data/bestScore.txt" };
	fileIn >> bestScore;
	std::ofstream fileOut("data/bestScore.txt", std::ios::trunc); // trunc: discard the contents of the stream when opening

	if (score > bestScore)
	{
		bestScore = score;
	}

	std::string s{ std::to_string(bestScore) };
	int len{ static_cast<int>(s.length()) };
	LTexture image{};

	for (int i = 0; i < len; ++i)
	{
		int number{ static_cast<int>(s[i] - '0') };
		if (number == 1)
		{
			image.Load("sprites/smallangrynumber/1.png", scaleNumberS);
		}
		else if (number == 2)
		{
			image.Load("sprites/smallangrynumber/2.png", scaleNumberS);
		}
		else if (number == 3)
		{
			image.Load("sprites/smallangrynumber/3.png", scaleNumberS);
		}
		else if (number == 4)
		{
			image.Load("sprites/smallangrynumber/4.png", scaleNumberS);
		}
		else if (number == 5)
		{
			image.Load("sprites/smallangrynumber/5.png", scaleNumberS);
		}
		else if (number == 6)
		{
			image.Load("sprites/smallangrynumber/6.png", scaleNumberS);
		}
		else if (number == 7)
		{
			image.Load("sprites/smallangrynumber/7.png", scaleNumberS);
		}
		else if (number == 8)
		{
			image.Load("sprites/smallangrynumber/8.png", scaleNumberS);
		}
		else if (number == 9)
		{
			image.Load("sprites/smallangrynumber/9.png", scaleNumberS);
		}
		else
		{
			image.Load("sprites/smallangrynumber/0.png", scaleNumberS);
		}
		image.Render(230 - (image.getWidth() * 0.75 * len) / 2 + i * image.getWidth() * 0.75, 376);
		//image.Render(240 - image.getWidth() * (len - i - 1) * 0.75 - 5 * (len - i - 1), 376);
	}
	image.Free();

	fileOut << bestScore;
	fileIn.close();
	fileOut.close();
}

void GameLoop::renderMessage()
{
	LTexture image{};
	image.Load("sprites/messagev6-2.png", 1.2);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 80);
	image.Free();
}

void GameLoop::renderBackgroundDay()
{
	LTexture image{};
	image.Load("sprites/background-day.png", 1);
	image.Render(0, 0);
	image.Free();
}

void GameLoop::renderBackgroundNight()
{
	LTexture image{};
	image.Load("sprites/background-night.png", 1);
	image.Render(0, 0);
	image.Free();
}

void GameLoop::renderLand()
{
	LTexture image{};
	image.Load("sprites/base.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, SCREEN_HEIGHT - image.getHeight());
	image.Free();
}

void GameLoop::resume()
{
	LTexture image{};
	image.Load("sprites/resume2.png", 0.8);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.Free();
}
void GameLoop::pause()
{
	LTexture image{};
	image.Load("sprites/pause2.png", 0.8);
	image.Render(SCREEN_WIDTH - 50, 20);
	image.Free();
}

void GameLoop::renderPauseTab()
{
	LTexture image{};
	image.Load("sprites/pauseTab.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 160);
	image.Load("sprites/pauseWordv2.png", 0.6);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.Free();
}

void GameLoop::redBirdTheme()
{
	LTexture image{};
	image.Load("sprites/red-bird.png", 0.8);
	image.Render(107, 304);
	image.Free();
}

void GameLoop::blueBirdTheme()
{
	LTexture image{};
	image.Load("sprites/blue-bird.png", 0.8);
	image.Render(107, 304);
	image.Free();
}

void GameLoop::chuckBirdTheme()
{
	LTexture image{};
	image.Load("sprites/chuck-bird.png", 0.8);
	image.Render(107, 304);
	image.Free();
}

void GameLoop::dayTheme()
{
	LTexture image{};
	image.Load("sprites/background-day.png", 0.1);
	image.Render(107, 240);
	image.Free();
}

void GameLoop::nightTheme()
{
	LTexture image{};
	image.Load("sprites/background-night.png", 0.1);
	image.Render(107, 240);
	image.Free();
}

void GameLoop::nextButton()
{
	LTexture image{};
	image.Load("sprites/nextRight.png", 1);
	image.Render(149, 312);
	image.Load("sprites/nextLeft.png", 1);
	image.Render(88, 312);
	image.Load("sprites/nextRight.png", 1);
	image.Render(149, 250);
	image.Load("sprites/nextLeft.png", 1);
	image.Render(88, 250);
	image.Free();
}

bool GameLoop::changeBird(bool& isRed, bool& isBlue, bool& isChuck)
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	// 13: nextRight and nextLeft's width
	// 16: nextRight and nextLeft's height
	if ((x > 149 && x < 149 + 13) && (y > 312 && y < 312 + 16))
	{
		++birdType;
		birdType %= Type::birdNum;
		if (birdType == Type::red)
		{
			isChuck = false;
			isRed = true;
		}
		else if (birdType == Type::blue)
		{
			isRed = false;
			isBlue = true;
		}
		else if (birdType == Type::chuck)
		{
			isBlue = false;
			isChuck = true;
		}

		return true;
	}
	else if ((x > 88 && x < 88 + 13) && (y > 312 && y < 312 + 16))
	{
		--birdType;
		birdType = ((birdType < 0)? 3 + birdType : birdType) % Type::birdNum;

		if (birdType == Type::red)
		{
			isBlue = false;
			isRed = true;
		}
		else if (birdType == Type::blue)
		{
			isChuck = false;
			isBlue = true;
		}
		else if (birdType == Type::chuck)
		{
			isRed = false;
			isChuck = true;
		}

		return true;
	}

	return false;
}

bool GameLoop::changeTheme()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	// 13: nextRight and nextLeft's width
	// 16: nextRight and nextLeft's height
	if (((x > 149 && x < 149 + 13) || (x > 88 && x < 88 + 13)) && (y > 250 && y < 250 + 16))
	{
		return true;
	}

	return false;
}

void GameLoop::renderGameOver()
{
	LTexture image{};
	image.Load("sprites/menuflangry.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 160);
	image.Load("sprites/GameOverWord.png", 0.6);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 180);
	image.Load("sprites/angryfacesv2-2.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 135);
	image.Free();
}

void GameLoop::renderMedal()
{
	LTexture image{};

	if (score <= 20)
	{
		image.Load("sprites/medal_bronze.png", 1.75);
	}
	if (score > 20 && score <= 50)
	{
		image.Load("sprites/medal_silver.png", 1.75);
	}
	else if (score > 50 && score <= 100)
	{
		image.Load("sprites/medal_gold.png", 1.75);
	}
	else if (score > 100)
	{
		image.Load("sprites/medal_platinum.png", 1.75);
	}
	image.Render(82, 275);

	image.Free();
}

void GameLoop::replay()
{
	LTexture image{};
	image.Load("sprites/replay.png", 1);
	image.Render((SCREEN_WIDTH - image.getWidth()) / 2, 420);
	image.Free();
}

bool GameLoop::checkReplay()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	if (x > (SCREEN_WIDTH - 100) / 2 && x < (SCREEN_WIDTH + 100) / 2 &&
		y > 420 && y < 420 + 56)
	{
		return true;
	}

	return false;
}

void GameLoop::restart()
{
	die = false;
	score = 0;
	bird.resetTime();
}