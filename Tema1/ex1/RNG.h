#pragma once

class RNG
{
public:

	RNG();
	~RNG();


	static float				Float(float min, float max);
	static unsigned				UInt(unsigned min, unsigned max);
	static int					Int(int min, int max);

	static void					InitiateSeed();
	static void					SetSeed(unsigned seed);

};