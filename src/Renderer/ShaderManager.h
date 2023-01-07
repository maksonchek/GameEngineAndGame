#pragma once

#include <glad/glad.h>
#include <string>
#include <glm/mat4x4.hpp>

namespace RenderEngine {
    /*!
     \brief �����, �������������� �������� ��������, �� ������������ � �����������. ������ � ������������ ��� ����������� ���������� ������ "RenderEngine".
        glad ������������ �������� ���������� ����� �����, ������� �������� "���������" ��� OpenGl. mat4x4 ��������� �������� � ������������������ ��������� ��� ������������ ������������ ��������
    */
    class ShaderManager {
    public:
        /*!
        *  ����������� ������. ������ ��������� � ����������� ������� � ��������� �� � ���� ��������� ���������, ������� ��� �������������. ����� ���� ������� �������� ������ ��������� � ����������� �������.
        * \param vertexShader, fragmentShader - ������ ��  ������ ������, ���������� ���������� ��������, ���������� �� GLSL 
        * ���������� ������:
        * \code
                GLuint vertexShaderId;  // ������ id ���������� ������� ���� ���, ��������� glsl - ���������� �����, �������� �� C
                if (!CreateShader(vertexShader, GL_VERTEX_SHADER, vertexShaderId))  // ���� ����� �������� ���������� ������� ����� ������, �.� ������ ����, �������� ������������, ��� ��� ��������� ������ �� ��������. ��� �������, ����� ������ ����� ���������� ��-�� �� ������� � ��������� ���������
                {
                    std::cerr << "VERTEX SHADER compile-time error" << std::endl;
                    return;
                }

                GLuint fragmentShaderId; // ����������, ��� � � ��������� �������� ����������� �� �� �������� �������� �������������� ��� ������������ �������
                if (!CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderId)) // ����������, ��� � � ��������� �������� ����������� �� �� �������� �������� ���������� ��������  ������������ �������
                {
                    std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
                    glDeleteShader(vertexShaderId);
                    return;
                }

                id = glCreateProgram(); // ������� ��������� ��������� � �������� � �������������. ���� �� �������, �� �� ���������� � ����������� ������� � �����-�� ��������� ���������, ����� �������� ����� https://habr.com/ru/post/311808/ ��� � ��� �� ��������� ������ ����� � ��� ��� ��� �������, � ��� ������ �������� ����� ������.
                glAttachShader(id, vertexShaderId); // ������������ ���������� ������ � ��������� ��������� � ��������������� id
                glAttachShader(id, fragmentShaderId); // ������������ ����������� ������ � ��������� ��������� � ��������������� id
                glLinkProgram(id); ///< ������� (�� ������� ���������) �� ��� �������. ��, �����, �� �������, �� ���������, �� ��� ����. 

                GLint success; // �� �������� ���� ���������, �� �� ��������� ���������, ���� � �������. ������ ����������, �� ������� �� ����� �����, ��������� �� �� ��� ���� ��� ���
                glGetProgramiv(id, GL_LINK_STATUS, &success); // �����, ������������ �� ��������� ��������� � ��������������� id, ��������� �������� � ��� ��������� ���������� "�����" 
                if (!success) // ���� ����� ������� �� �� ����� �������, �������� ��������� � ������� ��������
                {
                    GLchar infoLog[1024];
                    glGetShaderInfoLog(id, 1024, nullptr, infoLog);
                    std::cerr << "Link error: " << infoLog << std::endl;
                }
                else // ���� �� �� ��, �� ������ isCompiled � false �� true, ������ � ��������� ������� ��� ��� �� ��� �����������. �� ��� ����� �� �����. ��� �����. ������, ����� ������������������� ����� �� ��������.
                {
                    isCompiled = true; // ��, � ����, ��� ������ ���������������� ������������, ��� ����� ���� �� �� ����. ���� �� �� �������, ���� � ����������. � ������ �������, �� �����, ��� ��� ����� ������, ��� ���� ������ ������� �����. 
                }

                glDeleteShader(vertexShaderId);  // ������, ���� ��������� ������� ��� ��������� ���� ������ - ������������ � ��������� ����������, ����� �������� �� ���� ��� ���� ������. ��, �� �������, �� ������ �� ���������� � ������ �������� ������. ������� ���.
                glDeleteShader(fragmentShaderId); // ������������ ������� ��� ���� ��������. �������. ..... ���, �� ������ ��� ������ ��������� ��������� ��������� ���������. 
        * \endcode
        */

        ShaderManager(const std::string& vertexShader, const std::string& fragmentShader);

        /*!
        * ���������� ������ - ������� ��������� ���������
        */
        ~ShaderManager();

        /*!
        * ���������� ��������� ��������� ��� ���������� ��������� ��������
        */
        void UseShader() const;

        /*!
        * ������������ ��� ������ � ���������� ��� ��� ����, ����� ���������� ������� ����������� ����� � uniform sampler (���������� ������ � �����). ������������ �� ����� glUniform1i �� ����� �������, ��� uniform sampler ����������� � ���������� ���������� ������.
        * \param name - ������ �� ��� ��������� ���������
        * \param value - ����� ����������� �����
        */
        void SetInt(const std::string& name, const GLint value);
        
        /*!
        * ������������ ��� ������ � ���������� ��� ��� ����, ����� ���������� ������� ����������� ����� � uniform sampler (���������� ������ � �����). ������������ �� ����� glUniform1f �� ����� �������, ��� uniform sampler ����������� � ���������� ���������� ������.
        * \param name - ������ �� ��� ��������� ���������
        * \param value - ����� ����������� �����
        */
        void SetFloat(const std::string& name, const GLfloat value);

        /*!
        * ����� �������� ����������������� ������� � ������. ����� ��� ����, ����� ������ ��������
        * \param name - ��� �������
        * \param matrix - ����������������� �������
        */
        void SetMatrix4x4(const std::string& name, const glm::mat4& matrix);

        /*!
         * ����� ��� �������� ���������� ������ � ���������
         * \return isCompiled - ��������� ���� ������
        */
        bool IsCompiled() const 
        { 
            return isCompiled; 
        }

        /*!
        * ��������� ����������� ��� ����������, ��� ��� ��� �� ����� ������.
        */
        ShaderManager() = delete;
        /*!
        * ��������� ����������� ��������� ������� � ������ ��������, ��� ��� � ��� ��������� ��� ������� � ����� � ��� �� id � ����� ��������� ����� ���������, ������ ����� �����������.
        */
        ShaderManager(const ShaderManager&) = delete;
        /*!
        * ��������� ������������ ��������� ������� � ������ ��������, ��� ��� � ��� ��������� ��� ������� � ����� � ��� �� id � ����� ��������� ����� ���������, ��������� ����� �����������.
        */
        ShaderManager& operator=(const ShaderManager&) = delete;
        /*!
        * ����������� ������ ���������� ��������� ������� �������, ������� ����� ��������, �����, ��� ��� �� ��������� ������� � id, �� ����� ����������.
        * \param shaderManager - ������, ������������ �� move ������
        * \code
            glDeleteProgram(id); //������� ������� ��������� ���������
            id = shaderManager.id; //������ ����� id ��������� ���������, ������ � �������������� ��������� ��������
            isCompiled = shaderManager.isCompiled; //������� �������� isCompiled �������� ����������� ��������� ��������

            shaderManager.id = 0; //��������� ������������� ������ ��������
            shaderManager.isCompiled = false;
            return *this; //���������� �������������� ������
        *\endcode
        */
        ShaderManager& operator=(ShaderManager&& shaderManager) noexcept;
        /*!
        * ����������� ����������� �������, ������� ����� �������� ���� ��������, ��� ��� ������� � id ������� �� ���������
        * \param shaderManager - ������, ������������ �� move ������
        * \code
            id = shaderManager.id; //������ ����� id ��������� ���������, ������ � ����������� ��������� ��������
            isCompiled = shaderManager.isCompiled; //������� �������� isCompiled �������� ����������� ��������� ��������

            shaderManager.id = 0; /��������� ���������� ������ ��������
            shaderManager.isCompiled = false;
        * \endcode
        */
        ShaderManager(ShaderManager&& shaderManager) noexcept;

    private:
        
        /*!
        * �����, ��������� ������, ������������� �������� ��� ������� � ������� ������� � ������������� ���. � ������ ������� ������ � ������� ������. 
        * \param source - ��� �������
        * \param shaderType - ��� �������
        * \param shaderId - ������������� �������
        * \return ���������� true, ���� ����� ���������� �������, false, ���� ���-�� ����� �� ���.
        * ���������� ������: 
        * \code
            shaderId = glCreateShader(shaderType); //������ ������ (���������� ��� �����������) � �������� ��� �������������
            const char* code = source.c_str(); //����������� � ������� ��� ������� �� GLSL, ��������� � �����
            glShaderSource(shaderId, 1, &code, nullptr); //����������� �������� ��� ������� � ������� �������...
            glCompileShader(shaderId); //...� ����������� ���

            GLint success; 
            glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success); //���������, �� �� ������ �������
            if (!success)
            {
                GLchar infoLog[1024];
                glGetShaderInfoLog(shaderId, 1024, nullptr, infoLog);
                std::cerr << "ERROR::SHADER: Compile-time error:\n" << infoLog << std::endl;
                return false; //���� ���, ���������� ����
            }
            return true; //���� �� ���������, ���������� ���
            \endcode
        */
        bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderId);

        bool isCompiled = false; ///< ���� ������, ������������ ��� ��������, ������ �� ������ ��� ���
        GLuint id = 0; ///< ������������� �������
    };
}
