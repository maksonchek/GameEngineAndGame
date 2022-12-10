#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>

namespace Renderer {

    class TextureManager;
    class ShaderManager;

    class Sprite {
	public:

        Sprite(const std::shared_ptr<TextureManager> pTexture,
                 const std::string initTile,
                   const std::shared_ptr<ShaderManager> pShaderProgram,
                     const glm::vec2& position = glm::vec2(0.f),
                       const glm::vec2& size = glm::vec2(1.f),
                         const float rotation = 0.f);

        ~Sprite();

        void Render() const;

        void SetPosition(const glm::vec2& position);

        void SetSize(const glm::vec2& size);

        void SetRotation(const float rotation);


        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

    private:

        GLuint VertexArrayObject;
        GLuint veretexCoordVBO;
        GLuint TextureCoordVBO;

        std::shared_ptr<TextureManager> pTexture;
        std::shared_ptr<ShaderManager> pShaderManager;

        glm::vec2 position;
        glm::vec2 size;
        float rotation;
};

}