#include "ShadersProgramsManager.h"
#include "glm\gtc\type_ptr.hpp"
#include "App.h"

#include <fstream>
#include <iostream>

ShadersProgramsManager* g_shadersManager;

ShadersProgramsManager::ShadersProgramsManager()
{
	m_currentProgram = -1;
	g_shadersManager = this;
}

ShadersProgramsManager::~ShadersProgramsManager()
{
}

uint ShadersProgramsManager::CreateShaderProgram(const std::vector<std::pair<std::string, GLenum> > shaderFiles)
{
	std::vector<uint> shaders;

	for (auto p : shaderFiles)
	{
		shaders.push_back(LoadShader(p.first, p.second));
	}

	uint glProgramObject = glCreateProgram();

	for (auto s : shaders)
	{
		glAttachShader(glProgramObject, s);
	}
	glLinkProgram(glProgramObject);

	int infoLogLength = 0, linkResult = 0;

	glGetProgramiv(glProgramObject, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE){
		glGetProgramiv(glProgramObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> program_log(infoLogLength);
		glGetProgramInfoLog(glProgramObject, glProgramObject, NULL, &program_log[0]);
		std::cout << "Shader Loader : EROARE DE LINKARE" << std::endl << &program_log[0] << std::endl;
		std::terminate();
	}

	for (auto s : shaders)
	{
		glDeleteShader(s);
	}

	m_programs.push_back(glProgramObject);

	return (m_programs.size() - 1);
}

uint ShadersProgramsManager::LoadShader(const std::string &shaderFile, GLenum shaderType)
{
	std::string shaderCode;
	std::ifstream file(shaderFile.c_str(), std::ios::in);

	if (!file.good())
	{
		std::cout << "File " << shaderFile.c_str() << " not found." << std::endl;
		std::terminate();
	}

	file.seekg(0, std::ios::end);
	shaderCode.resize((uint)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	int infoLogLength = 0, compileResult = 0;
	unsigned int glShaderObject;

	glShaderObject = glCreateShader(shaderType);
	const char *shaderCodePtr = shaderCode.c_str();
	const int shaderCodeSize = shaderCode.size();
	glShaderSource(glShaderObject, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(glShaderObject);
	glGetShaderiv(glShaderObject, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE){
		std::string strShaderType = "";
		if (shaderType == GL_VERTEX_SHADER) strShaderType = "vertex shader";
		if (shaderType == GL_TESS_CONTROL_SHADER) strShaderType = "tess control shader";
		if (shaderType == GL_TESS_EVALUATION_SHADER) strShaderType = "tess evaluation shader";
		if (shaderType == GL_GEOMETRY_SHADER) strShaderType = "geometry shader";
		if (shaderType == GL_FRAGMENT_SHADER) strShaderType = "fragment shader";
		if (shaderType == GL_COMPUTE_SHADER) strShaderType = "compute shader";

		glGetShaderiv(glShaderObject, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char> shaderLog(infoLogLength);
		glGetShaderInfoLog(glShaderObject, infoLogLength, NULL, &shaderLog[0]);
		std::cout << "Shader Loader: COMPILE ERROR for " << strShaderType.c_str() << std::endl << &shaderLog[0] << std::endl;
		return 0;
	}

	return glShaderObject;
}

uint ShadersProgramsManager::GetProgram(uint index)
{
	return m_programs[index];
}

uint ShadersProgramsManager::GetProgram()
{
	return m_currentProgram;
}

uint ShadersProgramsManager::GetUniformLocation(uint programIndex, const std::string& variable)
{
	return glGetUniformLocation(m_programs[programIndex], variable.c_str());
}

void ShadersProgramsManager::UseProgram(uint index)
{
	m_currentProgram = index;
	glUseProgram(m_programs[index]);
}

void ShadersProgramsManager::SetViewMatrix(glm::mat4 view)
{
	glUniformMatrix4fv(GetUniformLocation(0, "View"), 1, false, glm::value_ptr(view));
}

void ShadersProgramsManager::SetProjectionMatrix(glm::mat4 projection)
{
	glUniformMatrix4fv(GetUniformLocation(0, "Projection"), 1, false, glm::value_ptr(projection));
}

void ShadersProgramsManager::SetModelMatrix(glm::mat4 model)
{
	glUniformMatrix4fv(GetUniformLocation(0, "Model"), 1, false, glm::value_ptr(model));
}
