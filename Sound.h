#pragma once
#include <SDL_mixer.h>
#include "Texture.h"
#include <string>

class Sound : LTexture
{
public:
	bool init();

	void free();

	void playDie();

	void playHit();

	void playPoint();

	void playSwoosh();

	void playWing();

	void playBackground(bool checkPause);

	void playClick();

	void renderSoundButton();

	bool checkSound();

private:
	const int POS_X{ 217 };
	const int POS_Y{ 267 };
	bool isPlay{ true };
	Mix_Chunk* wing{ NULL };
	Mix_Chunk* hit{ NULL };
	Mix_Chunk* die{ NULL };
	Mix_Chunk* swoosh{ NULL };
	Mix_Chunk* point{ NULL };
	Mix_Chunk* click{ NULL };
	Mix_Music* background{ NULL };
	SDL_Rect mute{};
	SDL_Rect active{};
};