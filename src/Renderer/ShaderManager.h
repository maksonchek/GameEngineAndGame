#pragma once

#include <glad/glad.h>
#include <string>

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