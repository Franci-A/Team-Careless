#include "deltatime.h";



float Time() // return -> current Time (since window opened)
{
	return (float)clock() / CLOCKS_PER_SEC;
}

void Update(TIME T) // Appeler chaque frame
{
	T.previousTime = T.time;

	T.time = Time();

	T.deltaTime = T.previousTime - T.time;
}