#include <memory>

#include <glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

#include "Sprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"

namespace Renderer
{
	Sprite::Sprite(const std::shared_ptr<TextureManager> pTexture, const std::shared_ptr<ShaderManager> pShader, const glm::vec2& position, const glm::vec2& size, const float rotation) :
		pTexture(std::move(pTexture)), pShader(std::move(pShader)), position(position), size(size), rotation(rotation)
	{
		const GLfloat vertexCoords[] =
		{
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
		};

		const GLfloat textureCoords[] =
		{
			0.f, 0.f,
			0.f, 1.f,
			1.f, 1.f,

			1.f, 1.f,
			1.f, 0.f,
			0.f, 0.f,
		};

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &vetrexCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vetrexCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glGenBuffers(1, &textureCoordsVBO);
		glBindBuffer(GL_ARRAY_BUFFER, textureCoordsVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoordsVBO), &textureCoordsVBO, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	};
	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &vetrexCoordsVBO);
		glDeleteBuffers(1, &textureCoordsVBO);
		glDeleteVertexArrays(1, &VAO);
	}
	void Sprite::Render() const
	{
		pShader->UseShader();

		glm::mat4 model()
	}
	void Sprite::SetPosition(const glm::vec2& position)
	{
		this->position = position;
	}
	void Sprite::SetSize(const glm::vec2& size)
	{
		this->size = size;
	}
	void Sprite::SetRotation(const float rotation)
	{

	}
}