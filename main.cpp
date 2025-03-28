#include "GameLoop.h"
#include "Texture.h"
#include <time.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

const int FPS{ 60 };
const int frameDelay{ 1000 / FPS };

int main(int argc, char* args[])
{
	Uint32 frameStart{};
	int frameTime{};
	GameLoop game;
	bool isExit{ true };
	bool isMenu{ false };
	bool isPause{ false };
	bool isSound{ true };
	bool isDark{ false };
	bool isRed{ true };
	bool isBlue{ false };
	bool isChuck{ false };

	game.sound.playBackground();
	while (!game.isQuit())
	{
		game.takeInput();

		//game.menu.init();
		game.menu.renderBackground();
		game.menu.renderLogo();
		game.menu.renderButton();
		if (game.userInput.type == GameLoop::Input::PLAY)
		{
			if (game.menu.playButtonPressed())
			{
				isExit = false;
				game.sound.playClick();
				break;
			}
		}
		game.display();

		//Limit FPS
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	Mix_HaltMusic();

	while (!game.isQuit() && !isExit)
	{
		Mix_ResumeMusic();
		frameStart = SDL_GetTicks();

		/*game.menu.renderBackground();
		game.menu.renderLogo();
		game.menu.renderButton();
		if (game.menu.playButtonPressed())
		{
			isExit = false;
		}
		if (game.menu.exitButtonPressed())
		{
			break;
		}
		game.display();*/

		if (game.isDie())
		{
			if (isMenu)
			{
				game.sound.playHit();
				game.sound.playDie();
				game.bird.render();
			}

			game.userInput.type = GameLoop::Input::NONE;
			while (game.isDie() && !game.isQuit())
			{
				game.takeInput();

				if (isMenu == true && game.userInput.type == GameLoop::Input::PLAY)
				{
					if (game.checkReplay())
					{
						game.sound.playClick();
						isMenu = false;
					}

					game.userInput.type = GameLoop::Input::NONE;
				}

				if (!isDark)
					game.renderBackgroundDay();
				else
					game.renderBackgroundNight();

				game.pipe.render();
				game.land.render();
				game.grass.render();

				if (isMenu)
				{
					game.bird.render();
					game.bird.fall();
					game.renderGameOver();
					//game.renderMedal();
					game.renderScoreSmall();
					game.renderBestScore();
					game.replay();
				}
				else
				{
					game.pipe.init();
					game.bird.init(isRed, isBlue, isChuck);
					game.bird.render();
					game.renderMessage();

					if (game.userInput.type == GameLoop::Input::PLAY)
					{
						game.restart();
						isMenu = true;
						game.userInput.type = GameLoop::Input::NONE;
					}

					game.land.update();
					game.grass.update();
				}

				game.display();
			}

			game.pipe.init();
		}
		else
		{
			game.takeInput();

			if (game.userInput.type == GameLoop::Input::PAUSE)
			{
				isPause = std::abs(1 - isPause);
				game.userInput.type = GameLoop::Input::NONE;
			}

			if (isPause == false && game.userInput.type == GameLoop::Input::PLAY)
			{
				if (isSound)
					game.sound.playWing();
				game.bird.resetTime();
				game.userInput.type = GameLoop::Input::NONE;
			}

			if (!isDark)
				game.renderBackgroundDay();
			else
				game.renderBackgroundNight();

			game.pipe.render();
			game.land.render();
			game.grass.render();
			game.bird.render();
			game.renderScoreLarge();

			if (!isPause)
			{
				if (game.bird.update(game.getPipeWidth(), game.getPipeHeight()))
				{
					game.sound.playPoint();
				}
				game.pipe.update();
				game.land.update();
				game.grass.update();
				game.pause();
			}
			else
			{
				game.resume();
				game.renderPauseTab();
				game.renderScoreSmall();
				game.renderBestScore();
				game.replay();
				game.sound.renderSoundButton();

				if (isRed)
					game.redBirdTheme();
				else if (isBlue)
					game.blueBirdTheme();
				else
					game.chuckBirdTheme();

				if (!isDark)
				{
					game.dayTheme();
				}
				else
				{
					game.nightTheme();
				}

				game.nextButton();

				if (game.userInput.type == GameLoop::Input::PLAY)
				{
					if (game.checkReplay())
					{
						game.sound.playClick();
						isPause = 0;
					}
					else if (game.sound.checkSound())
					{
						isSound = std::abs(1 - isSound);
					}
					else if (game.changeTheme())
					{
						game.sound.playTick();
						isDark = std::abs(1 - isDark);
					}
					else if (game.changeBird(isRed, isBlue, isChuck))
					{
						game.sound.playTick();
						game.bird.init(isRed, isBlue, isChuck);
					}

					game.userInput.type = GameLoop::Input::NONE;
				}
			}

			game.display();
		}

		//Limit FPS
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	return 0;
}