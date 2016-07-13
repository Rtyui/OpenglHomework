#pragma once

#include "SFML\Window.hpp"
#include "ShadersProgramsManager.h"
#include "Input.h"
#include "Camera.h"
#include "PlatformsManager.h"

class App
{
public:
	App();
	~App();

	void						Run();
	void						LoadShaders();

	uint						m_windowWidth;
	uint						m_windowHeight;

	bool						m_gameRunning;

private:

	sf::Window*					m_window;
	sf::ContextSettings			m_settings;

	ShadersProgramsManager		m_shadersManager;
	Input						m_input;
	PlatformsManager			m_platformsManager;
	Camera*						m_firstPersonCamera;
	Camera*						m_thirdPersonCamera;

};

extern App* g_app;

