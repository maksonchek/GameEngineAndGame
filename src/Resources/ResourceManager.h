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
}

/*!
* \brief �����, ���������� �� �������� �������� - ���������� ������� � ������ �������, �������� �� json �����. ����������� ��� ������ ��������� �������� ��� ��������. 
*/
class ResourceManager {
public:
    /*!
    * ���� ����� ����� ��� �����������, ��� �� ������ ���� ����� ��� ����� ������.
    */
    ResourceManager() = delete;
    ~ResourceManager() = delete;

    /*!
    * ����� ��������������� � �������� �������� ���� � ����� �� ����� ��������� ����. ��� ��� exe ����� � ����� ����� � ������ res, �� �������� � exetutablePath ������� argv[0]
    * \param exetutablePath - ���� � ����� � res
    * ����������: 
    * \code
          size_t found = executablePath.find_last_of("/\\"); 
          path = executablePath.substr(0, found);
    * \endcode
    */
    static void SetExecutablePath(const std::string& exetutablePath);

    /*!
    * �����, ������������� ������ �� ���� �������� ���� ����� ���������� �������� �����
    * ����������:
    * \code
         shaderManagers.clear();
         textures.clear();
         sprites.clear();
    * \endcode
    */
    static void DestructAllRes();
     
    /*!
    * ��������� ������ � ��������� ������ � ���������� ����� ��������� �� ����
    * \param shaderName - ��� ������� 
    * \param vertexPath - ���� � ����� � �������� ����� ��������� ������� ������, ���������� �� GLSL
    * \param fragmentPath - ���� � ����� � �������� ����� ��������� ������� ����������, ���������� �� GLSL
    * \return ��������� ��  ����������� ������
    * ����������:
    * \code
            std::string vertexString = GetTextFromFile(vertexPath); // ��������� ����� ���������� ���������
            if (vertexString.empty()) //���� ���-�� ����� �� ���, ������� ������
            {
                std::cerr << "Can't find vertex shader :-( " << std::endl;
                return nullptr;
            }
            //���������� ��������� � ��������� ����������
            std::string fragmentxString = GetTextFromFile(fragmentPath);
            if (fragmentxString.empty())
            {
                std::cerr << "Can't find fragment shader :-( " << std::endl;
                return nullptr;
            }
            
            std::shared_ptr<RenderEngine::ShaderManager>& newShader = shaderManagers.emplace(shaderName, std::make_shared<RenderEngine::ShaderManager>(vertexString, fragmentxString)).first->second; //������ ����� ������ �� ���������� ��������� � �����������
            if (newShader->IsCompiled()) //���� ������ �������� ������, ���������� ���, ����� ������� ������ � ���������� nullptr
            {
                return newShader;
            }

            std::cerr << "Can't load shader program:" << std::endl << "Vertex program: " << vertexPath << std::endl  << "Fragment program: " << fragmentPath << std::endl;

            return nullptr;
    * \endcode
    */
    static std::shared_ptr<RenderEngine::ShaderManager> LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

    /*!
    * �������� ������ � ������ ������
    * \param shaderName - ��� �������, ������� ����� ��������
    * \return ��������� �� ������
    * ����������:
    * \code
            mapShaderManager::const_iterator it = shaderManagers.find(shaderName);
            if (it != shaderManagers.end())
            {
                return it->second;
            }
            std::cerr << "Can't find the shader program :-( " << shaderName << std::endl;
            return nullptr;
    * \endcode 
    */
    static std::shared_ptr<RenderEngine::ShaderManager> GetShaderManager(const std::string& shaderName);

    /*!
    * �����, ������� ��������� � ���������� ���������� �����
    * \param textureName - ��� ����������� ������
    * \param texturePath - ���� � ����������� ������
    * \return ��������� �� ���������� �����
    *  �� ���� ������� ���������� �������� ����������� stb_image.h, ������������� � ���� ������������ ����, ������������ �������� RGBE ������, ��������� ������ ����� � ��������� ������ � �� ��� ���� ��� ����� �����! ������� ���������� � ���� ������ �������� ������ ����������� ����������� ��������� ������:
    * ����������:
    * \code
            int channels = 0; //���������� �������� �������
            int width = 0; // ������ ��������
            int height = 0; //������ ��������
       
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
    * \endcode
    */
    static std::shared_ptr<RenderEngine::TextureManager> LoadTexture(const std::string& textureName, const std::string& texturePath);

    /*!
    * �����, ������������ ������ ��� ���������� �����, ������� ��� ��� ��������
    * \param textureName - ��� ����������� ������
    * ����������:
    * \code
            mapTextureManager::const_iterator it = textures.find(textureName);
            if (it != textures.end())
            {
                return it->second;
            }
            std::cerr << "Can't find the texture: " << textureName << std::endl;
            return nullptr;
    * \endcode
    */
    static std::shared_ptr<RenderEngine::TextureManager> GetTextureManager(const std::string& textureName);

    /*!
    * ��������� ������ ������ � ���������� ��������� �� ����
    * \param
    * \param textureName - ��� ������ ������, � �������� ����� ������� ������
    * \param shaderName - ��� �������, ������� ������������� ������� �������
    * \param titleName - ��� ������� ��� ������� (�� ��������� ��� default), � ������� ������ ���������� ����� ��������������
    * \return - ��������� �� ������ 
    * ����������:
    * \code
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
    * \endcode
    */
    static std::shared_ptr<RenderEngine::Sprite> LoadSprite(const std::string &spriteName,
                                                          const std::string &textureName,
                                                             const std::string &shaderName,
                                                                   const std::string &titleName = "default");

    /*!
    * �����, ����������� �������� ������ � ��������� ������
    * \param spriteName - ��� �������
    * \return ��������� �� ������
    * ����������:
    * \code
            mapSprite::const_iterator iter = sprites.find(spriteName);
            if (iter != sprites.end())
            {
                return iter->second;
            }
            std::cerr << "Can't find the sprite: " << spriteName << std::endl;
            return nullptr;
    * \endcode
    */
    static std::shared_ptr<RenderEngine::Sprite> GetSprite(const std::string& spriteName);

    /*!
    * �����, ����������� ��� �������� � ����������� ������
    * \param atlasName - ��� ������
    * \param texturePath - ������������ ������ �������
    * \param tilesNames - ����� �������
    * \param tileWidth - ������ �������
    * \param tileHeight - ������ �������
    * \return ��������� �� ��������
    * ����������:
    * \code
            const unsigned int tileHeight) {
            auto pTexture = LoadTexture(std::move(atlasName), std::move(texturePath));
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
    *\endcode
    */
    static std::shared_ptr<RenderEngine::TextureManager> LoadTextureAtlas(const std::string atlasName,
                                                                         const std::string texturePath,
                                                                           const std::vector<std::string> tilesNames,
                                                                            const unsigned int tileWidth,
                                                                              const unsigned int tileHeight);
    
    /*!
    * �����, �������������� �������� �������� �� ����� json � ��������� � ������ � ����������� ��� �������
    * \param filePath - ���� � json - ����� � ���������
    * \return ����������� �� ������� � ��������� ��� ���
    * ����������:
    * \code
            const std::string JSONString = GetTextFromFile(filePath);  //��������� ���� ����� � json-�����
            if (JSONString.empty())
            {
                std::cerr << "File with JSON is empty :-(" << std::endl;
                return false;
            }

            rapidjson::Document doc; 
            rapidjson::ParseResult parseResult = doc.Parse(JSONString.c_str()); //������ ����� � ��������� ������ ��� ������ � json
            if (!parseResult)
            {
                std::cerr << "JSON parse error :-((((((((((((((( " << rapidjson::GetParseError_En(parseResult.Code()) << " In file " << filePath << std::endl;
                return false;
            }

           auto shadersIter =  doc.FindMember("shaders"); //������� ��������� �������� 

           if (shadersIter != doc.MemberEnd()) //���� ����� ��������� ���� � ��� ��� ���-�� ��������, ��������� �������
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

           if (textureAtlasIter != doc.MemberEnd()) //���������� ��������� ��� ������ �� ���� ������� �������
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
           auto spritesIter = doc.FindMember("sprites"); //����� ������� ���������� �������, ����������� � ��� �������. ���� � ��� ���� ��������, ��������� ����� �������� � ����������� �� �� �������.
           if (spritesIter != doc.MemberEnd()) 
           {
               for (const auto& currentSprite : spritesIter->value.GetArray())
               {
                   const std::string name = currentSprite["name"].GetString();
                   const std::string textureAtlas = currentSprite["textureAtlas"].GetString();
                   const std::string shader = currentSprite["shader"].GetString();
                   const std::string tile = currentSprite["initialTile"].GetString();

                   auto pSprite = LoadSprite(name, textureAtlas, shader, tile);
                   if (!pSprite)
                   {
                       continue;
                   }
                   auto framesIter = currentSprite.FindMember("frames");
                   if (framesIter != currentSprite.MemberEnd())
                   {
                       const auto framesArray = framesIter->value.GetArray();
                       std::vector<RenderEngine::Sprite::FrameParams> framesParams;
                       framesParams.reserve(framesArray.Size());
                       for (const auto& frame : framesArray)
                       {
                           const std::string tile = frame["tile"].GetString();
                           const double duration = frame["duration"].GetDouble();
                           const auto pTextureAtlas = GetTextureManager(textureAtlas);
                           const auto pTile = pTextureAtlas->GetTile(tile);
                           framesParams.emplace_back(pTile.leftBottom, pTile.rightTop, duration);
                       }
                       pSprite->InsertFrames(std::move(framesParams));
                   }
               }
             
               auto levelsIt = doc.FindMember("levels"); //��������� �������� ������� ������
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
                       levels.emplace_back(std::move(levelRows));             
                   }
               }
           }
           return true;
    *\endcode
    */
    static bool LoadResourcesFromJSON(const std::string& filePath);

    /*!
    * �����, ����������� ���������� ������� � ����
    */
    static const std::vector<std::vector<std::string>>& GetLevels() 
    { 
        return levels; 
    }

    ResourceManager(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(ResourceManager&&) = delete;
    ResourceManager(ResourceManager&&) = delete;

private:
    /*!
    * �����, ����������� ����� � �����
    * \param relativeFilePath - ���� � �����, � �������� ����� ������� ������
    * \return ��������� � ����� �����
    * ����������:
    * \code
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
    * \endcode
    */
    static std::string GetTextFromFile(const std::string& relativeFilePath); 

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderManager>> mapShaderManager; ///<������� ��������� ��� �������� ������������� ���������� � ������ ������� � ��� ��������� ����������
    static mapShaderManager shaderManagers; ///<���������� ���������� ���� ����

    ///< ���������� � ���������� � ���������
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::TextureManager>> mapTextureManager;
    static mapTextureManager textures; 

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> mapSprite; 
    static mapSprite sprites; 

    static std::string path; ///<����������, �������� ���� � ����� � ���������

    static std::vector<std::vector<std::string>> levels; ///<������ ��������, �������� �������� �������
};