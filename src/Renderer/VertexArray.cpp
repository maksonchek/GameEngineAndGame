#include "VertexArray.h"
namespace RenderEngine {
    VertexArray::VertexArray()
    {
        glGenVertexArrays(1, &id);
    }

    VertexArray::~VertexArray()
    {
        glDeleteVertexArrays(1, &id);
    }

    VertexArray& VertexArray::operator=(VertexArray&& vertexArray) noexcept
    {
        id = vertexArray.id;
        vertexArray.id = 0;
        return *this;
    }

    VertexArray::VertexArray(VertexArray&& vertexArray) noexcept
    {
        id = vertexArray.id;
        vertexArray.id = 0;
    }

    void VertexArray::BindBuffer() const
    {
        glBindVertexArray(id);
    }

    void VertexArray::UnBindBuffer() const
    {
        glBindVertexArray(0);
    }

    void VertexArray::AddVertexBuffer(const VertexBuffer& vertexBuffer, const VertexBufferLayout& layout)
    {
        BindBuffer();
        vertexBuffer.BindBuffer();
        const auto& layoutElements = layout.GetLayoutElements();
        GLbyte* offset = nullptr;
        for (unsigned int i = 0; i < layoutElements.size(); ++i)
        {
            const auto& currentLayoutElement = layoutElements[i];
            GLuint currentAttribIndex = elementsCount + i;
            glEnableVertexAttribArray(currentAttribIndex);
            glVertexAttribPointer(currentAttribIndex, currentLayoutElement.count, currentLayoutElement.type, currentLayoutElement.isDoNormalize, layout.GetStride(), offset);
            offset += currentLayoutElement.size;
        }
        elementsCount += static_cast<unsigned int>(layoutElements.size());
    }
}