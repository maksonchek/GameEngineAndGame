#include "VertexBuffer.h"

namespace Renderer {
    VertexBuffer::VertexBuffer()
        : id(0)
    {
    }

    VertexBuffer::~VertexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertexBuffer) noexcept
    {
        id = vertexBuffer.id;
        vertexBuffer.id = 0;
        return *this;
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& vertexBuffer) noexcept
    {
        id = vertexBuffer.id;
        vertexBuffer.id = 0;
    }

    void VertexBuffer::InitializeBuffer(const void* data, const unsigned int size)
    {
        glGenBuffers(1, &id);
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

    void VertexBuffer::UpdateBuffer(const void* data, const unsigned int size) const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
    }

    void VertexBuffer::BindBuffer() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void VertexBuffer::UnBindBuffer() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}