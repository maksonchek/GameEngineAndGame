<<<<<<< HEAD
#pragma once
=======
#pragma.once
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18

#include <glad/glad.h>
#include <memory>
#include <glm/vec2.hpp>

namespace Renderer
{
	class TextureManager;
	class ShaderManager;

	class  Sprite
	{
	public:
		 Sprite(const std::shared_ptr<TextureManager> pTexture, const std::shared_ptr<ShaderManager> pShader, 
			 const glm::vec2& position = glm::vec2(0.f), const glm::vec2& size = glm::vec2(1.f), const float rotation = 0.f);
		~ Sprite();

		Sprite(const Sprite&) = delete;
		Sprite& operator= (const Sprite&) = delete;

		void Render() const;
		void SetPosition(const glm::vec2& position);
		void SetSize(const glm::vec2& size);
		void SetRotation(const float rotation);

	private:
		std::shared_ptr<TextureManager> pTexture;
		std::shared_ptr<ShaderManager> pShader;
<<<<<<< HEAD
		glm::vec2 this_size;
		glm::vec2 this_position;
		float this_rotation;
=======
		glm::vec2 size;
		glm::vec2 position;
		float rotation;
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18
		GLuint VAO;
		GLuint vetrexCoordsVBO;
		GLuint textureCoordsVBO;
	};
}