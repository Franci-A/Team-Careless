#pragma once
#include <time.h>
#include <ctime>



struct TIME // Cr�er au d�but, Structure TIME constante
{
	float time = 0.0f;
	float previousTime = 0.0f;
	float deltaTime = 0.0f;
};

float Time(); // return 'Current Time'

void Update(TIME T); // Appeler chaque frame