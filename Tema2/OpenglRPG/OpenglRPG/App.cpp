#include "App.h"
#include "glew\glew.h"
#include "Defines.h"
#include "Player.h"
#include "Platform.h"

#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp"


#include <iostream>

App* g_app;

App::App()
{
	m_windowWidth = 800;
	m_windowHeight = 600;

	glewExperimental = true;

	m_settings.depthBits = 24;
	m_settings.stencilBits = 8;
	m_settings.antialiasingLevel = 4;
	m_settings.majorVersion = 3;
	m_settings.minorVersion = 0;

	m_window = new sf::Window(sf::VideoMode(m_windowWidth, m_windowHeight), "SFML graphics with OpenGL", sf::Style::Default, m_settings);
	m_window->setFramerateLimit(60);
	m_window->setVerticalSyncEnabled(true);

	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_DEPTH_TEST);
	glewInit();

	LoadShaders();

	m_gameRunning = true;

	g_app = this;
}


App::~App()
{
}

void App::Run()
{
	sf::Clock clock;
	sf::Time deltaTime;

	m_thirdPersonCamera = new Camera(Camera::TYPE::TPC);
	m_firstPersonCamera = new Camera(Camera::TYPE::FPC);

	Object *player = new Player(Vec3(0, 10, 0), m_thirdPersonCamera, m_firstPersonCamera);
	g_platformsManager->CreateMap("../Resources/map.txt", 10.f);


	bool running = true;

	while (running)
	{
		sf::Event event;
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				running = false;
			}
			else if (event.type == sf::Event::Resized)
			{
				m_windowWidth = event.size.width;
				m_windowHeight = event.size.height;
			}
		}

		deltaTime = clock.restart();

		g_input->Update();
		if (m_gameRunning)
			player->Update(deltaTime.asSeconds());

		if (m_gameRunning)
		{
			for (int i = 0; i < g_platformsManager->GetPlatformsNumber(); ++i)
			{
				player->CheckCollision(g_platformsManager->GetPlatform(i));
			}
		}

		if (g_input->WasKeyJustPressed("KeyB"))
		{
			std::cout << player->GetPosition().x << " " << player->GetPosition().y << " " << player->GetPosition().z << std::endl;
		}


		m_thirdPersonCamera->LoadMatrices();
		m_thirdPersonCamera->SetViewport();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		player->Draw();
		for (int i = 0; i < g_platformsManager->GetPlatformsNumber(); ++i)
		{
			g_platformsManager->GetPlatform(i)->Draw();
		}


		m_firstPersonCamera->LoadMatrices();
		m_firstPersonCamera->SetViewport();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < g_platformsManager->GetPlatformsNumber(); ++i)
		{
			g_platformsManager->GetPlatform(i)->Draw();
		}

		m_window->display();

		glDisable(GL_SCISSOR_TEST);
	}

	delete player;
}

void App::LoadShaders()
{
	std::vector<std::pair<std::string, GLenum> > shadersFiles;
	shadersFiles.push_back(std::make_pair("../Resources/Shaders/shader_vertex.glsl", GL_VERTEX_SHADER));
	shadersFiles.push_back(std::make_pair("../Resources/Shaders/shader_fragment.glsl", GL_FRAGMENT_SHADER));

	uint programIndex = g_shadersManager->CreateShaderProgram(shadersFiles);
	g_shadersManager->UseProgram(programIndex);
}
