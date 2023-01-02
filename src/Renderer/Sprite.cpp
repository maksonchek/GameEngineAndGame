#include "Sprite.h"

#include "ShaderManager.h"
#include "TextureManager.h"
#include "Renderer.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RenderEngine {

    Sprite::Sprite(std::shared_ptr<TextureManager> pTexture,
                    std::string initialTile,
                    std::shared_ptr<ShaderManager> pShaderManager)
                    : pTexture(std::move(pTexture))
                    , pShaderManager(std::move(pShaderManager))
                    , lastFrameId(0)
    {
        const GLfloat vertexCoords[] = {
            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,
            1.f, 0.f
        };

        auto subTexture = this->pTexture->GetTile(std::move(initialTile));

        const GLfloat textureCoords[] = {
            subTexture.leftBottom.x, subTexture.leftBottom.y,
            subTexture.leftBottom.x, subTexture.rightTop.y,
            subTexture.rightTop.x,   subTexture.rightTop.y,
            subTexture.rightTop.x,   subTexture.leftBottom.y,
        };

        const GLuint indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        vertexCoordsBuffer.InitializeBuffer(vertexCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout vertexCoordsLayout;
        vertexCoordsLayout.AddElementLayoutFloat(2, false);
        vertexArray.AddVertexBuffer(vertexCoordsBuffer, vertexCoordsLayout);

        textureCoordsBuffer.InitializeBuffer(textureCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout textureCoordsLayout;
        textureCoordsLayout.AddElementLayoutFloat(2, false);
        vertexArray.AddVertexBuffer(textureCoordsBuffer, textureCoordsLayout);

        indexBuffer.InitializeBuffer(indices, 6);

        vertexArray.UnBindBuffer();
        indexBuffer.UnBindBuffer();
    }


    void Sprite::Render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer, const size_t frameId) const
    {
        if (lastFrameId != frameId)
        {
            lastFrameId = frameId;
            const FrameParams& currentFrameDescription = framesParams[frameId];

            const GLfloat textureCoords[] = {
                currentFrameDescription.leftBottom.x, currentFrameDescription.leftBottom.y,
                currentFrameDescription.leftBottom.x, currentFrameDescription.rightTop.y,
                currentFrameDescription.rightTop.x,   currentFrameDescription.rightTop.y,
                currentFrameDescription.rightTop.x,   currentFrameDescription.leftBottom.y,
            };

            textureCoordsBuffer.UpdateBuffer(textureCoords, 2 * 4 * sizeof(GLfloat));
        }

        pShaderManager->UseShader();

        glm::mat4 model(1.f);
        model = glm::translate(model, glm::vec3(position, 0.f));
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
        model = glm::scale(model, glm::vec3(size, 1.f));

        pShaderManager->SetMatrix4x4("modelMat", model);
        pShaderManager->SetFloat("layer", layer);
        glActiveTexture(GL_TEXTURE0);
        pTexture->Bind();

        Renderer::RenderGraphics(vertexArray, indexBuffer, *pShaderManager);
    }

    void Sprite::InsertFrames(std::vector<FrameParams> frameParams)
    {
        framesParams = std::move(frameParams);
    }

    double Sprite::GetFrameDuration(const size_t frameId) const
    {
        return framesParams[frameId].duration;
    }

    size_t Sprite::GetFramesCount() const
    {
        return framesParams.size();
    }
    Sprite::~Sprite()
    {
    }
}