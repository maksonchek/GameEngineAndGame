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

    /*!
    * \brief �����, ���������� �� ��������� �������� � ������ �����, ������� �������, � ������ �����. �� ����, ��� ����������� ���������� �������� �������
    */
    class Sprite {
    public:
        /*!
        * ���������, �������� � ���� ��� ������, ����������� ��� ����� �������� �� �������, �.� ��������. ��������� ����� �������� ������� ������ � ������ SpriteAnimator
        */
        struct FrameParams {
            FrameParams(const glm::vec2 leftBottom, const glm::vec2 rightTop, const double duration) ///<���������� ������ ���������
                : leftBottom(leftBottom)
                , rightTop(rightTop)
                , duration(duration)
            {}
            glm::vec2 leftBottom; ///<���������� ������ ������� ���� �������� �������
            glm::vec2 rightTop; ///<���������� �������� �������� ���� �������� �������
            double duration; ///<������������ �����
        };

        /*!
        * ����������� ������� 
        * \param pTexture - ����� ��������� �� ��������� ������ ��������� �������
        * \param initialTile - ��� ��������, � ������� ���������������� ������� ������
        * \param pShaderManager - ��������� �� ��������� ������ ��������� ��������
        * ����������:
        * \code
                const GLfloat vertexCoords[] = { //����� ������ ���������� ������ ��� ���������� �������. ��� ���������� ����������� �������
                    0.f, 0.f,
                    0.f, 1.f,
                    1.f, 1.f,
                    1.f, 0.f
                };

                auto tile = this->pTexture->GetTile(std::move(initialTile)); // ��������

                const GLfloat textureCoords[] = {  //����� ������ ���������� ������ ��� ��������
                    tile.leftBottom.x, tile.leftBottom.y,
                    tile.leftBottom.x, tile.rightTop.y,
                    tile.rightTop.x,   tile.rightTop.y,
                    tile.rightTop.x,   tile.leftBottom.y,
                };

                const GLuint indices[] = { //����� ������ ������� ��� ���������� �������
                    0, 1, 2,
                    2, 3, 0
                };

                vertexCoordsBuffer.InitializeBuffer(vertexCoords, 2 * 4 * sizeof(GLfloat)); //����������������� ������ ����������� �������
                VertexBufferLayout vertexCoordsLayout; //������ ��������� ������� VertexBufferLayout ��� ����� ����������� �������� ������
                vertexCoordsLayout.AddElementLayoutFloat(2, false); //��������� � vertexCoordsLayout �������� ������
                vertexArray.AddVertexBuffer(vertexCoordsBuffer, vertexCoordsLayout); //��������� � ������ ������ ������ ����������� �������

                //�� �� ����� ������ � ������������ �������
                textureCoordsBuffer.InitializeBuffer(textureCoords, 2 * 4 * sizeof(GLfloat));
                VertexBufferLayout textureCoordsLayout;
                textureCoordsLayout.AddElementLayoutFloat(2, false);
                vertexArray.AddVertexBuffer(textureCoordsBuffer, textureCoordsLayout);

                //�������������� ��������� ������ ��� ��������
                indexBuffer.InitializeBuffer(indices, 6);

                //���������� ������� ��������� vertexArray � indexBuffer
                vertexArray.UnBindBuffer();
                indexBuffer.UnBindBuffer();
        * \endcode
        */
        Sprite(std::shared_ptr<TextureManager> pTexture, std::string initialTile, std::shared_ptr<ShaderManager> pShaderManager);

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        /*!
        * ������� ��������� �������
        * \param position - �������  ������� ��� ���������
        * \param size - ������� �������
        * \param rotation - ������� �������
        * \param layer - ���� ��� ��������� �� ������ (�� ��������� 0)
        * \param frameId - ������������� �������� �����-�������� (�� ��������� 0)
        * ����������:
        * \code
                if (lastFrameId != frameId) //���� ���������� ���� �� ����� ��������
                {
                    lastFrameId = frameId; //������� ���� ���������� �������
                    const FrameParams& currentFrameDescription = framesParams[frameId]; //��������� ��������� �����

                    const GLfloat textureCoords[] = { //��������� ���������� ������� ��������
                        currentFrameDescription.leftBottom.x, currentFrameDescription.leftBottom.y,
                        currentFrameDescription.leftBottom.x, currentFrameDescription.rightTop.y,
                        currentFrameDescription.rightTop.x,   currentFrameDescription.rightTop.y,
                        currentFrameDescription.rightTop.x,   currentFrameDescription.leftBottom.y,
                    };

                    textureCoordsBuffer.UpdateBuffer(textureCoords, 2 * 4 * sizeof(GLfloat)); //��������� ������ ������� ���������� �������
                }

                pShaderManager->UseShader(); //���������� ������

                /������ ��� ����������� ��������� � ������ � ����������� �� ���� ��������������� ��������
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

        Renderer::RenderGraphics(vertexArray, indexBuffer, *pShaderManager); //������������ ������
        * \endcode
        */
        void Render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer = 0, const size_t frameId = 0) const;

        /*!
        * ��������� ������ � ����� �� framesParams � ��������� ���� ������� �������
        * ����������:
        * \code
        *         framesParams = std::move(frameParams); 
        * \endcode
        *
        */
        void InsertFrames(std::vector<FrameParams> framesParams);
        /*!
        * �������� ������ � ����������� �������
        */
        double GetFrameDuration(const size_t frameId) const;
        /*!
        * �������� ������ � ���������� ������
        */
        size_t GetFramesCount() const;
        ~Sprite();

    protected:
        std::shared_ptr<TextureManager> pTexture; //����� ��������� �� ������ ��� ������ � ����������
        std::shared_ptr<ShaderManager> pShaderManager; //����� ��������� �� ������ ��� ������ � ���������

        VertexArray vertexArray; //������ ������
        VertexBuffer vertexCoordsBuffer; //������ ���������� ������� ��� ������
        VertexBuffer textureCoordsBuffer; //������ ���������� ������� ��� ��������
        IndexBuffer indexBuffer; //������ ���������� ������� 

        std::vector<FrameParams> framesParams; //������ ���������� ������
        mutable size_t lastFrameId; //���������� id �����
    };

}