#include "bullet.h";


Bullet* SpawnBall(int playerX, int playerY, int cursorX, int cursorY, BALL_TYPE type) //Remplacer player X et Y par ptr -> Player
{
	Bullet* newBall = new Bullet;
	(*newBall).type = type;
	(*newBall).X_offset = cursorX - playerX; //(*player).posX
	(*newBall).Y_offset = cursorY - playerY; //(*player).posY
	(*newBall).speed = 25.0f;

	(*newBall).visual.setRadius(7.0f);
	(*newBall).visual.setOrigin((*newBall).visual.getRadius() / 2, (*newBall).visual.getRadius() / 2);

	(*newBall).timer_StartPoint = T.currentTime;
	(*newBall).timer = 0.0f;

	(*newBall).posX += (*newBall).X_offset * (*newBall).speed * T.deltaTime;
	(*newBall).posY += (*newBall).Y_offset * (*newBall).speed * T.deltaTime;

	return newBall;
}

// Mvmt - Update Position
void MoveBall(Bullet* ball)
{
	(*ball).timer = T.currentTime - (*ball).timer_StartPoint;

	(*ball).posX += (*ball).X_offset * (*ball).speed * T.deltaTime;
	(*ball).posY += (*ball).Y_offset * (*ball).speed * T.deltaTime;
}

//void Check_Wall_Collision(ptr ball)
//{ if (ball.posX + ballWidth >= PlayZonePosX + PlayZoneWidth || ball.posX - ballWidth <= PlayZonePosX)
//		{ ball.X_offset = -ball.X_offset }
//	if (ball.posY + ballHeight >= PlayZonePosY + PlayZoneHeight || ball.posY - ballHeight <= PlayZonePosY)
//		{ ball.Y_offset = -ball.Y_offset }
//}

// CatchBall(ptr ball) // Si collision Player-Ball
// delete Ball

void DisplayBall(sf::RenderWindow* window, Bullet* ball)
{
	(*window).draw((*ball).visual);
}