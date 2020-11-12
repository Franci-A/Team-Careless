#pragma once
#include <time.h>
#include <ctime>



struct Timer // Cr�er au d�but, Structure TIME constante
{
	float time = 0.0f;
	float previousTime = 0.0f;
	float deltaTime = 0.0f;
};

float GetTime(); // return 'Current Time'

void Update(Timer T); // Appeler chaque frame