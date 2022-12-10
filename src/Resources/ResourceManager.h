#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace Renderer
{
    class ShaderManager;
    class TextureManager;
    class Sprite;
    class SpriteAnimator;
}


class ResourceManager {
public:
    ResourceManager(const std::string& executablePath);
    ~ResourceManager() = default;

    std::shared_ptr<Renderer::ShaderManager> LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

    std::shared_ptr<Renderer::ShaderManager> GetShaderManager(const std::string& shaderName);

    std::shared_ptr<Renderer::TextureManager> LoadTexture(const std::string& textureName, const std::string& texturePath);

    std::shared_ptr<Renderer::TextureManager> GetTextureManager(const std::string& textureName);

    std::shared_ptr<Renderer::Sprite> LoadSprite(const std::string &spriteName,
                                                   const std::string &textureName,
                                                     const std::string &shaderName,
                                                       const unsigned int spriteWidth,
                                                        const unsigned int spriteHeight,
                                                           const std::string &titleName = "default");

    std::shared_ptr<Renderer::Sprite> GetSprite(const std::string& spriteName);

    std::shared_ptr<Renderer::SpriteAnimator> LoadSpriteAnimator(const std::string &spriteName,
                                                   const std::string &textureName,
                                                     const std::string &shaderName,
                                                       const unsigned int spriteWidth,
                                                         const unsigned int spriteHeight,
                                                           const std::string &titleName = "default");

    std::shared_ptr<Renderer::SpriteAnimator> GetSpriteAnimator(const std::string& spriteName);


    std::shared_ptr<Renderer::TextureManager> LoatTextureAtlas(const std::string textureName,
                                                                 const std::string texturePath,
                                                                   const std::vector<std::string> tilesNames,
                                                                    const unsigned int tileWidth,
                                                                      const unsigned int tileHeight);
    


    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

private:
    std::string GetTextFromFile(const std::string& relativeFilePath) const;

    typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderManager>> mapShaderManager;
    mapShaderManager shaderManagers;

    typedef std::map<const std::string, std::shared_ptr<Renderer::TextureManager>> mapTextureManager;
    mapTextureManager textures;

    typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> mapSprite;
    mapSprite sprites;

    typedef std::map<const std::string, std::shared_ptr<Renderer::SpriteAnimator>> mapSpriteAnimators;
    mapSpriteAnimators animateSprites;

    std::string path;
};