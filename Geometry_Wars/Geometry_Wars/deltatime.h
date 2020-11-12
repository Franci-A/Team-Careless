#pragma once
#include <time.h>
#include <ctime>


struct TIME // Créer au début, Structure TIME constante
{
	float currentTime = 0.0f;
	float previousTime = 0.0f;
	float deltaTime = 0.0f;
};


float Time(); // return 'Current Time'

void Update(TIME* T); // Appeler chaque frame