#pragma once

#include <vector>
#include "glew\glew.h"
#include "Defines.h"

class ShadersProgramsManager
{
public:

	ShadersProgramsManager();
	~ShadersProgramsManager();

	uint					CreateShaderProgram(const std::vector<std::pair<std::string, GLenum> > shaderFiles);
	uint					GetUniformLocation(uint programIndex, const std::string& variable);
	uint					GetProgram(uint index);
	uint					GetProgram();
	void					UseProgram(uint index);
	void					SetViewMatrix(glm::mat4 view);
	void					SetProjectionMatrix(glm::mat4 projection);
	void					SetModelMatrix(glm::mat4 model);


private:

	uint					LoadShader(const std::string &shaderFile, GLenum shaderType);

	std::vector<uint>		m_programs;
	uint					m_currentProgram;

};

extern ShadersProgramsManager* g_shadersManager;