#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

namespace RenderEngine {
    /*!
    * \brief ����� ��� ������ � ����������
    * 
    */
    class TextureManager
    {
    public:
        /*!
        * \brief ���������, �������� ���������� ��������� (������� ������ �����, ������ ����� �����)
        */
        struct Tile
        {
            glm::vec2 leftBottom;
            glm::vec2 rightTop;

            Tile(const glm::vec2& leftBottom, const glm::vec2& rightTop)
                : leftBottom(leftBottom)
                , rightTop(rightTop)
            {}

            Tile()
                : leftBottom(0.f)
                , rightTop(1.f)
            {}
        };

        /*!
        * ��������� �������� � ���������� ������������ � ������ 
        * \param name - ��� ��������
        * \param leftBottom, rightTop - ���������� �������� ����� ��������
        * ����������:
        * \code
        *         tiles.emplace(std::move(name), Tile(leftBottom, rightTop));
        * \endcode
        */
        void AddTile(std::string name, const glm::vec2& leftBottom, const glm::vec2& rightTop);

        /*!
        * �������� ������ �������� � ���������� ������. ���� ����� ���, ���������� ��������� �������� � �������� �����������
        * \param name - ��� ��������
        * ����������:
        * \code
                auto it = tiles.find(name);
                if (it != tiles.end())
                {
                    return it->second;
                }
                const static Tile defaultTile;
                return defaultTile;
        * \endcode
        */
        const Tile& GetTile(const std::string& name) const;

        unsigned int GetWidth() const
        {
            return width;
        }
        unsigned int GetHeight() const
        {
            return height;
        }

        /*!
        * ����� ����������� �������� � ������� id � ��������� ����������� �����
        */
        void Bind() const;
        
        /*!
        * ����������� ������, ������������, ����������� � ������������� ��������
        * \param width, height - ������ � ������ ��������
        * \param textFromFile - ������ � ��������, ��������� �� �����
        * \param channels - �������� ������
        * \param filter - ������ ���������
        * \param wrapMode - ����� ������
        * ����������:
        * \code
                switch (channels)
                {
                case 4:
                    mode = GL_RGBA;
                    break;
                case 3:
                    mode = GL_RGB;
                    break;
                default:
                    mode = GL_RGBA;
                    break;
                }

                glGenTextures(1, &id);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, id);
                glTexImage2D(GL_TEXTURE_2D, 0, mode, this->width, this->height, 0, mode, GL_UNSIGNED_BYTE, data);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
                glGenerateMipmap(GL_TEXTURE_2D);

                glBindTexture(GL_TEXTURE_2D, 0);
        * \endcode
        */
        TextureManager(const GLuint width, GLuint height,
                         const unsigned char* textFromFile,
                           const unsigned int channels = 4,
                             const GLenum filter = GL_LINEAR,
                               const GLenum wrapMode = GL_CLAMP_TO_EDGE);

        TextureManager() = delete;
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;

        /*!
        * ��������������� move-��������� ������������
        * ����������:
                glDeleteTextures(1, &id);
                id = texture.id;
                texture.id = 0;
                mode = texture.mode;
                width = texture.width;
                height = texture.height;
                return *this;
        */
        TextureManager& operator=(TextureManager&& texture);
        
        /*!
        * ����������� move-�����������
        * ����������:
                id = texture.id;
                texture.id = 0;
                mode = texture.mode;
                width = texture.width;
                height = texture.height;
        */
        TextureManager(TextureManager&& texture);
        ~TextureManager();

    private:

        unsigned int width; //������ ��������
        unsigned int height; // ������ ��������

        GLuint id; //������������� ��������
        GLenum mode; //����� ��������� ��������. ������ �� ������������ � ����

        std::map<std::string, Tile> tiles; //������ ��� �������� � � ������ � �����������
    };
}