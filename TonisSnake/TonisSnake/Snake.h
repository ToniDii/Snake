#pragma once
#include <SDL.h>
#include <iostream>
#include "defines.h"
#include <vector>

class Snake
{
public:
	enum Direction
	{
		Up,
		Down,
		Left,
		Right,
		NONE
	};
	Direction currentSnakeDirection;
	Direction lastSnakeDirection;

	Snake(int _posX, int _posY, int _width, int _height, Direction _currentDirection);
	~Snake();


	void Spawn(Snake& _player);
	void Update(Snake& _player);
	void Movement(Snake& _player);
	void Render(SDL_Renderer& _renderer);
	void SnakePushBack(Snake& _player);

	const int GetSnakeIndexPosX(int _index) const;
	const int GetSnakeIndexPosY(int _index) const;
	const int Getm_SnakeSize() const;
	const int GetSnakeIndexDirection(int _index) const;

private:
	int snakePosX;
	int snakePosY;
	int snakeWidth;
	int snakeHeight;
	int snakeLength;
	int snakeRectGap;
	int snakeMoveSpeed;
	int DirectionChangePosX = -1;
	int DirectionChangePosY = -1;
	int ButtonPressDelayMs = 100;
	int afterButtonPressed = 0;
	bool snakeCanGetLonger;
	std::vector<Snake> m_Snake;
	std::vector<int> m_DirectionChangeX;
	std::vector<int> m_DirectionChangeY;
	bool wFirstPress = true;
	bool sFirstPress = true;
	bool aFirstPress = true;
	bool dFirstPress = true;

};

inline const int Snake::GetSnakeIndexPosX(int _index) const {
	return m_Snake[_index].snakePosX;
};

inline const int Snake::GetSnakeIndexPosY(int _index) const {
	return m_Snake[_index].snakePosY;
};

inline const int Snake::Getm_SnakeSize() const {
	return m_Snake.size();
};

inline const int Snake::GetSnakeIndexDirection(int _index) const {
	return m_Snake[_index].currentSnakeDirection;
};