#include "Sprite.h"

#include "ShaderManager.h"
#include "TextureManager.h"

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Renderer {

    Sprite::Sprite(std::shared_ptr<TextureManager> pTextureManager,
                     std::string initTile,
                       std::shared_ptr<ShaderManager> pShaderManager,
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
            1.f, 0.f,
        };

        auto tile = pTexture->GetTile(std::move(initTile));

        const GLfloat textureCoords[] = {

            tile.leftBottom.x, tile.leftBottom.y,
            tile.leftBottom.x, tile.rightTop.y,
            tile.rightTop.x, tile.rightTop.y,
            tile.rightTop.x, tile.leftBottom.y,
        };

        const GLint indexes[] = {

            0, 1, 2,
            2, 3, 0,
        };

        glGenVertexArrays(1, &VertexArrayObject);
        glBindVertexArray(VertexArrayObject);

        vertexBuffer.InitializeBuffer(vertexCoords, 2 * 4 * sizeof(GLfloat));
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        textureBuffer.InitializeBuffer(textureCoords, 2 * 4 * sizeof(GLfloat));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        indexBuffer.InitializeBuffer(indexes, 6 * sizeof(GLuint));

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
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
        glDeleteVertexArrays(1, &VertexArrayObject);
    }
}