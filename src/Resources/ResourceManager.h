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
    * �����, ����������� ��� �������� �� ���� ���������� �������
    * \param atlasName - ��� ������
    * \param texturePath - ������������ ������ �������
    * \param tilesNames - ����� �������
    * \param tileWidth - ������ �������
    * \param tileHeight - ������ �������
    * \return ��������� �� ��������
    * ����������:
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
    */
    static std::shared_ptr<RenderEngine::TextureManager> LoadTextureAtlas(const std::string atlasName,
                                                                         const std::string texturePath,
                                                                           const std::vector<std::string> tilesNames,
                                                                            const unsigned int tileWidth,
                                                                              const unsigned int tileHeight);
    

    static bool LoadResourcesFromJSON(const std::string& filePath);

    static const std::vector<std::vector<std::string>>& GetLevels() 
    { 
        return levels; 
    }

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

    static std::string path;

    static std::vector<std::vector<std::string>> levels;
};