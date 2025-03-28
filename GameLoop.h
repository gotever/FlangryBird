#pragma once
#include "Bird.h"
#include "Land.h"
#include "Grass.h"
#include "Pipe.h"
#include "Sound.h"
#include "Texture.h"
#include "Random.h"
#include <fstream>
#include <sstream>

enum Type { red, blue, chuck, birdNum };

class GameLoop : LTexture
{
public:
	GameLoop();

	~GameLoop();

	bool initGame();

	bool isQuit()
	{
		return quit;
	}

	bool isDie()
	{
		return die;
	}

	int getPipeWidth()
	{
		return pipe.width();
	}

	int getPipeHeight()
	{
		return pipe.height();
	}

	void takeInput();

	void display();

	void releaseGame();

	void renderScoreSmall();

	void renderScoreLarge();

	void renderBestScore();

	void renderMessage();

	void renderBackgroundDay();

	void renderBackgroundNight();

	void renderLand();

	void resume();

	void pause();

	void renderPauseTab();

	void redBirdTheme();

	void blueBirdTheme();

	void chuckBirdTheme();

	void dayTheme();

	void nightTheme();

	void nextButton();

	bool changeTheme();

	bool changeBird(bool& isRed, bool& isBlue, bool& isChuck);

	void renderGameOver();

	void renderMedal();

	void replay();

	bool checkReplay();

	void restart();

	struct Input
	{
		enum Type { QUIT, PLAY, PAUSE, NONE };
		Type type;
	};

	Input userInput{};
	Bird bird{};
	Pipe pipe{};
	Sound sound{};
	Land land{};
	Grass grass{};
	int birdType{};

private:
	const double scaleNumberS = 0.75;
	const double scaleNumberL = 1;
	int bestScore{};
};