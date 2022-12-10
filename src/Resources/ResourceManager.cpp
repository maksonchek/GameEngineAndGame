#include "ResourceManager.h"
#include "../Renderer/ShaderManager.h"
#include "../Renderer/TextureManager.h"
#include "../Renderer/Sprite.h"

#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

ResourceManager::ResourceManager(const std::string& executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
    path = executablePath.substr(0, found);
}

std::string ResourceManager::GetTextFromFile(const std::string& relativeFilePath) const
{
    std::ifstream f;
    f.open(path + "/" + relativeFilePath.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Failed to open file: " << relativeFilePath << std::endl;
        return std::string{};
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::shared_ptr<Renderer::ShaderManager> ResourceManager::GetShaderManager(const std::string& shaderName)
{
    mapShaderManager::const_iterator it = shaderManagers.find(shaderName);
    if (it != shaderManagers.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the shader program :-( " << shaderName << std::endl;
    return nullptr;
}

std::shared_ptr<Renderer::ShaderManager> ResourceManager::LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexString = GetTextFromFile(vertexPath);
    if (vertexString.empty())
    {
        std::cerr << "Can't find vertex shader :-( " << std::endl;
        return nullptr;
    }

    std::string fragmentxString = GetTextFromFile(fragmentPath);
    if (fragmentxString.empty())
    {
        std::cerr << "Can't find fragment shader :-( " << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::ShaderManager>& newShader = shaderManagers.emplace(shaderName, std::make_shared<Renderer::ShaderManager>(vertexString, fragmentxString)).first->second;
    if (newShader->IsCompiled())
    {
        return newShader;
    }

    std::cerr << "Can't load shader program:\n"
        << "Vertex program: " << vertexPath << "\n"
        << "Fragment program: " << fragmentPath << std::endl;

    return nullptr;
}


std::shared_ptr<Renderer::Sprite> ResourceManager::LoadSprite(const std::string& spriteName,
                                                                const std::string& textureName,
                                                                  const std::string& shaderName,
                                                                    const unsigned int spriteWidth,
                                                                      const unsigned int spriteHeight,
                                                                        const std::string& titleName) {
    auto pTexture = GetTextureManager(textureName);
    if (!pTexture)
    {
        std::cerr << "Can't find the texture: " << textureName << " for the sprite: " << spriteName << std::endl;
    }

    auto pShader = GetShaderManager(shaderName);
    if (!pShader)
    {
        std::cerr << "Can't find the shader: " << shaderName << " for the sprite: " << spriteName << std::endl;
    }

    std::shared_ptr<Renderer::Sprite> newSprite = sprites.emplace(textureName, std::make_shared<Renderer::Sprite>(pTexture,
                                                                                                                    titleName,
                                                                                                                      pShader,
                                                                                                                        glm::vec2(0.f, 0.f),
                                                                                                                          glm::vec2(spriteWidth, spriteHeight))).first->second;

    return newSprite;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::GetSprite(const std::string& spriteName)
{
    mapSprite::const_iterator it = sprites.find(spriteName);
    if (it != sprites.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the sprite: " << spriteName << std::endl;
    return nullptr;
}

std::shared_ptr<Renderer::TextureManager> ResourceManager::GetTextureManager(const std::string& textureName)
{
    mapTextureManager::const_iterator it = textures.find(textureName);
    if (it != textures.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the texture: " << textureName << std::endl;
    return nullptr;
}


std::shared_ptr<Renderer::TextureManager> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
    int channels = 0;
    int width = 0;
    int height = 0;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(std::string(path + "/" + texturePath).c_str(), &width, &height, &channels, 0);

    if (!pixels)
    {
        std::cerr << "Can't load image: " << texturePath << std::endl;
        return nullptr;
    }

    std::shared_ptr<Renderer::TextureManager> newTexture = textures.emplace(textureName, std::make_shared<Renderer::TextureManager>(width,
        height,
        pixels,
        channels,
        GL_NEAREST,
        GL_CLAMP_TO_EDGE)).first->second;
    stbi_image_free(pixels);
    return newTexture;
}

std::shared_ptr<Renderer::TextureManager> ResourceManager::LoatTextureAtlas(const std::string textureName,
                                                                              const std::string texturePath,
                                                                                 const std::vector<std::string> tilesNames,
                                                                                    const unsigned int tileWidth,
                                                                                       const unsigned int tileHeight) {
    auto pTexture = LoadTexture(std::move(textureName), std::move(texturePath));
    if (pTexture)
    {
        const unsigned int textureWidth = pTexture->GetWidth();
        const unsigned int textureHeight = pTexture->GetHeight();
        unsigned int currentTextureOffsetX = 0;
        unsigned int currentTextureOffsetY = textureHeight;
        for (const auto& currentTileName : tilesNames)
        {
            glm::vec2 leftBottom(static_cast<float>(currentTextureOffsetX) / textureWidth, static_cast<float>(currentTextureOffsetY - tileHeight) / textureHeight);
            glm::vec2 rightTop(static_cast<float>(currentTextureOffsetX + tileWidth) / textureWidth, static_cast<float>(currentTextureOffsetY) / textureHeight);

            pTexture->AddTile(std::move(currentTileName), leftBottom, rightTop);

            currentTextureOffsetX += tileWidth; 
            if (currentTextureOffsetX >= textureWidth)
            {
                currentTextureOffsetX = 0;
                currentTextureOffsetY -= tileHeight;
            }
        }
    }
    return pTexture;
}