#pragma once 
#include <glad/glad.h>
#include <vector>
namespace Renderer 
{
    struct VertexBufferLayoutElement {
        GLint count;
        GLenum type;
        GLboolean isDoNormalize;
        unsigned int size;
    };

    class VertexBufferLayout {
    public:

        VertexBufferLayout();

        void ReserveElements(const size_t count);


        void AddElementLayoutFloat(const unsigned int count, const bool isDoNormalize);

        unsigned int GetStride() const
        {
            return elementStride;
        }
        const std::vector<VertexBufferLayoutElement>& GetLayoutElements() const 
        { 
            return layoutElments; 
        }

    private:
        std::vector<VertexBufferLayoutElement> layoutElments;
        unsigned int elementStride;
    };

}