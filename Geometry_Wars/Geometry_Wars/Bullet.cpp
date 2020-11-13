#include "Bullet.h";
#include "DeltaTime.h";



Bullet* SpawnBall(int playerX, int playerY, int cursorX, int cursorY, BALL_TYPE type, Bullet* newBall) //Remplacer player X et Y par ptr -> Player
{

	(*newBall).type = type;
	(*newBall).X_offset = cursorX - playerX;
	(*newBall).Y_offset = cursorY - playerY;
	//if (sqrt(powf(cursorX, 2) + powf(cursorY, 2)) != 0) {
	//	(*newBall).X_offset = (10 * (cursorX - playerX)) / sqrt(powf(cursorX - playerX, 2) + powf(cursorY - playerY, 2));
	//	(*newBall).Y_offset = (10 * (cursorY - playerY)) / sqrt(powf(cursorX - playerX, 2) + powf(cursorY - playerY, 2));
	//}
	(*newBall).speed = .1f;

	(*newBall).timer_StartPoint = GetTime();
	(*newBall).timer = 0.0f;

	return newBall;
}

// Mvmt - Update Position
void UpdatePosition(Bullet* ball)
{
	(*ball).timer = GetTime() - (*ball).timer_StartPoint;

	(*ball).posX = (*ball).X_offset * (*ball).speed ;
	(*ball).posY = (*ball).Y_offset * (*ball).speed;

	(*ball).visual.move((*ball).posX, (*ball).posY);
}

void Check_Wall_Collision(Bullet* ball, int width, int height)
{
	if (ball->visual.getPosition().x + ball->visual.getRadius() >= width || ball->visual.getPosition().x - ball->visual.getRadius() <= 0)
	{
		ball->X_offset = -ball->X_offset;
	}
	if (ball->visual.getPosition().y + ball->visual.getRadius() >= height || ball->visual.getPosition().y - ball->visual.getRadius() <= 0)
	{
		ball->Y_offset = -ball->Y_offset;
	}
}

// CatchBall(ptr ball) // Si collision Player-Ball
// delete Ball