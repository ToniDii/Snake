#include <iostream>
#include <SDL.h>
#include "SDL_ttf.h"
#include "Defines.h"
#include "Snake.h"
#include "Ball.h"
#include "GameRules.h"



int main(int argc, char* argv[])
{
	TTF_Init();
	srand((unsigned)time(0));
	int randomBallStartPosX = rand() % screen_width;
	int randomBallStartPosY = rand() % screen_height;

	Snake* Player = new Snake(playerStartPosX, playerStartPosY, snakeRectWidth, snakeRectHeight, Snake::Up);
	Ball* Enemy = new Ball(randomBallStartPosX, randomBallStartPosY, ballRadius);
	GameRules* Rules = new GameRules();
	

	Player->Spawn(*Player);

	//debug
	std::cout << "randomBallStartPosX: " << randomBallStartPosX << std::endl;
	std::cout << "randomBallStartPosY: " << randomBallStartPosY << std::endl;

	if (SDL_Init(SDL_INIT_VIDEO) == 0) {
		SDL_Window* window = NULL;
		SDL_Renderer* renderer = NULL;

		Rules->InitPoints(*renderer);

		if (SDL_CreateWindowAndRenderer(screen_width, screen_height, 0, &window, &renderer) == 0) {
			SDL_bool done = SDL_FALSE;

			while (!done) {
				int before = SDL_GetTicks();
				SDL_Event event;
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
				SDL_RenderClear(renderer);

				Player->Update(*Player);
				Player->Movement(*Player);
				Player->Render(*renderer);

				Enemy->Update();
				Enemy->Render(renderer);

				Rules->UpdatePoints(*Player, *Enemy, *renderer);
				Rules->RenderPoints(*renderer);
				Rules->LosingCondition(*Player);

				int after = SDL_GetTicks();
				int ticks = after - before;

				if (ticks < 16)
				{
					SDL_Delay(16 - ticks);
				}
				ticks = SDL_GetTicks() - before;
				/*std::cout << ticks << "\n";*/

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						done = SDL_TRUE;
					}
				}
				SDL_RenderPresent(renderer);
			}
		}

		if (renderer) {
			SDL_DestroyRenderer(renderer);
		}
		if (window) {
			SDL_DestroyWindow(window);
		}
	}

	TTF_Quit();
	SDL_Quit();
	return 0;
}