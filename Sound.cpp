#include "Sound.h"
#include <stdio.h>
#include <iostream>
#include <string>

bool Sound::init()
{
	std::string die_path{ "audio/die.wav" };
	std::string hit_path{ "audio/hit.wav" };
	std::string point_path{ "audio/point.wav" };
	std::string swoosh_path{ "audio/swoosh.wav" };
	std::string wing_path{ "audio/wing.wav" };
	std::string sound_button{ "sprites/sound.png" };
	std::string background_path{ "audio/angrybirdstheme.wav" };

	bool success = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		die = Mix_LoadWAV(die_path.c_str());
		if (die == NULL)
		{
			printf("Failed to load die sound! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		hit = Mix_LoadWAV(hit_path.c_str());
		if (hit == NULL)
		{
			printf("Failed to load hit sound! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		point = Mix_LoadWAV(point_path.c_str());
		if (point == NULL)
		{
			printf("Failed to load point sound! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		swoosh = Mix_LoadWAV(swoosh_path.c_str());
		if (swoosh == NULL)
		{
			printf("Failed to load swoosh sound! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		wing = Mix_LoadWAV(wing_path.c_str());
		if (wing == NULL)
		{
			printf("Failed to load wing sound! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		background = Mix_LoadMUS(background_path.c_str());
		if (background == NULL)
		{
			printf("Failed to load wing sound! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}

		if (!Load(sound_button)) // load sound button to texture
		{
			return false;
		}

		active.x = 0; active.y = 0; active.w = getWidth(); active.h = getHeight() / 2;
		mute.x = 0; mute.y = getHeight() / 2; mute.w = getWidth(); mute.h = getHeight() / 2;
	}

	return success;
}



void Sound::free()
{
	Free();

	Mix_FreeChunk(die);
	die = NULL;
	Mix_FreeChunk(hit);
	hit = NULL;
	Mix_FreeChunk(point);
	point = NULL;
	Mix_FreeChunk(swoosh);
	swoosh = NULL;
	Mix_FreeChunk(wing);
	wing = NULL;

	Mix_FreeMusic(background);
	background = NULL;

	Mix_Quit();
}

void Sound::playDie()
{
	if (isPlay)
	{
		Mix_PlayChannel(-1, die, 0);
	}
}

void Sound::playHit()
{
	if (isPlay)
	{
		Mix_PlayChannel(-1, hit, 0);
	}
}

void Sound::playPoint()
{
	if (isPlay)
	{
		Mix_PlayChannel(-1, point, 0);
	}
}

void Sound::playSwoosh()
{
	if (isPlay)
	{
		Mix_PlayChannel(-1, swoosh, 0);
	}
}

void Sound::playWing()
{
	if (isPlay)
	{
		Mix_PlayChannel(-1, wing, 0);
	}
}

void Sound::playBackground(bool checkPause)
{
	//If there is no music playing
	if (isPlay)
	{
		//Play the music
		Mix_PlayMusic(background, -1);
	}
	//If music is being played
	//else
	//{
	//	//If the music is paused
	//	if (Mix_PausedMusic() == 1)
	//	{
	//		//Resume the music
	//		Mix_ResumeMusic();
	//	}
	//	//If the music is playing
	//	else
	//	{
	//		//Pause the music
	//		Mix_PauseMusic();
	//	}
	//}
}

void Sound::renderSoundButton()
{
	if (isPlay)
	{
		Render(POS_X, POS_Y, 0, &active);
	}
	else
	{
		Render(POS_X, POS_Y, 0, &mute);
	}
}

bool Sound::checkSound()
{
	int x{}, y{};
	SDL_GetMouseState(&x, &y);
	if (x > POS_X && x < POS_X + getWidth() &&
		y > POS_Y && y < POS_Y + getWidth())
	{
		isPlay = !isPlay;
		return true;
	}

	return false;
}