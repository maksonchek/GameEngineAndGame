#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderManager.h"

#include <string>

namespace RenderEngine
{
	class Renderer
	{
	public:
		static void RenderGraphics(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderManager& shaderManager);

		static void ClearColor(float red, float green, float blue, float alpha);

		static void Clear();

		static void SetViewPort(unsigned int width, unsigned int height, unsigned int leftOffset = 0, unsigned int bottomOffset = 0);

		static std::string GetRendererString();

		static std::string GetVersionString();
	};
}