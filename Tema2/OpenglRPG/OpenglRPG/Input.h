#pragma once
#include "SFML\Window.hpp"
#include <vector>
#include <map>
class Input
{
public:
	Input();
	~Input();

	void											Update();
	bool											WasKeyJustPressed(const std::string& button);
	bool											IsKeyPressed(const std::string& button);

private:

	void											LoadInput(const std::string& file);

	std::map<std::string, int>						m_keysAndCode;
	std::map<std::string, int>						m_keysAndIndex;
	std::vector<bool>								m_currentState;
	std::vector<bool>								m_lastState;

};

extern Input* g_input;