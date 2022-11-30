#include "ResourceManager.h"
#include "../Renderer/ShaderManager.h"

#include <sstream>
#include <fstream>
#include <iostream>

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
		std::cerr << "������� ������ �����������!" << std::endl;
		return nullptr;
	}
	std::string fragmentText = GetTextFromFile(fragmentPath);
	if (fragmentPath.empty())
	{
		std::cerr << "������� ���������� �����������!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Renderer::ShaderManager>& newShader = mapShaderManagers.emplace(shaderName, std::make_shared<Renderer::ShaderManager>(vertexText, fragmentText)).first->second;
	if (newShader->IsCompiled())
	{
		return newShader;
	}
	else
	{
		std::cerr << "�� ���������� ��������� �������� ��������. ���-�� �� ��� � ����� �������: \n"
			<< "��������: " << vertexPath << "\n"
			<< "���������: " << fragmentPath << std::endl;
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
	std::cerr << "�� ������� ������" << shaderName << std::endl;
	return nullptr;
}

std::string ResourceManager::GetTextFromFile(const std::string& relativeFilePath) const
{
	std::ifstream f;
	f.open(resPath + "/" + relativeFilePath.c_str(), std::ios::in, std::ios::binary);
	if (!f.is_open())
	{
		std::cerr << "�� ������� ������� ����" << relativeFilePath << std::endl;
		return std::string{};
	}

	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}




