#include "ResourceManager.h"
#include "../Renderer/ShaderManager.h"
#include "../Renderer/TextureManager.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/SpriteAnimator.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"

 ResourceManager::mapShaderManager ResourceManager::shaderManagers;

 ResourceManager::mapTextureManager ResourceManager::textures;

 ResourceManager::mapSprite ResourceManager::sprites;

 ResourceManager::mapSpriteAnimators ResourceManager::animateSprites;

 std::string ResourceManager::path;

 std::vector<std::vector<std::string>> ResourceManager::levels;

void ResourceManager::SetExecutablePath(const std::string& executablePath)
{
    size_t found = executablePath.find_last_of("/\\");
     path = executablePath.substr(0, found);
}

void ResourceManager::DestructAllRes()
{
    shaderManagers.clear();
    textures.clear();
    sprites.clear();
    animateSprites.clear();
}

std::string ResourceManager::GetTextFromFile(const std::string& relativeFilePath) 
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

std::shared_ptr<RenderEngine::ShaderManager> ResourceManager::GetShaderManager(const std::string& shaderName)
{
    mapShaderManager::const_iterator it = shaderManagers.find(shaderName);
    if (it != shaderManagers.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the shader program :-( " << shaderName << std::endl;
    return nullptr;
}

std::shared_ptr<RenderEngine::ShaderManager> ResourceManager::LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
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

    std::shared_ptr<RenderEngine::ShaderManager>& newShader = shaderManagers.emplace(shaderName, std::make_shared<RenderEngine::ShaderManager>(vertexString, fragmentxString)).first->second;
    if (newShader->IsCompiled())
    {
        return newShader;
    }

    std::cerr << "Can't load shader program:\n"
        << "Vertex program: " << vertexPath << "\n"
        << "Fragment program: " << fragmentPath << std::endl;

    return nullptr;
}


std::shared_ptr<RenderEngine::Sprite> ResourceManager::LoadSprite(const std::string& spriteName,
                                                                    const std::string& textureName,
                                                                       const std::string& shaderName,
                                                                          const std::string& titleName) 
{
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

    std::shared_ptr<RenderEngine::Sprite> newSprite = sprites.emplace(spriteName, std::make_shared<RenderEngine::Sprite>(pTexture,
                                                                                                                           titleName,
                                                                                                                             pShader)).first->second;

    return newSprite;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::GetSprite(const std::string& spriteName)
{
    mapSprite::const_iterator iter = sprites.find(spriteName);
    if (iter != sprites.end())
    {
        return iter->second;
    }
    std::cerr << "Can't find the sprite: " << spriteName << std::endl;
    return nullptr;
}

std::shared_ptr<RenderEngine::SpriteAnimator> ResourceManager::LoadSpriteAnimator(const std::string& spriteName,
                                                                                    const std::string& textureName, const std::string& shaderName,  const std::string& titleName)
{
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

    std::shared_ptr<RenderEngine::SpriteAnimator> newSprite = animateSprites.emplace(spriteName, std::make_shared<RenderEngine::SpriteAnimator>(pTexture, titleName, pShader)).first->second;

    return newSprite;
}

std::shared_ptr<RenderEngine::SpriteAnimator> ResourceManager::GetSpriteAnimator(const std::string& spriteName)
{
    mapSpriteAnimators::const_iterator iter = animateSprites.find(spriteName);
    if (iter != animateSprites.end())
    {
        return iter->second;
    }
    std::cerr << "Can't find the sprite: " << spriteName << std::endl;
    return nullptr;
}

std::shared_ptr<RenderEngine::TextureManager> ResourceManager::GetTextureManager(const std::string& textureName)
{
    mapTextureManager::const_iterator it = textures.find(textureName);
    if (it != textures.end())
    {
        return it->second;
    }
    std::cerr << "Can't find the texture: " << textureName << std::endl;
    return nullptr;
}


std::shared_ptr<RenderEngine::TextureManager> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
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

    std::shared_ptr<RenderEngine::TextureManager> newTexture = textures.emplace(textureName, std::make_shared<RenderEngine::TextureManager>(width, height, pixels, channels, GL_NEAREST,  GL_CLAMP_TO_EDGE)).first->second;
    stbi_image_free(pixels);
    return newTexture;
}

std::shared_ptr<RenderEngine::TextureManager> ResourceManager::LoadTextureAtlas(std::string textureName,
                                                                              std::string texturePath,
                                                                                 std::vector<std::string> tilesNames,
                                                                                    const unsigned int tileWidth,
                                                                                       const unsigned int tileHeight) {
    auto pTexture = LoadTexture(std::move(textureName), std::move(texturePath));
    if (pTexture)
    {
        const unsigned int textureWidth = pTexture->GetWidth();
        const unsigned int textureHeight = pTexture->GetHeight();
        unsigned int currentTextureOffsetX = 0;
        unsigned int currentTextureOffsetY = textureHeight;
        for (auto& currentTileName : tilesNames)
        {
            glm::vec2 leftBottom(static_cast<float>(currentTextureOffsetX + 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - tileHeight + 0.01f) / textureHeight);
            glm::vec2 rightTop(static_cast<float>(currentTextureOffsetX + tileWidth - 0.01f) / textureWidth, static_cast<float>(currentTextureOffsetY - 0.01f) / textureHeight);

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

bool ResourceManager::LoadResourcesFromJSON(const std::string& filePath)
{
    const std::string JSONString = GetTextFromFile(filePath);
    if (JSONString.empty())
    {
        std::cerr << "File with JSON is empty :-(" << std::endl;
        return false;
    }

    rapidjson::Document doc;
    rapidjson::ParseResult parseResult = doc.Parse(JSONString.c_str());
    if (!parseResult)
    {
        std::cerr << "JSON parse error :-((((((((((((((( " << rapidjson::GetParseError_En(parseResult.Code()) << " In file " << filePath << std::endl;
        return false;
    }

   auto shadersIter =  doc.FindMember("shaders");

   if (shadersIter != doc.MemberEnd())
   {
       for (const auto &shader : shadersIter->value.GetArray())
       {
           const std::string name = shader["name"].GetString();
           const std::string vertexPath = shader["vertex_path"].GetString();
           const std::string fragmentPath = shader["fragment_path"].GetString();
           LoadShaders(name, vertexPath, fragmentPath);
       }
   }

   auto textureAtlasIter = doc.FindMember("TextureAtlases");

   if (textureAtlasIter != doc.MemberEnd())
   {
       for (const auto& atlas : textureAtlasIter->value.GetArray())
       {
           const std::string name = atlas["name"].GetString();
           const std::string atlasPath = atlas["filePath"].GetString();
           const unsigned int tileWidth = atlas["tileWidth"].GetUint();
           const unsigned int tileHeight = atlas["tileHeight"].GetUint();

           const auto tilesArray = atlas["tiles"].GetArray();
           std::vector<std::string> tiles;
           tiles.reserve(tilesArray.Size());
           for (const auto& tile : tilesArray)
           {
               tiles.emplace_back(tile.GetString());
           }
           LoadTextureAtlas(name, atlasPath, std::move(tiles), tileWidth, tileHeight);
       }
   }
   auto spritesIter = doc.FindMember("sprites");
   if (spritesIter != doc.MemberEnd())
   {
       for (const auto& currentSprite : spritesIter->value.GetArray())
       {
           const std::string name = currentSprite["name"].GetString();
           const std::string textureAtlas = currentSprite["textureAtlas"].GetString();
           const std::string shader = currentSprite["shader"].GetString();
           const std::string tile = currentSprite["tileName"].GetString();

           auto pSprite = LoadSprite(name, textureAtlas, shader, tile);
           if (!pSprite)
           {
               continue;
           }
       }
   }

   auto textureAnimIter = doc.FindMember("AnimateSprites");
   if (textureAnimIter != doc.MemberEnd())
   {
       for (const auto& anim : textureAnimIter->value.GetArray())
       {
           const std::string name = anim["name"].GetString();
           const std::string textureAtlas = anim["textureAtlas"].GetString();
           const std::string shader = anim["shader"].GetString();
           const std::string initialTile = anim["initialTile"].GetString();

           auto pAnimatedSprite = LoadSpriteAnimator(name, textureAtlas, shader, initialTile);
           if (!pAnimatedSprite)
           {
               continue;
           }

           const auto statesArray = anim["states"].GetArray();
           for (const auto& state : statesArray)
           {
               const std::string stateName = state["stateName"].GetString();
               std::vector<std::pair<std::string, uint64_t>> frames;
               const auto framesArray = state["frames"].GetArray();
               frames.reserve(framesArray.Size());
               for (const auto& frame : framesArray)
               {
                   const std::string tile = frame["tile"].GetString();
                   const uint64_t duration = frame["duration"].GetUint64();
                   frames.emplace_back(std::pair<std::string, uint64_t>(tile, duration));
               }
               pAnimatedSprite->InsertState(stateName, std::move(frames));
           }
       }
       float a = 30 % 1;
       auto levelsIt = doc.FindMember("levels");
       if (levelsIt != doc.MemberEnd())
       {
           for (const auto& currentLevel : levelsIt->value.GetArray())
           {
               const auto description = currentLevel["description"].GetArray();
               std::vector<std::string> levelRows;
               levelRows.reserve(description.Size());
               size_t maxLength = 0;
               for (const auto& currentRow : description)
               {
                   levelRows.emplace_back(currentRow.GetString());
                   if (maxLength < levelRows.back().length())
                   {
                       maxLength = levelRows.back().length();
                   }
               }

               for (auto& currentRow : levelRows)
               {
                   while (currentRow.length() < maxLength)
                   {
                       currentRow.append("D");
                   }
               }
               levels.emplace_back(std::move(levelRows));
               
           }
       }
   }
   return true;
}