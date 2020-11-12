#include "DeltaTime.h";



float GetTime() // return -> current Time (since window opened)
{
	return (float)clock() / CLOCKS_PER_SEC;
}

void Update(Timer T) // Appeler chaque frame
{
	T.previousTime = T.time;

	T.time = GetTime();

	T.deltaTime = T.previousTime - T.time;
}