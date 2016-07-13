#include "Input.h"
#include "tinyxml\tinyxml.h"
#include "Defines.h"
#include <iostream>

Input* g_input;

Input::Input()
{
	LoadInput("../Resources/XML/Input.xml");
	g_input = this;
}


Input::~Input()
{
}

void Input::LoadInput(const std::string& file)
{
	TiXmlDocument doc;
	doc.LoadFile(file.c_str());

	auto parent = doc.FirstChildElement();

	int i = 0;

	for (auto e = parent->FirstChildElement(); e; e = e->NextSiblingElement())
	{
		int code;
		auto name = e->Value();
		e->QueryIntAttribute("code", &code);

		m_keysAndCode[name] = code;
		m_keysAndIndex[name] = i++;
	}

	m_lastState = std::vector<bool>(m_keysAndCode.size(), false);
	m_currentState = std::vector<bool>(m_keysAndCode.size(), false);
}

void Input::Update()
{
	m_lastState = m_currentState;

	for (auto e : m_keysAndCode)
	{
		m_currentState[m_keysAndIndex[e.first]] = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e.second)))
		{
			m_currentState[m_keysAndIndex[e.first]] = true;
		}
	}
}

bool Input::WasKeyJustPressed(const std::string& button)
{
	if (m_keysAndIndex.find(button) != m_keysAndIndex.end())
		return m_currentState[m_keysAndIndex[button]] && !m_lastState[m_keysAndIndex[button]];
	std::cout << "Invalid Key Check! " << button << std::endl;
	return false;
}

bool Input::IsKeyPressed(const std::string& button)
{
	if (m_keysAndIndex.find(button) != m_keysAndIndex.end())
		return m_currentState[m_keysAndIndex[button]];
	std::cout << "Invalid Key Check! " << button << std::endl;
	return false;
}