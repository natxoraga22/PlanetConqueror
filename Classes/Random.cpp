//
//  Random.cpp
//  PlanetConqueror
//
//  Created by Ignacio Raga Llorens on 13/11/15.
//
//

#include "Random.h"


void Random::setSeed()
{
    srand((unsigned int)time(nullptr));
}

int Random::getRandomInt(int min, int max)
{
    int interval = max - min + 1;
    int random = (rand() % interval) + min;
    return random;
}

float Random::getRandomFloat(float min, float max)
{
    float interval = max - min;
    float random = (float)rand() / (float)(RAND_MAX/interval) + min;
    return random;
}