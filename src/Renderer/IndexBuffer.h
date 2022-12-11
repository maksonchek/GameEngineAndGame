#pragma once

#include <glad/glad.h>

namespace Renderer {

    class IndexBuffer {
    public:
        IndexBuffer();
        ~IndexBuffer();

        IndexBuffer(const IndexBuffer&) = delete;
        IndexBuffer& operator=(const IndexBuffer&) = delete;
        IndexBuffer& operator=(IndexBuffer&& indexBuffer) noexcept;
        IndexBuffer(IndexBuffer&& indexBuffer) noexcept;

        void InitializeBuffer(const void* data, const unsigned int size);
        void BindBuffer() const;
        void UnBindBuffer() const;

    private:
        GLuint id;
    };

}