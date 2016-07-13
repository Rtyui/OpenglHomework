#include "RNG.h"
#include <stdlib.h>
#include <time.h>

RNG::RNG()
{
}

RNG::~RNG()
{
}

float RNG::Float(float min, float max)
{
	return min + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max - min)));
}

uint RNG::UInt(uint min, uint max)
{
	return (uint)((rand() % (max - min)) + min);
}

int RNG::Int(int min, int max)
{
	return min + (rand() * (int)(max - min) / RAND_MAX);
}

void RNG::InitiateSeed()
{
	srand((uint)time(NULL));
}

void RNG::SetSeed(uint seed)
{
	srand(seed);
}