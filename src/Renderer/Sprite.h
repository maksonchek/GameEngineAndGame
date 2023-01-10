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
    * \brief Класс, отвечающий за наложение текстуры в нужном месте, нужного размера, в нужное время. По сути, это графическая компонента игрового объекта
    */
    class Sprite {
    public:
        /*!
        * Структура, хранящая в себе все данные, необходимые для смены текстуры на объекте, т.е анимации. Интерфейс самой анимации спрайта описан в классе SpriteAnimator
        */
        struct FrameParams {
            FrameParams(const glm::vec2 leftBottom, const glm::vec2 rightTop, const double duration) ///<Коструктор данной структуры
                : leftBottom(leftBottom)
                , rightTop(rightTop)
                , duration(duration)
            {}
            glm::vec2 leftBottom; ///<Координаты левого нижнего угла игрового объекта
            glm::vec2 rightTop; ///<Координаты верхнего крайнего угла игрового объекта
            double duration; ///<Длительность кадра
        };

        /*!
        * Конструктор спрайта 
        * \param pTexture - умный указатель на экземпляр класса менеджера текстур
        * \param initialTile - имя текстуры, с которой инициализируется игровой объект
        * \param pShaderManager - указатель на экземпляр класса менеджера шейдеров
        * Реализация:
        * \code
                const GLfloat vertexCoords[] = { //Здесь храним ккординаты вершин для вершинного шейдера. Это координаты отноительно объекта
                    0.f, 0.f,
                    0.f, 1.f,
                    1.f, 1.f,
                    1.f, 0.f
                };

                auto tile = this->pTexture->GetTile(std::move(initialTile)); // получаем

                const GLfloat textureCoords[] = {  //Здесь храним ккординаты вершин для текстуры
                    tile.leftBottom.x, tile.leftBottom.y,
                    tile.leftBottom.x, tile.rightTop.y,
                    tile.rightTop.x,   tile.rightTop.y,
                    tile.rightTop.x,   tile.leftBottom.y,
                };

                const GLuint indices[] = { //Здесь храним индексы для индексного буффера
                    0, 1, 2,
                    2, 3, 0
                };

                vertexCoordsBuffer.InitializeBuffer(vertexCoords, 2 * 4 * sizeof(GLfloat)); //Инициалиализируем объект вертексного буффера
                VertexBufferLayout vertexCoordsLayout; //Создаём экземпляр объекта VertexBufferLayout для более компактного хранения данных
                vertexCoordsLayout.AddElementLayoutFloat(2, false); //Добавляем в vertexCoordsLayout элементы вершин
                vertexArray.AddVertexBuffer(vertexCoordsBuffer, vertexCoordsLayout); //Добавляем в массив вершин объект вертексного буффера

                //то же самое делаем с координатами текстур
                textureCoordsBuffer.InitializeBuffer(textureCoords, 2 * 4 * sizeof(GLfloat));
                VertexBufferLayout textureCoordsLayout;
                textureCoordsLayout.AddElementLayoutFloat(2, false);
                vertexArray.AddVertexBuffer(textureCoordsBuffer, textureCoordsLayout);

                //Инициализируем индексный буффер для индексов
                indexBuffer.InitializeBuffer(indices, 6);

                //Отвязываем ставшие ненужными vertexArray и indexBuffer
                vertexArray.UnBindBuffer();
                indexBuffer.UnBindBuffer();
        * \endcode
        */
        Sprite(std::shared_ptr<TextureManager> pTexture, std::string initialTile, std::shared_ptr<ShaderManager> pShaderManager);

        Sprite(const Sprite&) = delete;
        Sprite& operator=(const Sprite&) = delete;

        /*!
        * Функция отрисовки объекта
        * \param position - позиция  объекта для отрисовки
        * \param size - размеры объекта
        * \param rotation - поворот объекта
        * \param layer - слой для отрисовки на экране (по умолчанию 0)
        * \param frameId - идентификатор начально кадра-текстуры (по умолчанию 0)
        * Реализация:
        * \code
                if (lastFrameId != frameId) //Если предыдущий кадр не равен текущему
                {
                    lastFrameId = frameId; //текущий кадр становится прошлым
                    const FrameParams& currentFrameDescription = framesParams[frameId]; //сохраняем параметры кадра

                    const GLfloat textureCoords[] = { //сохраняем координаты текущей текстуры
                        currentFrameDescription.leftBottom.x, currentFrameDescription.leftBottom.y,
                        currentFrameDescription.leftBottom.x, currentFrameDescription.rightTop.y,
                        currentFrameDescription.rightTop.x,   currentFrameDescription.rightTop.y,
                        currentFrameDescription.rightTop.x,   currentFrameDescription.leftBottom.y,
                    };

                    textureCoordsBuffer.UpdateBuffer(textureCoords, 2 * 4 * sizeof(GLfloat)); //Обновляем данные объекта вершинного буффера
                }

                pShaderManager->UseShader(); //Используем шейдер

                /Вносим все необходимые изменения в объект и накладываем на него соответствующую текстуру
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

        Renderer::RenderGraphics(vertexArray, indexBuffer, *pShaderManager); //Отрисовываем объект
        * \endcode
        */
        void Render(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer = 0, const size_t frameId = 0) const;

        /*!
        * Переносим данные о кадре из framesParams в параметры када данного объекта
        * Реализация:
        * \code
        *         framesParams = std::move(frameParams); 
        * \endcode
        *
        */
        void InsertFrames(std::vector<FrameParams> framesParams);
        /*!
        * Получаем данные о направлении объекта
        */
        double GetFrameDuration(const size_t frameId) const;
        /*!
        * Получаем данные о количестве кадров
        */
        size_t GetFramesCount() const;
        ~Sprite();

    protected:
        std::shared_ptr<TextureManager> pTexture; //Умный указатель на объект для работы с текстурами
        std::shared_ptr<ShaderManager> pShaderManager; //Умный указатель на объект для работы с шейдерами

        VertexArray vertexArray; //массив вершин
        VertexBuffer vertexCoordsBuffer; //объект вершинного буффера для вершин
        VertexBuffer textureCoordsBuffer; //объект вершинного буффера для текстуры
        IndexBuffer indexBuffer; //объект индексного буффера 

        std::vector<FrameParams> framesParams; //вектор параметров кадров
        mutable size_t lastFrameId; //предыдузий id кадра
    };

}