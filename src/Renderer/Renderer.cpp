#include "Renderer.h"

namespace RenderEngine
{

	void Renderer::RenderGraphics(const VertexArray& vertexArray, const IndexBuffer& indexBuffer, const ShaderManager& shaderManager)
	{
		shaderManager.UseShader();
		vertexArray.BindBuffer();
		indexBuffer.BindBuffer();

		glDrawElements(GL_TRIANGLES, indexBuffer.GetElementsCount(), GL_UNSIGNED_INT, nullptr);
	}
	void Renderer::ClearColor(float red, float green, float blue, float alpha)
	{
		glClearColor(red, green, blue, alpha);
	}
	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::SetViewPort(unsigned int width, unsigned int height, unsigned int leftOffset, unsigned int bottomOffset)
	{
		glViewport(leftOffset, bottomOffset, width, height);
	}
	std::string Renderer::GetRendererString()
	{
		return (const char*)glGetString(GL_RENDERER);
	}
	std::string Renderer::GetVersionString()
	{
		return (const char*)glGetString(GL_VERSION);
	}

}