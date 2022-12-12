#pragma once

#include <glad/glad.h>
#include <glm/vec2.hpp>
#include <string>
#include <map>

namespace RenderEngine {
    class TextureManager
    {
    public:

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

        void AddTile(std::string name, const glm::vec2& leftBottom, const glm::vec2& rightTop);
        const Tile& GetTile(const std::string& name) const;
        unsigned int GetWidth() const
        {
            return width;
        }
        unsigned int GetHeight() const
        {
            return height;
        }

        void Bind() const;

        TextureManager(const GLuint width, GLuint height,
                         const unsigned char* textFromFile,
                           const unsigned int channels = 4,
                             const GLenum filter = GL_LINEAR,
                               const GLenum wrapMode = GL_CLAMP_TO_EDGE);

        TextureManager() = delete;
        TextureManager(const TextureManager&) = delete;
        TextureManager& operator=(const TextureManager&) = delete;
        TextureManager& operator=(TextureManager&& texture);
        TextureManager(TextureManager&& texture);
        ~TextureManager();

    private:

        unsigned int width;
        unsigned int height;

        GLuint id;
        GLenum mode;

        std::map<std::string, Tile> tiles;
    };
}