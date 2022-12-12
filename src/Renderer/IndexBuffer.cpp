#include "IndexBuffer.h"

namespace RenderEngine {
    IndexBuffer::IndexBuffer() : id(0), elementsCount(0)
    {
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &id);
    }

    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& indexBuffer) noexcept
    {
        id = indexBuffer.id;
        indexBuffer.id = 0;
        elementsCount = indexBuffer.elementsCount;
        indexBuffer.elementsCount = 0;
        return *this;
    }

    IndexBuffer::IndexBuffer(IndexBuffer&& indexBuffer) noexcept
    {
        id = indexBuffer.id;
        indexBuffer.id = 0;
        elementsCount = indexBuffer.elementsCount;
        indexBuffer.elementsCount = 0;
    }

    void IndexBuffer::InitializeBuffer(const void* data, const unsigned int elementsCount)
    {
        this->elementsCount = elementsCount;
        glGenBuffers(1, &id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsCount * sizeof(GLuint), data, GL_STATIC_DRAW);
    }

    void IndexBuffer::BindBuffer() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void IndexBuffer::UnBindBuffer() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}