<<<<<<< HEAD
#include "Sprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"
=======
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18
#include <memory>

#include <glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

<<<<<<< HEAD
=======
#include "Sprite.h"
#include "ShaderManager.h"
#include "TextureManager.h"
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18

namespace Renderer
{
	Sprite::Sprite(const std::shared_ptr<TextureManager> pTexture, const std::shared_ptr<ShaderManager> pShader, const glm::vec2& position, const glm::vec2& size, const float rotation) :
<<<<<<< HEAD
		pTexture(std::move(pTexture)), pShader(std::move(pShader)), this_position(position), this_size(size), this_rotation(rotation)
=======
		pTexture(std::move(pTexture)), pShader(std::move(pShader)), position(position), size(size), rotation(rotation)
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18
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

<<<<<<< HEAD
		glm::mat4 model(1.f);

		model = glm::translate(model, glm::vec3(this_position, 0.f));
		model = glm::translate(model, glm::vec3(0.5f * this_size.x, 0.5f * this_size.y, 0.f));
		model = glm::rotate(model, glm::radians(this_rotation), glm::vec3(0.f, 0.f, 1.f));
		model = glm::translate(model, glm::vec3(-0.5f * this_size.x, -0.5f*this_size.y, 0.f));
		model = glm::scale(model, glm::vec3(this_size, 1.f));

		glBindVertexArray(VAO);
		pShader->SetMatrix4x4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);
		pTexture->Bind();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}
	void Sprite::SetPosition(const glm::vec2& position)
	{
		this_position = position;
	}
	void Sprite::SetSize(const glm::vec2& size)
	{
		this_size = size;
	}
	void Sprite::SetRotation(const float rotation)
	{
		this_rotation = rotation;
=======
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

>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18
	}
}