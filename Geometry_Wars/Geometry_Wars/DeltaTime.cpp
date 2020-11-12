#include "deltatime.h";


TIME T{ 0.0f, 0.0f, 0.0f };

float Time() // return -> current Time (since window opened)
{
	return (float)clock() / CLOCKS_PER_SEC;
}

void Update(TIME* T) // Appeler chaque frame
{
	(*T).previousTime = (*T).currentTime;

	(*T).currentTime = Time();

	(*T).deltaTime = (*T).currentTime - (*T).previousTime;
}