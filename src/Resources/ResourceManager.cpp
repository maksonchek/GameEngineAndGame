#include "ResourceManager.h"
#include "../Renderer/ShaderManager.h"
#include "../Renderer/TextureManager.h"
#include <sstream>
#include <fstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h";

ResourceManager::ResourceManager(const std::string& exePath)
{
	size_t foundedPath = exePath.find_last_of("/\\");
	resPath = exePath.substr(0, foundedPath);
}

std::shared_ptr<Renderer::ShaderManager> ResourceManager::LoadShaderManager(const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::string vertexText = GetTextFromFile(vertexPath);
	if (vertexText.empty())
	{
		std::cerr << "Шейдеры вершин отсутствуют!" << std::endl;
		return nullptr;
	}
	std::string fragmentText = GetTextFromFile(fragmentPath);
	if (fragmentPath.empty())
	{
		std::cerr << "Шейдеры фрагментов отсутствуют!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderManager>& newShader = mapShaderManagers.emplace(shaderName, std::make_shared<Renderer::ShaderManager>(vertexText, fragmentText)).first->second;
	if (newShader->IsCompiled())
	{
		return newShader;
	}
	else
	{
		std::cerr << "Не получилось загрузить мэнэджер шейдеров. что-то не так с этими файлами: \n"
			<< "Вертексы: " << vertexPath << "\n"
			<< "Фрагменты: " << fragmentPath << std::endl;
	}
	return nullptr;
}

std::shared_ptr<Renderer::ShaderManager> ResourceManager::GetShader(const std::string& shaderName)
{
	ShaderManagersMap_t::const_iterator iter = mapShaderManagers.find(shaderName);
	if (iter != mapShaderManagers.end())
	{
		return iter->second;
	}
	std::cerr << "Не нашелся шейдер" << shaderName << std::endl;
	return nullptr;
}



std::shared_ptr<Renderer::TextureManager> ResourceManager::GetTexture(const std::string& textureName)
{
	TexturesManagersMap_t::const_iterator iter = mapTexturesManager.find(textureName);
	if (iter != mapTexturesManager.end())
	{
		return iter->second;
	}
	std::cerr << "Не нашлась текстура" << textureName << std::endl;
	return nullptr;
}

std::shared_ptr<Renderer::TextureManager> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
	int colorChannels = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(resPath + "/" + texturePath).c_str(), &width, &height, &colorChannels, 0);
	if (!pixels)
	{
		std::cerr << "Произошла ошибка при загрузке текстур" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::TextureManager> newTexture = mapTexturesManager.emplace(textureName, std::make_shared<Renderer::TextureManager>(width, height, pixels, colorChannels, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;

	stbi_image_free(pixels);

	return newTexture;
}

std::string ResourceManager::GetTextFromFile(const std::string& relativeFilePath) const
{
	std::ifstream f;
	f.open(resPath + "/" + relativeFilePath.c_str(), std::ios::in, std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "Не удалось открыть файл" << relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}




