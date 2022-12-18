#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include<chrono>

#include "Resources/ResourceManager.h"
#include "Game/Game.h"
#include "Renderer/Renderer.h"

glm::ivec2 g_windowSize(13*16, 14*16);

std::unique_ptr<Game> game = std::make_unique<Game>(g_windowSize);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;
    RenderEngine::Renderer::SetViewPort(width, height);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
    game->SetClick(key, action);
}

int main(int argc, char** argv)
{
    /* Инициализация glfw */
    if (!glfwInit())
    {
        std::cout << "glfw initialization failed! :-(" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Создаём окошко для вывода картинок */
    GLFWwindow* pWindow = glfwCreateWindow(g_windowSize.x, g_windowSize.y, "Хе-хеы", nullptr, nullptr);
    if (!pWindow)
    {
        std::cout << "glfw didn't create window! :-(" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);

    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD :-(" << std::endl;
    }

    std::cout << "Renderer: " << RenderEngine::Renderer::GetRendererString() << std::endl;
    std::cout << "OpenGL version: " << RenderEngine::Renderer::GetVersionString() << std::endl;

    RenderEngine::Renderer::ClearColor(0, 0, 0, 1);

    {
        ResourceManager::SetExecutablePath(argv[0]);
        game->InitGame();

        auto lastTime = std::chrono::high_resolution_clock::now();
        //int i = 0;
        /* Игровой цикл */
        while (!glfwWindowShouldClose(pWindow))
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            game->Update(timeDuration);

            /* Покадровая отрисовка */
            RenderEngine::Renderer::Clear();

            game->Render();
            glfwSwapBuffers(pWindow);

            glfwPollEvents();
        }
        game = nullptr;
        ResourceManager::DestructAllRes();
    }

    glfwTerminate();
    return 0;
}