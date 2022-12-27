#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"

#include <glad/glad.h>
#include <glm/vec2.hpp>

#include <memory>
#include <string>

namespace RenderEngine {

    class TextureManager;
    class ShaderManager;

    class Sprite {
    public:

        struct FrameParams {
            FrameParams(const glm::vec2 leftBottom, const glm::vec2 rightTop, const uint64_t duration)
                : leftBottom(leftBottom)
                , rightTop(rightTop)
                , duration(duration)
            {}
            glm::vec2 leftBottom;
            glm::vec2 rightTop;
            uint64_t duration;
        };

        Sprite(std::shared_ptr<TextureManager> pTexture,
            std::string initialTile,
            std::shared_ptr<ShaderManager> pShaderManager);


        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;
        void Render(const glm::vec2& position, const glm::vec2& size, const float rotation, const size_t frameId = 0) const;

        void InsertFrames(std::vector<FrameParams> framesParams);
        uint64_t GetFrameDuration(const size_t frameId) const;
        size_t GetFramesCount() const;
        ~Sprite();

    protected:
        std::shared_ptr<TextureManager> pTexture;
        std::shared_ptr<ShaderManager> pShaderManager;

        VertexArray vertexArray;
        VertexBuffer vertexCoordsBuffer;
        VertexBuffer textureCoordsBuffer;
        IndexBuffer indexBuffer;

        std::vector<FrameParams> framesParams;
        mutable size_t lastFrameId;
    };

}