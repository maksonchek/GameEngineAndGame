#include "VertexBufferLayout.h"

namespace RenderEngine {
    VertexBufferLayout::VertexBufferLayout() : elementStride(0)
    {

    }

    void VertexBufferLayout::ReserveElements(const size_t count)
    {
        layoutElments.reserve(count);
    }

    void VertexBufferLayout::AddElementLayoutFloat(const unsigned int count, const bool isDoNormalize)
    {
        unsigned int elememtSize = count * static_cast<unsigned int>(sizeof(GLfloat));
        layoutElments.push_back({ static_cast<GLint>(count), GL_FLOAT, isDoNormalize, elememtSize});
        elementStride += layoutElments.back().size;
    }
}