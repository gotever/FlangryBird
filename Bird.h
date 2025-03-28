#pragma once
#include "Texture.h"
#include "Sound.h"
#include "Pipe.h"

//const short int TOTAL_BIRD_SHEET{ 3 };

class Bird : LTexture
{
public:
	Bird();

	bool init(bool isRed, bool isBlue, bool isChuck);

	//void render(LTexture* flyingBird);

	void render();

	//std::string birdState();

	void free();

	void resetTime();

	void fall();

	//void loadFlyingBird(LTexture* flyingBird);

	bool update(int pipeWidth, int pipeHeight);

	//LTexture flyingBirdDay[3];

private:
	int animationTimer{};
	int angle{};
	int time{}; // the time between 2 taps
	int x0{}; // current position of the bird
	int ahead{ 0 };
	//LTexture saved_path{};
	std::string saved_path{ "" };
	//LTexture flyingBirdDay[TOTAL_BIRD_SHEET];
	Position birdPos{};
};