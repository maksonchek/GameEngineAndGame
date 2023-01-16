#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include<chrono>

#include "Resources/ResourceManager.h"
#include "Game/Game.h"
#include "Renderer/Renderer.h"
#include "PhysicsEngine/PhysicsEngine.h"


glm::ivec2 mainWindowSize(13*16, 14*16); ///<Стандартный азмер игрового окна
constexpr int scaling = 3;

std::unique_ptr<Game> game = std::make_unique<Game>(mainWindowSize); ///<Создание экземпляра класса игры

/*!
* Функция, отрисовывающая игру в нормальном для восприятия виде при изменении размеров игрового окна
*/
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    mainWindowSize.x = width;
    mainWindowSize.y = height;
    const float level_aspect_ratio = static_cast<float>(game->GetCurrentLevelWidth()) / game->GetCurrentLevelHeight();
    unsigned int viewPortWidth = mainWindowSize.x;
    unsigned int viewPortHeight = mainWindowSize.y;
    unsigned int viewPortLeftOffset = 0;
    unsigned int viewPortBottomOffset = 0;

    if (static_cast<float>(mainWindowSize.x) / mainWindowSize.y > level_aspect_ratio)
    {
        viewPortWidth = static_cast<unsigned int>(mainWindowSize.y * level_aspect_ratio);
        viewPortLeftOffset = (mainWindowSize.x - viewPortWidth) / 2;
    }
    else
    {
        viewPortHeight = static_cast<unsigned int>(mainWindowSize.x / level_aspect_ratio);
        viewPortBottomOffset = (mainWindowSize.y - viewPortHeight) / 2;
    }

    RenderEngine::Renderer::SetViewPort(viewPortWidth, viewPortHeight, viewPortLeftOffset, viewPortBottomOffset);
}

/*!
* Функция, принимающая нажатия кнопок и передающая их классу игры для дальнейшей обработки
*/
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
    /*!
    * Инициализация glfw 
    */
    if (!glfwInit())
    {
        std::cout << "glfw initialization failed! :-(" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /*!
    *Создаём окошко для вывода картинок 
    */
    GLFWwindow* pWindow = glfwCreateWindow(mainWindowSize.x, mainWindowSize.y, "Хе-хеы", nullptr, nullptr);
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
    RenderEngine::Renderer::SetLayer(true);

    {
        ResourceManager::SetExecutablePath(argv[0]); ///<Установка пути к папке с ресурсами игры
        game->InitGame(); ///<Инициализация игры
        glfwSetWindowSize(pWindow, static_cast<int>(scaling *game->GetCurrentLevelWidth()), static_cast<int>(scaling*game->GetCurrentLevelHeight())); ///<Установка размеров окна
        auto lastTime = std::chrono::high_resolution_clock::now(); ///<Переменная времени, необходимая для вычисления длительности кадра
        /* Игровой цикл */
        while (!glfwWindowShouldClose(pWindow))
        {
            auto currentTime = std::chrono::high_resolution_clock::now(); ///<<Переменная времени, необходимая для вычисления длительности кадра
            double timeDuration = std::chrono::duration<double, std::milli>(currentTime - lastTime).count(); ///<Длительность кадра
            lastTime = currentTime;
            game->Update(timeDuration); ///<Обновление игровых данных
            PhysicsEngineManager::PhysicsEngine::Update(timeDuration); ///<Обновление физических данных
            RenderEngine::Renderer::Clear(); ///<Очистка прошлого кадра

            game->Render(); ///<Отрисовка нового кадра
            glfwSwapBuffers(pWindow); 

            glfwPollEvents();
        }
        game = nullptr;
        ResourceManager::DestructAllRes();
    }
    ///< Очистка ресурсов
    PhysicsEngineManager::PhysicsEngine::DeleteAll();
    glfwTerminate();
    return 0;
}