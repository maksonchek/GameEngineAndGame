#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "ShaderManager.h"

#include <string>

namespace RenderEngine
{
	/*!
	* \brief Класс, отвещающий за отрисовку графики и управление этой отрисовкой. Также помогает создавать окно, через которое будет всё рисоваться. 
		Принадлежит пространству имён RenderEngine. Вообще, всё что в этом движке отвечает за грфику принадлежит пространству имен RenderEngine.
	*/
	class Renderer
	{
	public:
		/*!
		* 
		*/
		static void RenderGraphics(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderManager& shaderManager);

		static void ClearColor(float red, float green, float blue, float alpha);

		static void SetLayer(const bool enabled);

		static void Clear();

		static void SetViewPort(unsigned int width, unsigned int height, unsigned int leftOffset = 0, unsigned int bottomOffset = 0);

		static std::string GetRendererString();

		static std::string GetVersionString();
	};
}