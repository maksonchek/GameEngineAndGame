#include "ShaderManager.h"
#include <glad/glad.h>
#include <string>
#include <iostream>

namespace Renderer {
	ShaderManager::ShaderManager(const std::string& vertexShader, const std::string& fragmentShader)
	{
		GLuint vertexShaderID;
		if (!isShaderCreated(vertexShader, GL_VERTEX_SHADER, vertexShaderID))
		{
			std::cerr << "VERTEX SHADER compile time error" << std::endl;
			return;
		}
		GLuint fragmentShaderID;
		if (!isShaderCreated(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID))
		{
			std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
			glDeleteShader(vertexShaderID);
			return;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertexShaderID);
		glAttachShader(ID, fragmentShaderID);
		glLinkProgram(ID);

		GLint success;
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link-time error:\n" << infoLog << std::endl;
		}
		else
		{
			isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}
	bool ShaderManager::isShaderCreated(const std::string& source, const GLenum shaderType, GLuint& shaderID)
	{
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
		}
		return true;
	}

	ShaderManager::~ShaderManager()
	{
		glDeleteProgram(ID);
	}
	
	void ShaderManager::UseShader() const
	{
		glUseProgram(ID);
	}
	
	ShaderManager& ShaderManager::operator = (ShaderManager&& shaderManager) noexcept
	{
		glDeleteProgram(ID);
		ID = shaderManager.ID;
		isCompiled = shaderManager.isCompiled;
		shaderManager.ID = 0;
		shaderManager.isCompiled = false;
		return *this;
	}
	ShaderManager::ShaderManager(ShaderManager&& shaderManager) noexcept
	{
		glDeleteProgram(ID);
		ID = shaderManager.ID;
		isCompiled = shaderManager.isCompiled;

		shaderManager.ID = 0;
		shaderManager.isCompiled = false;
	}
}