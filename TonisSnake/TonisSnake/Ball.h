#pragma once
#include <SDL.h>
#include <iostream>
#include <ctime>
#include "defines.h"


class Ball
{
public:
	Ball(int _posX, int _posY, int _radius);
	~Ball();

	void Render(SDL_Renderer* _renderer);


	void inline SetBallPosX(int _x) {
		ballCenterPosX = _x;
	}
	void inline SetBallPosY(int _y) {
		ballCenterPosY = _y;
	}

	const int GetBallPosX() const;
	const int GetBallPosY() const;


private:
	int ballCenterPosX;
	int ballCenterPosY;
	int ballRadius;
};

inline const int Ball::GetBallPosX() const {
	return ballCenterPosX;
};

inline const int Ball::GetBallPosY() const {
	return ballCenterPosY;
};

