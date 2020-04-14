#include "GameRules.h"


GameRules::GameRules() :
	PointFont(TTF_OpenFont("F:/GitRepository/Snake/TonisSnake/assets/arial.ttf", 150))
	/*PointFont(TTF_OpenFont("arial.ttf", 50))*/
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

	Score_rect.w = 55;
	Score_rect.h = 20;
	Score_rect.x = 0;
	Score_rect.y = 0;
}


void GameRules::LosingCondition(Snake& _snake)
{
	for (int i = _snake.Getm_SnakeSize() - 1; i > 1; i--)
	{
		if (_snake.GetSnakeIndexPosX(0) < _snake.GetSnakeIndexPosX(i) + snakeRectWidth && 
			_snake.GetSnakeIndexPosX(0) > _snake.GetSnakeIndexPosX(i) - snakeRectWidth &&
			_snake.GetSnakeIndexPosY(0) >= _snake.GetSnakeIndexPosY(i) && 
			_snake.GetSnakeIndexPosY(0) <= _snake.GetSnakeIndexPosY(i) + snakeRectHeight)
		{
			std::cout << "You lost! Your final Points are: " << Score << std::endl;
			SDL_Quit();
		}
	}
};

void GameRules::UpdatePoints(Snake& _snake, Ball& _ball, SDL_Renderer& _renderer)
{
	if (_ball.GetBallPosX() + ballRadius + Offset >= _snake.GetSnakeIndexPosX(0) && 
		_ball.GetBallPosX() - ballRadius - Offset <= _snake.GetSnakeIndexPosX(0) &&
		_ball.GetBallPosY() + ballRadius + Offset >= _snake.GetSnakeIndexPosY(0) && 
		_ball.GetBallPosY() - ballRadius - Offset <= _snake.GetSnakeIndexPosY(0))
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
		std::cout << "You scored! Your Points are: " << Score << std::endl;



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

	SDL_RenderCopy(&_renderer, scoreMessage, NULL, &Score_rect);
}