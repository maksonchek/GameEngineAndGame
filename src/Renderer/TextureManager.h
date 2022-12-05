#pragma once

#include <glad/glad.h>
#include <string>

namespace Renderer {
	class TextureManager
	{
	public:
		TextureManager(const GLuint width, const GLuint height, const unsigned char* textureBites, const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR, const GLenum wrapMode = GL_CLAMP_TO_EDGE);
		TextureManager() = delete;
		TextureManager(const TextureManager&) = delete;
		TextureManager& operator = (const TextureManager&) = delete;

		TextureManager& operator = (TextureManager&& texture);
		TextureManager(TextureManager&& texture);
		~TextureManager();

		void Bind() const;

	private:
		GLuint id;
		GLenum mode;
		unsigned int width;
		unsigned int height;
	};
}