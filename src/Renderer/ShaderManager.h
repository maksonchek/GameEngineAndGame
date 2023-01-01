#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace RenderEngine {
    class ShaderManager {
    public:

        ShaderManager(const std::string& vertexShader, const std::string& fragmentShader);
        ~ShaderManager();

        void UseShader() const;

        void SetInt(const std::string& name, const GLint value);

        void ShaderManager::SetFloat(const std::string& name, const GLfloat value);

        void SetMatrix4x4(const std::string& name, const glm::mat4& matrix);

        bool IsCompiled() const 
        { 
            return isCompiled; 
        }


        ShaderManager() = delete;
        ShaderManager(const ShaderManager&) = delete;
        ShaderManager& operator=(const ShaderManager&) = delete;
        ShaderManager& operator=(ShaderManager&& shaderManager) noexcept;
        ShaderManager(ShaderManager&& shaderManager) noexcept;

    private:

        bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderId);

        bool isCompiled = false;
        GLuint id = 0;
    };
}
