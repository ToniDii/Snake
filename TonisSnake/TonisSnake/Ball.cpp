#include "Ball.h"

Ball::Ball(int _posX, int _posY, int _radius) :
	ballCenterPosX(_posX),
	ballCenterPosY(_posY),
	ballRadius(_radius)
{};

Ball::~Ball() {};


void Ball::Update() 
{

};

void Ball::Render(SDL_Renderer* _renderer)
{
	const int32_t diameter = (ballRadius * 2);

	int32_t x = (ballRadius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(_renderer, ballCenterPosX + x, ballCenterPosY - y);
		SDL_RenderDrawPoint(_renderer, ballCenterPosX + x, ballCenterPosY + y);
		SDL_RenderDrawPoint(_renderer, ballCenterPosX - x, ballCenterPosY - y);
		SDL_RenderDrawPoint(_renderer, ballCenterPosX - x, ballCenterPosY + y);
		SDL_RenderDrawPoint(_renderer, ballCenterPosX + y, ballCenterPosY - x);
		SDL_RenderDrawPoint(_renderer, ballCenterPosX + y, ballCenterPosY + x);
		SDL_RenderDrawPoint(_renderer, ballCenterPosX - y, ballCenterPosY - x);
		SDL_RenderDrawPoint(_renderer, ballCenterPosX - y, ballCenterPosY + x);

		SDL_Rect ballRect;
		ballRect.x = ballCenterPosX - ballRadius/2;
		ballRect.y = ballCenterPosY - ballRadius / 2;
		ballRect.w = ballRadius;
		ballRect.h = ballRadius;
		SDL_SetRenderDrawColor(_renderer, 255, 69, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(_renderer, &ballRect);

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}
};