#pragma once

#include <glad/glad.h>
#include <string>
#include<glm/mat4x4.hpp>
#include<glm/gtc/type_ptr.hpp>

namespace Renderer {
	class ShaderManager
	{
	public:
		ShaderManager(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderManager();

		bool IsCompiled() const
		{
			return isCompiled;
		}
		
		void UseShader() const;
		
		void SetInt(const std::string& name, const GLint value);

		void SetMatrix4x4(const std::string& name, const glm::mat4& matrix);

		ShaderManager() = delete;
		ShaderManager(ShaderManager&) = delete;
		ShaderManager& operator = (const ShaderManager&) = delete;
		ShaderManager& operator = (ShaderManager&& shaderManager) noexcept;
		ShaderManager(ShaderManager&& shaderManager) noexcept;

	private:
		bool isCompiled = false;
		bool isShaderCreated(const std::string& source, const GLenum shaderType, GLuint& shaderID);
		GLuint ID = 0;
	}; 
}