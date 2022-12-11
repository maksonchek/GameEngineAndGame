#pragma once

#include <glad/glad.h>

namespace Renderer {

    class VertexBuffer {
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
        GLuint id;
    };

}