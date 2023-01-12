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
		* \code
				shaderManager.UseShader();
				vertexArray.BindBuffer();
				indexBuffer.BindBuffer();

				glDrawElements(GL_TRIANGLES, indexBuffer.GetElementsCount(), GL_UNSIGNED_INT, nullptr);
		* \endcode
		*/
		static void RenderGraphics(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderManager& shaderManager);

		/*!
		* \code		
				glClearColor(red, green, blue, alpha);
		* \endcode
		*/
		static void ClearColor(float red, float green, float blue, float alpha);

		/*!
		* \code
				if (enabled)
				{
					glEnable(GL_DEPTH_TEST);
				}
				else
				{
					glDisable(GL_DEPTH_TEST);
				}
		* \endcode
		*/
		static void SetLayer(const bool enabled);

		/*!
		* \code
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		* \endcode
		*/
		static void Clear();

		/*!
		* \code
			glViewport(leftOffset, bottomOffset, width, height);
		* \endcode
		*/
		static void SetViewPort(unsigned int width, unsigned int height, unsigned int leftOffset = 0, unsigned int bottomOffset = 0);

		/*!
		* \code
			return (const char*)glGetString(GL_RENDERER);
		* \endcode
		*/
		static std::string GetRendererString();

		/*!
		* \code
			return (const char*)glGetString(GL_VERSION);
		* \endcode
		*/
		static std::string GetVersionString();
	};
}