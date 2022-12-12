#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>
#include "VertexArray.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace RenderEngine {

    class TextureManager;
    class ShaderManager;

    class Sprite {
	public:

        Sprite(std::shared_ptr<TextureManager> pTexture,
                 std::string initTile,
                    std::shared_ptr<ShaderManager> pShaderManager,
                     const glm::vec2& position = glm::vec2(0.f),
                       const glm::vec2& size = glm::vec2(1.f),
                         const float rotation = 0.f);

        ~Sprite();

        virtual void Render() const;

        void SetPosition(const glm::vec2& position);

        void SetSize(const glm::vec2& size);

        void SetRotation(const float rotation);


        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

    protected:
        
        VertexArray vertexArray;
        VertexBuffer vertexBuffer;
        VertexBuffer textureBuffer;
        IndexBuffer indexBuffer;

        std::shared_ptr<TextureManager> pTexture;
        std::shared_ptr<ShaderManager> pShaderManager;

        glm::vec2 position;
        glm::vec2 size;
        float rotation;
};

}