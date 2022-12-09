#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class ShaderManager;
	class TextureManager;
<<<<<<< HEAD
	class Sprite;
=======
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18
}

class ResourceManager {
public:
	ResourceManager(const std::string& exePath);
	~ResourceManager() = default;

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&&) = delete;
	ResourceManager(const ResourceManager&&) = delete;

	std::shared_ptr<Renderer::ShaderManager> LoadShaderManager(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath);
	std::shared_ptr<Renderer::ShaderManager> GetShader(const std::string& shaderName);

	std::shared_ptr<Renderer::TextureManager> GetTexture(const std::string& textureName);

	std::shared_ptr<Renderer::TextureManager> LoadTexture(const std::string& textureName, const std::string& texturePath);

<<<<<<< HEAD
	std::shared_ptr<Renderer::Sprite> LoadSprite(const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const unsigned int spriteWidth, const int spriteHeight);

	std::shared_ptr<Renderer::Sprite> GetSprite(const std::string& spriteName);


	
=======
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18
private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderManager>> ShaderManagersMap_t;
	ShaderManagersMap_t mapShaderManagers;
	std::string GetTextFromFile(const std::string& relativeFilePath) const;
	std::string resPath;
	typedef std::map<const std::string, std::shared_ptr<Renderer::TextureManager>> TexturesManagersMap_t;
	TexturesManagersMap_t mapTexturesManager;
<<<<<<< HEAD

	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap_t;
	SpritesMap_t mapSprites;
=======
>>>>>>> 6b4f5a3531bde0d598e6d6c8ed7e6ec3735fbb18
};