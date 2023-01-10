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
* \brief Класс, отвечающий за загрузку ресурсов - считывание текстур с атласа текстур, разметки из json файла. Задействует все классы рендерера напрямую или косвенно. 
*/
class ResourceManager {
public:
    /*!
    * Этот класс нужен нам статическим, так он должен быть одним для всего движка.
    */
    ResourceManager() = delete;
    ~ResourceManager() = delete;

    /*!
    * Метод устанавливающий в менеджер ресурсов путь к папке со всеми ресурсами игры. Так как exe лужит в одной папке с папкой res, то передать в exetutablePath следует argv[0]
    * \param exetutablePath - путь к папке с res
    * Реализация: 
    * \code
          size_t found = executablePath.find_last_of("/\\"); 
          path = executablePath.substr(0, found);
    * \endcode
    */
    static void SetExecutablePath(const std::string& exetutablePath);

    /*!
    * Метод, освобождающий память от всех ресурсов игры после завершения игрового цикла
    * Реализация:
    * \code
         shaderManagers.clear();
         textures.clear();
         sprites.clear();
    * \endcode
    */
    static void DestructAllRes();
     
    /*!
    * Загружает шейдер с указанным именем и возвращает умный указатель на него
    * \param shaderName - имя шейдера 
    * \param vertexPath - путь к файлу с исходным кодом программы шейдера вершин, написанной на GLSL
    * \param fragmentPath - путь к файлу с исходным кодом программы шейдера фрагментов, написанной на GLSL
    * \return указатель на  загруженный шейдер
    * Реализация:
    * \code
            std::string vertexString = GetTextFromFile(vertexPath); // считываем текст вертексной программы
            if (vertexString.empty()) //Если что-то пошло не так, выводим ошибку
            {
                std::cerr << "Can't find vertex shader :-( " << std::endl;
                return nullptr;
            }
            //Аналогично поступаем с шейдерной программой
            std::string fragmentxString = GetTextFromFile(fragmentPath);
            if (fragmentxString.empty())
            {
                std::cerr << "Can't find fragment shader :-( " << std::endl;
                return nullptr;
            }
            
            std::shared_ptr<RenderEngine::ShaderManager>& newShader = shaderManagers.emplace(shaderName, std::make_shared<RenderEngine::ShaderManager>(vertexString, fragmentxString)).first->second; //Создаём новый шейдер из вертексной программы и фрагментной
            if (newShader->IsCompiled()) //Еслм шейдер собрался удачно, возвращаем его, иначе выводим ошибку и возвращаем nullptr
            {
                return newShader;
            }

            std::cerr << "Can't load shader program:" << std::endl << "Vertex program: " << vertexPath << std::endl  << "Fragment program: " << fragmentPath << std::endl;

            return nullptr;
    * \endcode
    */
    static std::shared_ptr<RenderEngine::ShaderManager> LoadShaders(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);

    /*!
    * Получаем шейдер с нужным именем
    * \param shaderName - имя шейдера, который нужно получить
    * \return указатель на шейдер
    * Реализация:
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
    * Метод, который загружает и возвращает текстурный атлас
    * \param textureName - имя текстурного атласа
    * \param texturePath - путь к текстурному атласу
    * \return указатель на текстурный атлас
    *  На наше счастье библиотека загрузки изображений stb_image.h, реализованная в один заголовочный файл, поддерживает загрузку RGBE файлов, возвращая массив чисел с плавающей точкой – то что надо для наших целей! Добавив библиотеку в свой проект загрузка данных изображений реализуется предельно просто:
    * Реализация:
    * \code
            int channels = 0; //количество цветовых каналов
            int width = 0; // ширина текстуры
            int height = 0; //высота текстуры
       
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
    * Метод, возвращающий нужную нам текстурный атлас, который уже был загружен
    * \param textureName - имя текстурного атласа
    * Реализация:
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
    * Загружает нужный спрайт и возвращает указатель на него
    * \param
    * \param textureName - имя атласа тексур, с которого будет получен спрайт
    * \param shaderName - имя шейдера, который соответствует данному спрайту
    * \param titleName - имя нужного нам спрайта (по умолчанию имя default), с которым объект изначально будет отрисовываться
    * \return - указатель на спрайт 
    * Реализация:
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
    * Метод, позволяющий получить спрайт с указанным именем
    * \param spriteName - имя спрайта
    * \return указатель на спрайт
    * Реализация:
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
    * Метод, считывающий все текстуры со всех текстурных атласов
    * \param atlasName - имя атласа
    * \param texturePath - расположение атласа текстур
    * \param tilesNames - имена текстур
    * \param tileWidth - ширина спрайта
    * \param tileHeight - высота спрайта
    * \return указатель на текстуру
    * Реализация:
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