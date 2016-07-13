#include "PlatformsManager.h"
#include "RNG.h"

#include <iostream>
#include <fstream>

PlatformsManager* g_platformsManager;

PlatformsManager::PlatformsManager()
{
	g_platformsManager = this;
}


PlatformsManager::~PlatformsManager()
{
}

void PlatformsManager::CreateMap(const std::string &file, float platformSide)
{
	std::ifstream f;

	f.open(file);

	int rows, columns;
	f >> rows >> columns;

	int val;

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			f >> val;
			for (int k = 0; k <= val; ++k)
			{
				m_platforms.push_back(new Platform(Vec3(platformSide * i, k * platformSide, platformSide * j), platformSide, i == rows - 1 && j == columns - 1 && k == val));
			}
		}
	}

}

int PlatformsManager::GetPlatformsNumber()
{
	return m_platforms.size();
}

Platform* PlatformsManager::GetPlatform(int index)
{
	return m_platforms.at(index);
}
