#include "Bullet.h";


Bullet* SpawnBall(int playerX, int playerY, int cursorX, int cursorY, Bullet* newBall) //Remplacer player X et Y par ptr -> Player
{
	if (sqrt(powf(cursorX - playerX, 2) + powf(cursorY - playerY, 2)) != 0) {
		(*newBall).X_offset = (10 * (cursorX - playerX)) / sqrt(powf(cursorX - playerX, 2) + powf(cursorY - playerY, 2));
		(*newBall).Y_offset = (10 * (cursorY - playerY)) / sqrt(powf(cursorX - playerX, 2) + powf(cursorY - playerY, 2));
	}

	//(*newBall).timer_StartPoint = GetTime();
	(*newBall).timer = 0.0f;

	return newBall;
}

// Mvmt - Update Position
void UpdatePosition(Bullet* ball, float deltaTime)
{
	//(*ball).timer = GetTime() - (*ball).timer_StartPoint;

	(*ball).posX = (*ball).X_offset * (*ball).speed *deltaTime;
	(*ball).posY = (*ball).Y_offset * (*ball).speed * deltaTime;

	(*ball).visual.move((*ball).posX, (*ball).posY);
}

void Check_Wall_Collision(Bullet* ball, int width, int height)
{
	if (ball->visual.getPosition().x + ball->visual.getRadius() > width || ball->visual.getPosition().x - ball->visual.getRadius() < 0)
	{
		ball->X_offset = -ball->X_offset;
		if (ball->X_offset < 0) {
			ball->visual.setPosition(width - ball->visual.getRadius() *2, ball->visual.getPosition().y);
		}
		else {
			ball->visual.setPosition(ball->visual.getRadius() *2, ball->visual.getPosition().y);
		}
		if (ball->type == BALL_TYPE::ACCELERATOR && ball->speed <= 275) {
			ball->speed += 10;
		}
	}
	if (ball->visual.getPosition().y + ball->visual.getRadius() > height || ball->visual.getPosition().y - ball->visual.getRadius() < 0)
	{

		ball->Y_offset = -ball->Y_offset;
		if (ball->Y_offset < 0) {
			ball->visual.setPosition(ball->visual.getPosition().x, height - ball->visual.getRadius());
		}
		else {
			ball->visual.setPosition(ball->visual.getPosition().x, ball->visual.getRadius() *2);
		}
		if (ball->type == BALL_TYPE::ACCELERATOR && ball->speed <= 275) {
			ball->speed += 10;
		}
	}
}

// Infos/Références Bullet Types
void InitializeBulletpedia(std::map<BALL_TYPE, Bullet_Powerup>& bulletpedia)
{
	Bullet_Powerup Default{
		BALL_TYPE::DEFAULT,
		sf::CircleShape::CircleShape(10.0f),
		120,
		1
	};
	bulletpedia[BALL_TYPE::DEFAULT] = Default;

	Bullet_Powerup Triple{
		BALL_TYPE::TRIPLE,
		sf::CircleShape::CircleShape(9.5f),
		130,
		3
	};
	bulletpedia[BALL_TYPE::TRIPLE] = Triple;

	Bullet_Powerup Big{
		BALL_TYPE::BIG,
		sf::CircleShape::CircleShape(30.0f),
		90,
		1
	};
	bulletpedia[BALL_TYPE::BIG] = Big;

	Bullet_Powerup Accelerator{
		BALL_TYPE::ACCELERATOR,
		sf::CircleShape::CircleShape(10.0f),
		105,
		1
	};
	bulletpedia[BALL_TYPE::ACCELERATOR] = Accelerator;

	Bullet_Powerup Snake{
		BALL_TYPE::SNAKE,
		sf::CircleShape::CircleShape(11.0f),
		110,
		5
	};
	bulletpedia[BALL_TYPE::SNAKE] = Snake;
}
