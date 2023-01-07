#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace RenderEngine {
    /*!
     \brief Класс, обеспечивающий создание шейдеров, их использоваие и уничтожение. Входит в пространство имён графической компоненты движка "RenderEngine".
        glad обеспечивает создание переменных таких типов, которые являются "понятными" для OpenGl. mat4x4 позволяет работать с трансформационными матрицами для передвижения отрисованных обЪектов
    */
    class ShaderManager {
    public:
        /*!
        *  Конструктор класса. Создаёт вершинные и фрагментные шейдеры и связывает их в одну шейдерную программу, готовую для использования. Псоле чего удаляет ненужные больше вершинные и фрагментные шейдеры.
        * \param vertexShader, fragmentShader - ссылки на  адреса файлов, содержащих интерфейсы шейдеров, написанные на GLSL 
        * Реализация метода:
        * \code
                GLuint vertexShaderId;  // Создаём id вершинного шейдера типа инт, понятного glsl - шейдерному языку, похожему на C
                if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId))  // Если метод создания вершинного шейдера выдал ошибку, т.е вернул фолс, сообщаем пользователю, что его вершинный шейдер не создался. Как правило, такая ошибка может возникнуть из-за не поладок в шейдерной программе
                {
                    std::cerr << "VERTEX SHADER compile-time error" << std::endl;
                    return;
                }

                GLuint fragmentShaderId; // Аналогично, как и с вершинным шейдером проделываем ту же операцию создания идентификатора для фрагментного шейдера
                if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId)) // Аналогично, как и с вершинным шейдером проделываем ту же операцию проверки успешности создания  фрагментного шейдера
                {
                    std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
                    glDeleteShader(vertexShaderId);
                    return;
                }

                id = glCreateProgram(); // Создаем шейдерную программу и получаем её идентификатор. Если не понятно, шо за вертексные и фрагментные шейдеры и какие-то шейдерные программы, лучше почитать здесь https://habr.com/ru/post/311808/ ибо я тут не собираюсь писать войну и мир про мир графики, я тут движок реализую между прочим.
                glAttachShader(id, vertexShaderId); // Присоединяем вертексный шейдер к шейдерной программе с идентификатором id
                glAttachShader(id, fragmentShaderId); // Присоединяем фрагментный шейдер к шейдерной программе с идентификатором id
                glLinkProgram(id); ///< Линкуем (на русском связываем) всё это воедино. Да, долго, да муторно, да непонятно, но так надо. 

                GLint success; // По хорошему надо проверить, всё ли нормально сработало, этим и займёмся. Создаём переменную, по которой мы потом поймём, сработало ои всё как надо или нет
                glGetProgramiv(id, GL_LINK_STATUS, &success); // Узнаём, слинковалась ли шейдерная программа с идентификатором id, результат передаем в уже созданную переменную "успех" 
                if (!success) // Если удача сегодня не на нашей стороне, получаем сообщение с ошибкой линковки
                {
                    GLchar infoLog[1024];
                    glGetShaderInfoLog(id, 1024, nullptr, infoLog);
                    std::cerr << "Link error: " << infoLog << std::endl;
                }
                else // Если же всё ок, то меняем isCompiled с false на true, знание о созданном шейдере нам ещё ой как понядобится. Но это будет не скоро. Или скоро. Смотря, какой задокументированный класс ты откроешь.
                {
                    isCompiled = true; // Да, я знаю, мой способ документирования неправильный, тут много слов не по делу. Зато он не скучный, хоть и непонятный. С другой стороны, не думаю, что это будут читать, ибо есть движки получше этого. 
                }

                glDeleteShader(vertexShaderId);  // Кстати, наши вершинные шейдеры уже выполнили свою миссию - слинковались с шейдерной программой, чтобы породить на свет ещё один шейдер. Да, он молодец, но теперь он бесполезен и только занимает память. Удаляем его.
                glDeleteShader(fragmentShaderId); // Фрагментного шейдера это тоже касается. Удаляем. ..... Эхх, мы только что лишили маленькую шейдерную программу родителей. 
        * \endcode
        */

        ShaderManager(const std::string& vertexShader, const std::string& fragmentShader);

        /*!
        * Деструктор класса - удаляет шейдерную программу
        */
        ~ShaderManager();

        /*!
        * Используем шейдерную программу для дальнейшей отрисовки объектов
        */
        void UseShader() const;

        /*!
        * Используется при работе с текстурами для для того, чтобы установить позицию текстурного блока в uniform sampler (текстурный объект в файле). Устанавливая их через glUniform1i мы будем уверены, что uniform sampler соотносится с правильным текстурным блоком.
        * \param name - ссылка на имя шейдерной программы
        * \param value - номер текстурного блока
        */
        void SetInt(const std::string& name, const GLint value);
        
        /*!
        * Используется при работе с текстурами для для того, чтобы установить позицию текстурного блока в uniform sampler (текстурный объект в файле). Устанавливая их через glUniform1f мы будем уверены, что uniform sampler соотносится с правильным текстурным блоком.
        * \param name - ссылка на имя шейдерной программы
        * \param value - номер текстурного блока
        */
        void SetFloat(const std::string& name, const GLfloat value);

        /*!
        * Метод передачи трансформационной матрицы в шейдер. Нужен для того, чтобы объект двигался
        * \param name - имя матрица
        * \param matrix - трансформационная матрица
        */
        void SetMatrix4x4(const std::string& name, const glm::mat4& matrix);

        /*!
         * Метод для проверки успешности работы с шейдерами
         * \return isCompiled - приватное поле класса
        */
        bool IsCompiled() const 
        { 
            return isCompiled; 
        }

        /*!
        * Запрещаем конструктор без параметров, так как это не имеет смысла.
        */
        ShaderManager() = delete;
        /*!
        * Запрещаем копирование менеджера шейдера в другой менеджер, так как у нас получатся два объекта с одним и тем же id и когда программа будет удаляться, выйдет казус неимоверный.
        */
        ShaderManager(const ShaderManager&) = delete;
        /*!
        * Запрещаем присваивание менеджера шейдера в другой менеджер, так как у нас получатся два объекта с одним и тем же id и когда программа будет удаляться, возникнет казус неимоверный.
        */
        ShaderManager& operator=(const ShaderManager&) = delete;
        /*!
        * Присваивать одному экземпляру менеджера шейдера другого, который скоро удалится, можно, так как не возникнет проблем с id, он будет уникальным.
        * \param shaderManager - объект, передающийся по move ссылке
        * \code
            glDeleteProgram(id); //Удаляем прошлую шейдерную программу
            id = shaderManager.id; //Делаем новый id шейдерной программы, взятый у присваиваемого менеджера шейдеров
            isCompiled = shaderManager.isCompiled; //Передаём текушему isCompiled значение присваемого менеджера шейдеров

            shaderManager.id = 0; //Отключаем присваиваемый шейдер менеджер
            shaderManager.isCompiled = false;
            return *this; //Возвращаем новоиспеченный объект
        *\endcode
        */
        ShaderManager& operator=(ShaderManager&& shaderManager) noexcept;
        /*!
        * Конструктор копирования объекта, который скоро удалится тоже разрешён, так как казусов с id шейдера не возникнет
        * \param shaderManager - объект, передающийся по move ссылке
        * \code
            id = shaderManager.id; //Делаем новый id шейдерной программы, взятый у копируемого менеджера шейдеров
            isCompiled = shaderManager.isCompiled; //Передаём текушему isCompiled значение копируемого менеджера шейдеров

            shaderManager.id = 0; /Отключаем копируемый шейдер менеджер
            shaderManager.isCompiled = false;
        * \endcode
        */
        ShaderManager(ShaderManager&& shaderManager) noexcept;

    private:
        
        /*!
        * Метод, создающий шейдер, привязывающий исходный код шейдера к объекту шейдера и компилирующий его. В случае неудачи выдвет в консоль ошибку. 
        * \param source - имя шейдера
        * \param shaderType - тип шейдера
        * \param shaderId - идентификатор шейдера
        * \return возвращает true, если метод выполнился успешно, false, если что-то пошло не так.
        * Реализация метода: 
        * \code
            shaderId = glCreateShader(shaderType); //Создаём шейдер (вертексный или фрагментный) и получаем его идентификатор
            const char* code = source.c_str(); //преобразуем в символы код шейдера на GLSL, считанный с файла
            glShaderSource(shaderId, 1, &code, nullptr); //привязываем исходный код шейдера к объекту шейдера...
            glCompileShader(shaderId); //...и компилируем его

            GLint success; 
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success); //Проверяем, всё ли прошло успешно
            if (!success)
            {
                GLchar infoLog[1024];
                glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
                std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
                return false; //Если нет, возвращаем фолс
            }
            return true; //Если всё нормально, возвращаем тру
            \endcode
        */
        bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderId);

        bool isCompiled = false; ///< поле класса, используемое для проверки, создан ли шейдер или нет
        GLuint id = 0; ///< идентификатор шейдера
    };
}
