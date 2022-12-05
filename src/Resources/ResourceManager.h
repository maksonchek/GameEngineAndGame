#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class ShaderManager;
	class TextureManager;
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

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderManager>> ShaderManagersMap_t;
	ShaderManagersMap_t mapShaderManagers;
	std::string GetTextFromFile(const std::string& relativeFilePath) const;
	std::string resPath;
	typedef std::map<const std::string, std::shared_ptr<Renderer::TextureManager>> TexturesManagersMap_t;
	TexturesManagersMap_t mapTexturesManager;
};