#pragma once
#include <iostream>
#include <string>
#include "Snake.h"
#include "Ball.h"
#include "SDL_ttf.h"

class GameRules
{
public:
	GameRules();
	~GameRules();

	void InitPoints(SDL_Renderer& _renderer);
	void RenderPoints(SDL_Renderer& _renderer);

	void LosingCondition(Snake& _snake, SDL_Renderer& _renderer);
	void UpdatePoints(Snake& _snake, Ball& _ball, SDL_Renderer& _renderer);

private:
	TTF_Font* PointFont;
	SDL_Color white = { 255, 255, 255 };

	SDL_Surface* surfaceMessage;
	SDL_Texture* Message;
	SDL_Rect Message_rect;

	SDL_Rect score_rect;
	SDL_Surface* scoreSurfaceMessage;
	SDL_Texture* scoreMessage;

	int Score = 0;
	int Offset = 6;
};

