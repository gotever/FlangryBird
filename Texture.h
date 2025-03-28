#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <stdio.h>

class Position
{
public:
	int x, y, angle, state;
	void setPos(const int x, const int y);
};

class LTexture
{
public:
	LTexture();
	~LTexture();

	bool Load(std::string path, double scale = 1);

	bool isNULL(); // check if texture is NULL

	int getWidth();
	int getHeight();

	void Free();

	void Render(int x, int y, int angle = 0, SDL_Rect* clip = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	static bool quit;
	static bool die;
	static int score;

	static SDL_Window* gWindow;
	static SDL_Renderer* gRenderer;
	static SDL_Event event;

	static const int SCREEN_WIDTH{ 350 };
	static const int SCREEN_HEIGHT{ 625 };
	static const int LAND_HEIGHT{ 140 };
	static const int BIRD_WIDTH{ 50 };
	static const int BIRD_HEIGHT{ 35 };
	static const int PIPE_SPACE{ 123 };
	static const int TOTAL_PIPE{ 4 };
	static const int PIPE_DISTANCE{ 220 };
	static const int GRASS_HEIGHT{ 30 };

private:
	SDL_Texture* Texture{};
	int tWidth{};
	int tHeight{};
};