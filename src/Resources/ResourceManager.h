#pragma once

#include <string>
#include <memory>
#include <map>

namespace Renderer {
	class ShaderManager;
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

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderManager>> ShaderManagersMap_t;
	ShaderManagersMap_t mapShaderManagers;
	std::string GetTextFromFile(const std::string& relativeFilePath) const;
	std::string resPath;
};