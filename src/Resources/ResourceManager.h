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
    * Метод, считывающий все текстуры с текстурного атласа
    * \param atlasName - имя атласа
    * \param texturePath - расположение атласа текстур
    * \param tilesNames - имена текстур
    * \param tileWidth - ширина спрайта
    * \param tileHeight - высота спрайта
    * \return указатель на текстуру
    * Реализация:
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
    * Метод, сопоставляющий разметку ресурсов из файла json с ресурсами в файлах и загружающий все ресурсы
    * \param filePath - путь к json - файлу с разметкой
    * \return загрузились ли ресурсы с разметкой или нет
    * Реализация:
    * \code
            const std::string JSONString = GetTextFromFile(filePath);  //Считываем весь текст с json-файла
            if (JSONString.empty())
            {
                std::cerr << "File with JSON is empty :-(" << std::endl;
                return false;
            }

            rapidjson::Document doc; 
            rapidjson::ParseResult parseResult = doc.Parse(JSONString.c_str()); //парсим текст в премлемый формад для работы с json
            if (!parseResult)
            {
                std::cerr << "JSON parse error :-((((((((((((((( " << rapidjson::GetParseError_En(parseResult.Code()) << " In file " << filePath << std::endl;
                return false;
            }

           auto shadersIter =  doc.FindMember("shaders"); //находим заголовок шейдеров 

           if (shadersIter != doc.MemberEnd()) //если такой заголовок есть и под ним что-то написано, загружаем шейдеры
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

           if (textureAtlasIter != doc.MemberEnd()) //аналогично загружаем все данные со всех атласов текстур
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
           auto spritesIter = doc.FindMember("sprites"); //Среди текстур обозначаем спрайты, привязываем к ним шейдеры. Если у них есть анимация, загружаем время анимаций и распологаем их по порядку.
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
             
               auto levelsIt = doc.FindMember("levels"); //считываем разметку каждого уровня
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
    * Метод, возвращаюий количество уровней в игре
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
    * Метод, считывающий текст с файла
    * \param relativeFilePath - путь к файлу, с которого нужно считать данные
    * \return считанный с файла текст
    * Реализация:
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

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderManager>> mapShaderManager; ///<Создаем псевдоним для удобства использования контейнера с именем шейдера и его шейдерной программой
    static mapShaderManager shaderManagers; ///<Переменная созданного нами типа

    ///< Аналогично с текстурами и спрайтами
    typedef std::map<const std::string, std::shared_ptr<RenderEngine::TextureManager>> mapTextureManager;
    static mapTextureManager textures; 

    typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> mapSprite; 
    static mapSprite sprites; 

    static std::string path; ///<переменная, хранящая путь к папке с ресурсами

    static std::vector<std::vector<std::string>> levels; ///<Вектор векторов, хранящий разметку уровней
};