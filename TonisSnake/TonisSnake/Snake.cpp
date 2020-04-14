#include "Snake.h"

Snake::Snake(int _posX, int _posY, int _width, int _height, Direction _currentDirection) :
	snakePosX(_posX),
	snakePosY(_posY),
	snakeWidth(_width),
	snakeHeight(_height),
	snakeMoveSpeed(4),
	currentSnakeDirection(_currentDirection)
{};

Snake::~Snake() {};

void Snake::Spawn(Snake& _player)
{
	int xOffset = 0;
	int yOffset = 0;

	for (int i = 0; i < snakeStartLength; i++)
	{
		Snake playerSnake(_player.snakePosX + xOffset, _player.snakePosY + yOffset, _player.snakeWidth, _player.snakeHeight, _player.currentSnakeDirection);
		m_Snake.push_back(playerSnake);

		yOffset += snakeHeight + snakeGapSize;
		std::cout << "Array Size:" << m_Snake.size() << std::endl;
	}
};

void Snake::Update(Snake& _player)
{
	// Keep Snake in Window
	for (int i = 0; i < m_Snake.size(); i++)
	{
		//left side 
		if (_player.m_Snake[i].snakePosX - snakeWidth < 0 && _player.m_Snake[i].currentSnakeDirection == Left)
		{
			_player.m_Snake[i].snakePosX = screen_width;
		}
		//right side
		if (_player.m_Snake[i].snakePosX + snakeWidth > screen_width&& _player.m_Snake[i].currentSnakeDirection == Right)
		{
			_player.m_Snake[i].snakePosX = 0;
		}
		// top side
		if (_player.m_Snake[i].snakePosY < snakeHeight && _player.m_Snake[i].currentSnakeDirection == Up)
		{
			_player.m_Snake[i].snakePosY = screen_height;
		}
		// bottom side
		if (_player.m_Snake[i].snakePosY + snakeHeight > screen_height&& _player.m_Snake[i].currentSnakeDirection == Down)
		{
			_player.m_Snake[i].snakePosY = 0;
		}
	}
}


void Snake::Movement(Snake& _player)
{
	SDL_Event event;
	const Uint8* state = SDL_GetKeyboardState(NULL);

	int SDL_timePassed = SDL_GetTicks();

	//Keyboard Inputs

	if (state[SDL_SCANCODE_W] && currentSnakeDirection != Down && SDL_timePassed >= TimeAfterButtonPressedMs) {
		lastSnakeDirection = currentSnakeDirection;
		currentSnakeDirection = Up;
		_player.m_Snake[0].currentSnakeDirection = currentSnakeDirection;

		int newDirectionChangeX(_player.m_Snake[0].snakePosX);
		m_DirectionChangeX.push_back(newDirectionChangeX);

		int newDirectionChangeY(_player.m_Snake[0].snakePosY);
		m_DirectionChangeY.push_back(newDirectionChangeY);

		TimeAfterButtonPressedMs = SDL_GetTicks() + ButtonPressDelayMs;
	}
	else if (state[SDL_SCANCODE_S] && currentSnakeDirection != Up && SDL_timePassed >= TimeAfterButtonPressedMs) {
		lastSnakeDirection = currentSnakeDirection;
		currentSnakeDirection = Down;
		_player.m_Snake[0].currentSnakeDirection = currentSnakeDirection;

		int newDirectionChangeX(_player.m_Snake[0].snakePosX);
		m_DirectionChangeX.push_back(newDirectionChangeX);

		int newDirectionChangeY(_player.m_Snake[0].snakePosY);
		m_DirectionChangeY.push_back(newDirectionChangeY);

		TimeAfterButtonPressedMs = SDL_GetTicks() + ButtonPressDelayMs;
	}
	if (state[SDL_SCANCODE_A] && currentSnakeDirection != Right && SDL_timePassed >= TimeAfterButtonPressedMs) {
		lastSnakeDirection = currentSnakeDirection;
		currentSnakeDirection = Left;
		_player.m_Snake[0].currentSnakeDirection = currentSnakeDirection;

		int newDirectionChangeX(_player.m_Snake[0].snakePosX);
		m_DirectionChangeX.push_back(newDirectionChangeX);

		int newDirectionChangeY(_player.m_Snake[0].snakePosY);
		m_DirectionChangeY.push_back(newDirectionChangeY);

		TimeAfterButtonPressedMs = SDL_GetTicks() + ButtonPressDelayMs;
	}
	else if (state[SDL_SCANCODE_D] && currentSnakeDirection != Left && SDL_timePassed >= TimeAfterButtonPressedMs) {
		lastSnakeDirection = currentSnakeDirection;
		currentSnakeDirection = Right;
		_player.m_Snake[0].currentSnakeDirection = currentSnakeDirection;

		int newDirectionChangeX(_player.m_Snake[0].snakePosX);
		m_DirectionChangeX.push_back(newDirectionChangeX);

		int newDirectionChangeY(_player.m_Snake[0].snakePosY);
		m_DirectionChangeY.push_back(newDirectionChangeY);

		TimeAfterButtonPressedMs = SDL_GetTicks() + ButtonPressDelayMs;
	}
	//Debug KEY
	if (state[SDL_SCANCODE_K])
	{

	}

	// Direction Change for Snake
	for (int i = 1; i < m_Snake.size(); i++)
	{
		for (int j = 0; j < m_DirectionChangeX.size(); j++)
		{
			if (_player.m_Snake[i].snakePosX == m_DirectionChangeX[j] && _player.m_Snake[i].snakePosY == m_DirectionChangeY[j])
			{
				_player.m_Snake[i].currentSnakeDirection = _player.m_Snake[i - 1].currentSnakeDirection;

				if (_player.m_Snake[m_Snake.size() - 1].snakePosX == m_DirectionChangeX[j] && _player.m_Snake[m_Snake.size() - 1].snakePosY == m_DirectionChangeY[j])
				{
					m_DirectionChangeX.erase(m_DirectionChangeX.begin());
					m_DirectionChangeY.erase(m_DirectionChangeY.begin());
				}
			}
		}
	}


	for (int i = 0; i < m_Snake.size(); i++)
	{
		switch (_player.m_Snake[i].currentSnakeDirection)
		{
		case Up:
			_player.m_Snake[i].snakePosY -= snakeMoveSpeed;
			break;
		case Down:
			_player.m_Snake[i].snakePosY += snakeMoveSpeed;
			break;
		case Left:
			_player.m_Snake[i].snakePosX -= snakeMoveSpeed;
			break;
		case Right:
			_player.m_Snake[i].snakePosX += snakeMoveSpeed;
			break;
		default:
			break;
		}
	}
}





void Snake::Render(SDL_Renderer& _renderer)
{

	for (int i = 0; i < m_Snake.size(); i++)
	{
		SDL_Rect snakeRect;
		snakeRect.x = m_Snake[i].snakePosX;
		snakeRect.y = m_Snake[i].snakePosY;
		snakeRect.w = m_Snake[i].snakeWidth;
		snakeRect.h = m_Snake[i].snakeHeight;
		SDL_SetRenderDrawColor(&_renderer, 238, 238, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(&_renderer, &snakeRect);
	}
};

void Snake::SnakePushBack(Snake& _player)
{
	int snakeLength = m_Snake.size() - 1;
	int XOffset = snakeWidth + snakeGapSize;
	int YOffset = snakeHeight + snakeGapSize;

	if (_player.m_Snake[snakeLength].currentSnakeDirection == Up) {
		Snake playerSnake(_player.m_Snake[snakeLength].snakePosX, _player.m_Snake[snakeLength].snakePosY + YOffset, _player.snakeWidth, _player.snakeHeight, _player.m_Snake[snakeLength].currentSnakeDirection);
		m_Snake.push_back(playerSnake);
	}
	else if (_player.m_Snake[snakeLength].currentSnakeDirection == Down) {
		Snake playerSnake(_player.m_Snake[snakeLength].snakePosX, _player.m_Snake[snakeLength].snakePosY - YOffset, _player.snakeWidth, _player.snakeHeight, _player.m_Snake[snakeLength].currentSnakeDirection);
		m_Snake.push_back(playerSnake);
	}
	if (_player.m_Snake[snakeLength].currentSnakeDirection == Left) {
		Snake playerSnake(_player.m_Snake[snakeLength].snakePosX + XOffset, _player.m_Snake[snakeLength].snakePosY, _player.snakeWidth, _player.snakeHeight, _player.m_Snake[snakeLength].currentSnakeDirection);
		m_Snake.push_back(playerSnake);
	}
	else if (_player.m_Snake[snakeLength].currentSnakeDirection == Right) {
		Snake playerSnake(_player.m_Snake[snakeLength].snakePosX - XOffset, _player.m_Snake[snakeLength].snakePosY, _player.snakeWidth, _player.snakeHeight, _player.m_Snake[snakeLength].currentSnakeDirection);
		m_Snake.push_back(playerSnake);
	}
};