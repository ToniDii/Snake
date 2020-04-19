#include "GameRules.h"


GameRules::GameRules() :
	PointFont(TTF_OpenFont("assets/arial.ttf", 150))
{
};


GameRules::~GameRules() 
{
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
};


void GameRules::InitPoints(SDL_Renderer& _renderer)
{
	std::string scoreText = std::to_string(Score);
	surfaceMessage = TTF_RenderText_Blended(PointFont, scoreText.c_str(), white);
	Message = SDL_CreateTextureFromSurface(&_renderer, surfaceMessage);


	Message_rect.w = 10;
	Message_rect.h = 20; 
	Message_rect.x = 60;  
	Message_rect.y = 0; 

	score_rect.w = 55;
	score_rect.h = 20;
	score_rect.x = 0;
	score_rect.y = 0;
}


void GameRules::LosingCondition(Snake& _snake, SDL_Renderer& _renderer)
{
	for (int i = _snake.Getm_SnakeSize() - 1; i > 1; i--)
	{
		if (_snake.GetSnakeIndexPosX(0) < _snake.GetSnakeIndexPosX(i) + snakeRectWidth && 
			_snake.GetSnakeIndexPosX(0) > _snake.GetSnakeIndexPosX(i) - snakeRectWidth &&
			_snake.GetSnakeIndexPosY(0) >= _snake.GetSnakeIndexPosY(i) && 
			_snake.GetSnakeIndexPosY(0) <= _snake.GetSnakeIndexPosY(i) + snakeRectHeight)
		{
			std::cout << "You lost! Your final Score is: " << Score << std::endl;

			SDL_Delay(3000);
			SDL_Quit();
		}
	}
};

void GameRules::UpdatePoints(Snake& _snake, Ball& _ball, SDL_Renderer& _renderer)
{
	int snakeHeadCenterPosX = _snake.GetSnakeIndexPosX(0) + snakeRectWidth / 2;
	int snakeHeadCenterPosY = _snake.GetSnakeIndexPosY(0) + snakeRectHeight / 2;

	if (snakeHeadCenterPosX - snakeRectWidth / 2 <= _ball.GetBallPosX() + ballRadius &&
		snakeHeadCenterPosX + snakeRectWidth / 2 >= _ball.GetBallPosX() - ballRadius &&
		snakeHeadCenterPosY - snakeRectHeight / 2 <= _ball.GetBallPosY() + ballRadius &&
		snakeHeadCenterPosY + snakeRectHeight / 2 >= _ball.GetBallPosY() - ballRadius)
	{

		int randomBallPosX = rand() % screen_width;
		int randomBallPosY = rand() % screen_height;

		
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(Message);

		Score += 1;
		if (Score == 10 || Score == 100)
		{
			Message_rect.w *= 2;
		}

		std::string scoreText = std::to_string(Score);
		surfaceMessage = TTF_RenderText_Blended(PointFont, scoreText.c_str(), white);
		Message = SDL_CreateTextureFromSurface(&_renderer, surfaceMessage);
		std::cout << "You scored! Your Score is: " << Score << std::endl;

		_snake.SnakePushBack(_snake);

		_ball.SetBallPosX(randomBallPosX);
		_ball.SetBallPosY(randomBallPosY);
	}
};



void GameRules::RenderPoints(SDL_Renderer& _renderer)
{
	SDL_RenderCopy(&_renderer, Message, NULL, &Message_rect);


	SDL_FreeSurface(scoreSurfaceMessage);
	SDL_DestroyTexture(scoreMessage);

	scoreSurfaceMessage = TTF_RenderText_Blended(PointFont, "Score:", white);
	scoreMessage = SDL_CreateTextureFromSurface(&_renderer, scoreSurfaceMessage);

	SDL_RenderCopy(&_renderer, scoreMessage, NULL, &score_rect);
}