#include "Sprite.h"

#include "ShaderManager.h"
#include "TextureManager.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer {

    Sprite::Sprite(const std::shared_ptr<TextureManager> pTextureManager,
                    const std::string initTile,
                      const std::shared_ptr<ShaderManager> pShaderManager,
                        const glm::vec2& position,
                          const glm::vec2& size,
                            const float rotation) : pTexture(std::move(pTextureManager))
                                                     , pShaderManager(std::move(pShaderManager))
                                                       , position(position)
                                                         , size(size)
                                                           , rotation(rotation) {
        const GLfloat vertexCoords[] = {

            0.f, 0.f,
            0.f, 1.f,
            1.f, 1.f,

            1.f, 1.f,
            1.f, 0.f,
            0.f, 0.f
        };

        auto tile = pTextureManager->GetTile(std::move(initTile));

        const GLfloat textureCoords[] = {

            tile.leftBottom.x, tile.leftBottom.y,
            tile.leftBottom.x, tile.rightTop.y,
            tile.rightTop.x, tile.rightTop.y,

            tile.rightTop.x, tile.rightTop.y,
            tile.rightTop.x, tile.leftBottom.y,
            tile.leftBottom.x, tile.leftBottom.y
        };

        glGenVertexArrays(1, &VertexArrayObject);
        glBindVertexArray(VertexArrayObject);

        glGenBuffers(1, &veretexCoordVBO);
        glBindBuffer(GL_ARRAY_BUFFER, veretexCoordVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glGenBuffers(1, &TextureCoordVBO);
        glBindBuffer(GL_ARRAY_BUFFER, TextureCoordVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void Sprite::Render() const
    {
        pShaderManager->UseShader();

        glm::mat4 model(1.f);
        
        model = glm::translate(model, glm::vec3(position, 0.f));
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
        model = glm::scale(model, glm::vec3(size, 1.f));

        glBindVertexArray(VertexArrayObject);
        pShaderManager->SetMatrix4x4("modelMat", model);

        glActiveTexture(GL_TEXTURE0);
        pTexture->Bind();

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
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
        this->rotation = rotation;
    }

    Sprite::~Sprite()
    {
        glDeleteBuffers(1, &veretexCoordVBO);
        glDeleteBuffers(1, &TextureCoordVBO);
        glDeleteVertexArrays(1, &VertexArrayObject);
    }
}