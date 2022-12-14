#include "TextureManager.h"

namespace RenderEngine {

    TextureManager::TextureManager(const GLuint width, GLuint height,
                                     const unsigned char* data,
                                        const unsigned int channels,
                                          const GLenum filter,
                                            const GLenum wrapMode) : width(width), height(height) {
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
        glTexImage2D(GL_TEXTURE_2D, 0, mode, width, height, 0, mode, GL_UNSIGNED_BYTE, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    TextureManager& TextureManager::operator=(TextureManager&& texture)
    {
        glDeleteTextures(1, &id);
        id = texture.id;
        texture.id = 0;
        mode = texture.mode;
        width = texture.width;
        height = texture.height;
        return *this;
    }

    TextureManager::TextureManager(TextureManager&& texture) 
    {
        id = texture.id;
        texture.id = 0;
        mode = texture.mode;
        width = texture.width;
        height = texture.height;
    }

    void TextureManager::Bind() const
    {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void TextureManager::AddTile(std::string name, const glm::vec2& leftBottom, const glm::vec2& rightTop)
    {
        tiles.emplace(std::move(name), Tile(leftBottom, rightTop));
    }

    const TextureManager::Tile& TextureManager::GetTile(const std::string& name) const
    {
        auto it = tiles.find(name);
        if (it != tiles.end())
        {
            return it->second;
        }
        const static Tile defaultSubTexture;
        return defaultSubTexture;
    }

    TextureManager::~TextureManager()
    {
        glDeleteTextures(1, &id);
    }
}