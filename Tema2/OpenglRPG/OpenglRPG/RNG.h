#pragma once
#include "Defines.h"

class RNG
{
public:

	RNG();
	~RNG();


	static float				Float(float min, float max);
	static uint					UInt(uint min, uint max);
	static int					Int(int min, int max);

	static void					InitiateSeed();
	static void					SetSeed(uint seed);

};