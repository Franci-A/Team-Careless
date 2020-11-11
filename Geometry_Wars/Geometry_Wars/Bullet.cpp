#include "bullet.h";
#include "deltatime.cpp";



Bullet* SpawnBall(int playerX, int playerY, int cursorX, int cursorY, BALL_TYPE type) //Remplacer player X et Y par ptr -> Player
{
	Bullet* newBall = new Bullet;
	(*newBall).type = type;
	(*newBall).X_offset = cursorX - playerX; //(*player).posX
	(*newBall).Y_offset = cursorY - playerY; //(*player).posY
	(*newBall).speed = 5.0f;

	(*newBall).timer_StartPoint = Time();
	(*newBall).timer = 0.0f;

	return newBall;
}

// Mvmt - Update Position
void UpdatePosition(Bullet* ball)
{
	(*ball).timer = Time() - (*ball).timer_StartPoint;

	(*ball).posX += (*ball).X_offset * (*ball).speed; // * clock()...
}

//void Check_Wall_Collision(ptr ball)
//{ if (ball.posX + ballWidth >= PlayZonePosX + PlayZoneWidth || ball.posX - ballWidth <= PlayZonePosX)
//		{ ball.X_offset = -ball.X_offset }
//	if (ball.posY + ballHeight >= PlayZonePosY + PlayZoneHeight || ball.posY - ballHeight <= PlayZonePosY)
//		{ ball.Y_offset = -ball.Y_offset }
//}

// CatchBall(ptr ball) // Si collision Player-Ball
// delete Ball