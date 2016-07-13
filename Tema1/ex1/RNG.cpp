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

unsigned RNG::UInt(unsigned min, unsigned max)
{
	return (unsigned)((rand() % (max - min)) + min);
}

int RNG::Int(int min, int max)
{
	return min + (rand() * (int)(max - min) / RAND_MAX);
}

void RNG::InitiateSeed()
{
	srand((unsigned)time(NULL));
}

void RNG::SetSeed(unsigned seed = (unsigned)time(NULL))
{
	srand(seed);
}