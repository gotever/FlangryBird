#include "Texture.h"
#include "GameLoop.h"
#include <iostream>

SDL_Window* LTexture::gWindow = NULL;
SDL_Renderer* LTexture::gRenderer = NULL;
SDL_Event LTexture::event;
bool LTexture::quit = false;
bool LTexture::die = true;
int LTexture::score = 0;

LTexture::LTexture()
{
	Texture = NULL;
}

LTexture::~LTexture()
{
	Free();
}

int LTexture::getWidth()
{
	return tWidth;
}

int LTexture::getHeight()
{
	return tHeight;
}

void LTexture::Free()
{
	if (Texture != NULL)
	{
		SDL_DestroyTexture(Texture);
		Texture = NULL;
		tWidth = 0;
		tHeight = 0;
	}
}

void LTexture::Render(int x, int y, int angle, SDL_Rect* clip, SDL_RendererFlip flip)
{
	SDL_Rect renderQuad{ x, y, tWidth, tHeight };

	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	SDL_RenderCopyEx(gRenderer, Texture, clip, &renderQuad, angle, NULL, flip);
}

bool LTexture::Load(std::string path, double scale)
{
	Free();

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xFF, 0xFF));

		Texture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (Texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			tWidth = (loadedSurface->w) * scale;
			tHeight = (loadedSurface->h) * scale;
		}

		SDL_FreeSurface(loadedSurface);
	}
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	return Texture != NULL;

}

bool LTexture::isNULL()
{
	if (Texture == NULL) return true;
	return false;
}

void Position::setPos(const int x, const int y)
{
	this->x = x;
	this->y = y;
}