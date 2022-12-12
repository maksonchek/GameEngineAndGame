#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace RenderEngine {

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
        unsigned int elementsCount = 0;
        GLuint id;
    };

}