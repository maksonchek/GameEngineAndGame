#pragma once

#include <glad/glad.h>

namespace RenderEngine 
{
    /*!
    * \brief Данный класс нужен для работы с объектами вершинного буфера. которые могут хранить большое количество вершин в памяти GPU. 
    * Преимущество использования таких объектов буфера, что мы можем посылать в видеокарту большое количество наборов данных за один раз, без необходимости отправлять по одной вершине за раз.
    * Функционал данного класса полностью совпадает с функционалом IndexBuffer, только некоторые команды и параметры OpenGL отличаются. 
    */
    class VertexBuffer 
    {
    public:
        VertexBuffer();
        ~VertexBuffer();

        VertexBuffer(const VertexBuffer&) = delete;

        VertexBuffer& operator=(const VertexBuffer&) = delete;

        VertexBuffer& operator=(VertexBuffer&& vertexBuffer) noexcept;

        VertexBuffer(VertexBuffer&& vertexBuffer) noexcept;

        void InitializeBuffer(const void* data, const unsigned int size);

        void UpdateBuffer(const void* data, const unsigned int size) const;

        void BindBuffer() const;

        void UnBindBuffer() const;


    private:
        GLuint id; //id вертексного объекта
    };

}