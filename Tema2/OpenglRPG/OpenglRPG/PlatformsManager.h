#pragma once

#include "Platform.h"

class PlatformsManager
{
public:
	PlatformsManager();
	~PlatformsManager();

	void								CreateMap(const std::string& file, float platformSide);
	int									GetPlatformsNumber();
	Platform*							GetPlatform(int index);

private:

	std::vector<Platform*>				m_platforms;
};

extern PlatformsManager* g_platformsManager;