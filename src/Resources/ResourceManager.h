#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace RenderEngine
{
    class ShaderManager;
    class TextureManager;
    class Sprite;
    class SpriteAnimator;
}


class ResourceManager {
public:
    ResourceManager() = delete;
    ~ResourceManager() = delete;

    static void SetExecutablePath(const std::string& exetutablePath);

    static void DestructAllRes();
     
    static std::shared_ptr<RenderEngine::ShaderManager> LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

    static std::shared_ptr<RenderEngine::ShaderManager> GetShaderManager(const std::string& shaderName);

    static std::shared_ptr<RenderEngine::TextureManager> LoadTexture(const std::string& textureName, const std::string& texturePath);

    static std::shared_ptr<RenderEngine::TextureManager> GetTextureManager(const std::string& textureName);

    static std::shared_ptr<RenderEngine::Sprite> LoadSprite(const std::string &spriteName,
                                                          const std::string &textureName,
                                                             const std::string &shaderName,
                                                                const unsigned int spriteWidth,
                                                                  const unsigned int spriteHeight,
                                                                     const std::string &titleName = "default");

    static std::shared_ptr<RenderEngine::Sprite> GetSprite(const std::string& spriteName);

    static std::shared_ptr<RenderEngine::SpriteAnimator> LoadSpriteAnimator(const std::string &spriteName,
                                                                           const std::string &textureName,
                                                                             const std::string &shaderName,
                                                                               const unsigned int spriteWidth,
                                                                                 const unsigned int spriteHeight,
                                                                                   const std::string &titleName = "default");

    static std::shared_ptr<RenderEngine::SpriteAnimator> GetSpriteAnimator(const std::string& spriteName);


    static std::shared_ptr<RenderEngine::TextureManager> LoatTextureAtlas(const std::string textureName,
                                                                         const std::string texturePath,
                                                                           const std::vector<std::string> tilesNames,
                                                                            const unsigned int tileWidth,
                                                                              const unsigned int tileHeight);
    

    static bool LoadResourcesFromJSON(const std::string& filePath);

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

private:
    static std::string GetTextFromFile(const std::string& relativeFilePath);

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderManager>> mapShaderManager;
    static mapShaderManager shaderManagers;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::TextureManager>> mapTextureManager;
    static mapTextureManager textures;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> mapSprite;
    static mapSprite sprites;

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::SpriteAnimator>> mapSpriteAnimators;
    static mapSpriteAnimators animateSprites;

    static std::string path;
};