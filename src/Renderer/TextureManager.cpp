#include "TextureManager.h"

namespace Renderer {
    TextureManager::TextureManager(const GLuint width, const GLuint height, const unsigned char* textureBites,
        const unsigned int channels, const GLenum filter, const GLenum wrapMode) : width(width), height(height)
    {
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
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureBites);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    }

    TextureManager& TextureManager::operator = (TextureManager&& texture)
    {
        glDeleteTextures(1, &id);
        id = texture.id;
        texture.id = 0;
        mode = texture.mode;
        width = texture.width;
        width = texture.height;
        return *this;
    }

    TextureManager::TextureManager(TextureManager&& texture)
    {
        id = texture.id;
        texture.id = 0;
        mode = texture.mode;
        width = texture.width;
        width = texture.height;
    }

    TextureManager::~TextureManager()
    {
        glDeleteTextures(1, &id);
    }

    void TextureManager::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }
}
