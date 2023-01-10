#pragma once 
#include <glad/glad.h>
#include <vector>
namespace RenderEngine 
{
    /*!
    * \brief ��� ��������� ������ ��� ���������� �������� ������������ ���� �������, ������� ����� ������������ � glVertexAttribPointer - �������-������������� ��������� ������
    */
    struct VertexBufferLayoutElement {
        GLint count; ///<���������� ���������
        GLenum type; ///<�� ���
        GLboolean isDoNormalize; ///<��������, ������ ��� glVertexAttribPointer, �� �� ���. � ������ �� ������ false
        unsigned int size; ///<������ �������� � ������
    };
    /*!
    * \brief ������ ����� ��������� ����� ��������� ��������� � ������ ������ �� �������, ������� ����� ����������, ���� �������� ������ ���������� ������� �� ��������� ������� � ������� � �������.
    ����� ������� � ����� ������� �� ������� ����� ��������� ������ �������,����,�������,���� � �.�
    */
    class VertexBufferLayout {
    public:
        /*!
        * �����������, � ������� ����� ������������������ ��� ����� ����������, ������ ������� ���� �������� � ������.
        */
        VertexBufferLayout();

        /*!
        * �������, ������������ � ������� ��������� ������� ������ ���������� ����
        * \param count - ������ ���������� ����
        */
        void ReserveElements(const size_t count);

        /*!
        * ��������� ������� ���� float � layoutElments 
        * \param count - ��������, ����������� ��� ���������� ������� �������� � ������
        * \param isDoNormalize - ��������, ������ ��� glVertexAttribPointer, �� �� ���. � ������ �� ������ false
        * ����������:
        * \code
                unsigned int elememtSize = count * static_cast<unsigned int>(sizeof(GLfloat)); //��������� ������ ��������
                layoutElments.push_back({ static_cast<GLint>(count), GL_FLOAT, isDoNormalize, elememtSize}); //�������� ������� � ������
                elementStride += layoutElments.back().size; //������������ ��� �������� �� ���������� ������ � ��������, ����� ���������� ��.
        * \endcode
        */
        void AddElementLayoutFloat(const unsigned int count, const bool isDoNormalize);

        /*!
        * �������, ������������ ��� ����� ����������
        */
        unsigned int GetStride() const
        {
            return elementStride;
        }
        /*!
        * �������, ������������ ������ ��������� �������
        */
        const std::vector<VertexBufferLayoutElement>& GetLayoutElements() const 
        { 
            return layoutElments; 
        }

    private:
        std::vector<VertexBufferLayoutElement> layoutElments; ///<������ ��������� �������
        unsigned int elementStride;///<��� ����� ����������
    };

}