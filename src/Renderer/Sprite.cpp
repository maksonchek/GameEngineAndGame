#include "Sprite.h"

#include "ShaderManager.h"
#include "TextureManager.h"
#include "Renderer.h"
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace RenderEngine {

    Sprite::Sprite(std::shared_ptr<TextureManager> pTextureManager,
                     std::string initTile,
                       std::shared_ptr<ShaderManager> pShaderManager) : pTexture(std::move(pTextureManager))
                                                     , pShaderManager(std::move(pShaderManager)) {
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

        vertexBuffer.InitializeBuffer(vertexCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout vertexLayoutCoords;
        vertexLayoutCoords.AddElementLayoutFloat(2, false);
        vertexArray.AddVertexBuffer(vertexBuffer, vertexLayoutCoords);

        textureBuffer.InitializeBuffer(textureCoords, 2 * 4 * sizeof(GLfloat));
        VertexBufferLayout textureLayoutCoords;
        textureLayoutCoords.AddElementLayoutFloat(2, false);
        vertexArray.AddVertexBuffer(textureBuffer, textureLayoutCoords);

        indexBuffer.InitializeBuffer(indexes, 6);

        vertexArray.UnBindBuffer();
        indexBuffer.UnBindBuffer();
    }

    void Sprite::Render(const glm::vec2& position, const glm::vec2& size, const float rotation) const
    {
        pShaderManager->UseShader();

        glm::mat4 model(1.f);
        
        model = glm::translate(model, glm::vec3(position, 0.f));
        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.f));
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.f, 0.f, 1.f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.f));
        model = glm::scale(model, glm::vec3(size, 1.f));

        pShaderManager->SetMatrix4x4("modelMat", model);

        glActiveTexture(GL_TEXTURE0);
        pTexture->Bind();

        Renderer::RenderGraphics(vertexArray, indexBuffer, *pShaderManager);
    }

    Sprite::~Sprite()
    {
    }
}