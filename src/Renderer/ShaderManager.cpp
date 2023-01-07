#include "ShaderManager.h"

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace RenderEngine 
{
    ShaderManager::ShaderManager(const std::string& vertexShader, const std::string& fragmentShader)
    {
        GLuint vertexShaderId;
        if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId)) 
        {
            std::cerr << "VERTEX SHADER compile-time error" << std::endl;
            return;
        }

        GLuint fragmentShaderId;
        if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId)) 
        {
            std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
            glDeleteShader(vertexShaderId);
            return;
        }

        id = glCreateProgram(); 
        glAttachShader(id, vertexShaderId); 
        glAttachShader(id, fragmentShaderId); 
        glLinkProgram(id);

        GLint success;
        glGetProgramiv(id, GL_LINK_STATUS, &success);  
        if (!success) 
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(id, 1024, nullptr, infoLog);
            std::cerr << "Link error: " << infoLog << std::endl;
        }
        else 
        {
            isCompiled = true; 
        }

        glDeleteShader(vertexShaderId);  
        glDeleteShader(fragmentShaderId); 
    }


    bool ShaderManager::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderId)
    {
        shaderId = glCreateShader(shaderType);
        const char* code = source.c_str();
        glShaderSource(shaderId, 1, &code, nullptr);
        glCompileShader(shaderId);

        GLint success;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            GLchar infoLog[1024];
            glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
            std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
            return false;
        }
        return true;
    }

    ShaderManager::~ShaderManager()
    {
        glDeleteProgram(id);
    }

    void ShaderManager::UseShader() const
    {
        glUseProgram(id);
    }

    ShaderManager& ShaderManager::operator=(ShaderManager&& shaderManager) noexcept
    {
        glDeleteProgram(id);
        id = shaderManager.id;
        isCompiled = shaderManager.isCompiled;

        shaderManager.id = 0;
        shaderManager.isCompiled = false;
        return *this;
    }

    ShaderManager::ShaderManager(ShaderManager&& shaderManager) noexcept
    {
        id = shaderManager.id;
        isCompiled = shaderManager.isCompiled;

        shaderManager.id = 0;
        shaderManager.isCompiled = false;
    }

    void ShaderManager::SetInt(const std::string& name, const GLint value)
    {
        glUniform1i(glGetUniformLocation(id, name.c_str()), value);
    }

    void ShaderManager::SetFloat(const std::string& name, const GLfloat value)
    {
        glUniform1f(glGetUniformLocation(id, name.c_str()), value);
    }

    void ShaderManager::SetMatrix4x4(const std::string& name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
    }
}
