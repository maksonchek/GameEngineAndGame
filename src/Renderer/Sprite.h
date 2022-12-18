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
                   std::shared_ptr<ShaderManager> pShaderManager);

        ~Sprite();

        virtual void Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const;

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

    protected:
        
        VertexArray vertexArray;
        VertexBuffer vertexBuffer;
        VertexBuffer textureBuffer;
        IndexBuffer indexBuffer;

        std::shared_ptr<TextureManager> pTexture;
        std::shared_ptr<ShaderManager> pShaderManager;
};

}