#pragma once 
#include <glad/glad.h>
#include <vector>
namespace RenderEngine 
{
    /*!
    * \brief эта структура хранит все неоходимые элементы создаваемого нами буффера, которые будут передаваться в glVertexAttribPointer - функцию-интерпритатор вершинных данных
    */
    struct VertexBufferLayoutElement {
        GLint count; ///<Количество элементов
        GLenum type; ///<Их тип
        GLboolean isDoNormalize; ///<параметр, нужный для glVertexAttribPointer, но не нам. В двмжве он всегда false
        unsigned int size; ///<Размер элемента в байтах
    };
    /*!
    * \brief Данный класс позволяет более компактно упаковать в памяти данные об объекте, который нужно нарисовать, путём создания одного буфферного объекта из веринного буффера и буффера с цветами.
    Таким образом в одном буффере по порядку будут размещены данные позиция,цвет,позиция,цвет и т.д
    */
    class VertexBufferLayout {
    public:
        /*!
        * Конструктор, в котором будет проинициализирован шаг между элементами, равный размеру типа элемента в байтах.
        */
        VertexBufferLayout();

        /*!
        * Функция, резевирующая в векторе элементов буффера нужное количество мест
        * \param count - нужное количество мест
        */
        void ReserveElements(const size_t count);

        /*!
        * Добавляет элемент типа float в layoutElments 
        * \param count - параметр, необходимый для вычисления размера элемента в байтах
        * \param isDoNormalize - параметр, нужный для glVertexAttribPointer, но не нам. В двмжве он всегда false
        * Реализация:
        * \code
                unsigned int elememtSize = count * static_cast<unsigned int>(sizeof(GLfloat)); //Вычисляем размер элемента
                layoutElments.push_back({ static_cast<GLint>(count), GL_FLOAT, isDoNormalize, elememtSize}); //Помущаем элемент в вектор
                elementStride += layoutElments.back().size; //Увеличиваемм шаг элемента на количество вершин в элементе, штобы обшагивать их.
        * \endcode
        */
        void AddElementLayoutFloat(const unsigned int count, const bool isDoNormalize);

        /*!
        * Функция, возвращающая шаг между элементами
        */
        unsigned int GetStride() const
        {
            return elementStride;
        }
        /*!
        * Функция, возвращающая вектор элементов буффера
        */
        const std::vector<VertexBufferLayoutElement>& GetLayoutElements() const 
        { 
            return layoutElments; 
        }

    private:
        std::vector<VertexBufferLayoutElement> layoutElments; ///<Вектор элементов буффера
        unsigned int elementStride;///<Шаг между элементами
    };

}