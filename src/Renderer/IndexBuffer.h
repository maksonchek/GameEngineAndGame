#pragma once

#include <glad/glad.h>

namespace RenderEngine {

    class IndexBuffer {
    public:
        IndexBuffer();
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

        void InitializeBuffer(const void* data, const unsigned int elementsCount);
        void BindBuffer() const;
        void UnBindBuffer() const;
        unsigned int GetElementsCount() const
        {
            return elementsCount;
        }

    private:
        GLuint id;
        unsigned int elementsCount;
    };

}