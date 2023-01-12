#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace RenderEngine {

    /*!
    * \brief Класс, описываюий массив врешин. Похож на VertexBuffer и IndexBuffer. Вообще VAO, т.е VertexArray, нужен для того, чтобы настроить атрибуты лишь единожды и передать их в VAO. 
    */
    class VertexArray {
    public:
        VertexArray();
        ~VertexArray();

        VertexArray(const VertexArray&) = delete;

        VertexArray& operator=(const VertexArray&) = delete;

        VertexArray& operator=(VertexArray&& vertexArray) noexcept;

        VertexArray(VertexArray&& vertexArray) noexcept;

        void BindBuffer() const;

        void UnBindBuffer() const;  

        void AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout);

    private:
        unsigned int elementsCount = 0; //количество элементов в вертексном массиве
        GLuint id; //id вертексного массива
    };

}