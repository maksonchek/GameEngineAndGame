#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include<chrono>

#include "Renderer/ShaderManager.h"
#include "Resources/ResourceManager.h"
#include "Renderer/TextureManager.h"
#include "Renderer/Sprite.h"
#include "Renderer/SpriteAnimator.h"

GLfloat point[] = {
     0.0f,  50.f, 0.0f,
     50.f, -50.f, 0.0f,
    -50.f, -50.f, 0.0f
};

GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};

GLfloat texCoord[] = {
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f
};

glm::ivec2 g_windowSize(640, 480);

void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height)
{
    g_windowSize.x = width;
    g_windowSize.y = height;
    glViewport(0, 0, width, height);
}

void glfwKeyCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
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

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

    glClearColor(1, 1, 0, 1);

    {
        ResourceManager resourceManager(argv[0]);
        auto pDefaultShaderProgram = resourceManager.LoadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram)
        {
            std::cerr << "Can't load shaders: " << "DefaultShader" << std::endl;
            return -1;
        }

        auto pSpriteShaderProgram = resourceManager.LoadShaders("SpriteShader", "res/shaders/vertexSprite.txt", "res/shaders/fragmentSprite.txt");
        if (!pSpriteShaderProgram)
        {
            std::cerr << "Can't create shader program: " << "SpriteShader" << std::endl;
            return -1;
        }

        auto tex = resourceManager.LoadTexture("DefaultTexture", "res/textures/assets.png");

        std::vector<std::string> tilesNames = 
        { 
            "block",
            "topBlock",
            "bottomBlock",
            "leftBlock",
            "rightBlock",
            "topLeftBlock",
            "topRightBlock",
            "bottomLeftBlock",

            "bottomRightBlock",
            "beton",
            "topBeton",
            "bottomBeton",
            "leftBeton",
            "rightBeton",
            "topLeftBeton",
            "topRightBeton",

            "bottomLeftBeton",
            "bottomRightBeton",
            "water1",
            "water2",
            "water3",
            "trees",
            "ice",
            "wall",

            "eagle",
            "deadEagle",
            "nothing",
            "respawn1",
            "respawn2",
            "respawn3",
            "respawn4"
        };
        auto pTextureAtlas = resourceManager.LoatTextureAtlas("DefaultTextureAtlas", "res/textures/assets.png", std::move(tilesNames), 16, 16);

        auto pSprite = resourceManager.LoadSprite("NewSprite", "DefaultTextureAtlas", "SpriteShader", 50, 50, "bottomRightBlock");
        pSprite->SetPosition(glm::vec2(0, 0));

        auto pSpriteAnimator = resourceManager.LoadSpriteAnimator("NewSpriteAnimator", "DefaultTextureAtlas", "SpriteShader", 50, 50, "bottomRightBlock");
        pSpriteAnimator->SetPosition(glm::vec2(300, 300));
        std::vector<std::pair<std::string, uint64_t>> spriteState;
        spriteState.emplace_back(std::make_pair<std::string, uint64_t>("water1", 1000000000));
        spriteState.emplace_back(std::make_pair<std::string, uint64_t>("water2", 1000000000));
        spriteState.emplace_back(std::make_pair<std::string, uint64_t>("water3", 1000000000));

        pSpriteAnimator->InsertState("spriteState", std::move(spriteState));
        pSpriteAnimator->SetState("spriteState");

        GLuint pointsVBO = 0;
        glGenBuffers(1, &pointsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colorsVBO = 0;
        glGenBuffers(1, &colorsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint texCoordsVBO = 0;
        glGenBuffers(1, &texCoordsVBO);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord), texCoord, GL_STATIC_DRAW);

        GLuint VAO = 0;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, pointsVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, texCoordsVBO);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

        pDefaultShaderProgram->UseShader();
        pDefaultShaderProgram->SetInt("textures", 0);

        glm::mat4 modelMatrix_1 = glm::mat4(1.f);
        modelMatrix_1 = glm::translate(modelMatrix_1, glm::vec3(100.f, 50.f, 0.f));

        glm::mat4 modelMatrix_2 = glm::mat4(1.f);
        modelMatrix_2 = glm::translate(modelMatrix_2, glm::vec3(590.f, 50.f, 0.f));

        glm::mat4 projectionMatrix = glm::ortho(0.f, static_cast<float>(g_windowSize.x), 0.f, static_cast<float>(g_windowSize.y), -100.f, 100.f);

        pDefaultShaderProgram->SetMatrix4x4("projectionMat", projectionMatrix);

        pSpriteShaderProgram->UseShader();
        pSpriteShaderProgram->SetInt("textures", 0);
        pSpriteShaderProgram->SetMatrix4x4("projectionMat", projectionMatrix);

        auto lastTime = std::chrono::high_resolution_clock::now();
        //int i = 0;
        /* Игровой цикл */
        while (!glfwWindowShouldClose(pWindow))
        {
            auto currentTime = std::chrono::high_resolution_clock::now();
            uint64_t timeDuration = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - lastTime).count();
            lastTime = currentTime;
            pSpriteAnimator->UpdateFrame(timeDuration);

            /* Покадровая отрисовка */
            glClear(GL_COLOR_BUFFER_BIT);

            pDefaultShaderProgram->UseShader();
            glBindVertexArray(VAO);
            tex->Bind();

            pDefaultShaderProgram->SetMatrix4x4("modelMat", modelMatrix_1);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            pDefaultShaderProgram->SetMatrix4x4("modelMat", modelMatrix_2);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            //i++;
            //pSprite->SetPosition(glm::vec2(i/1000, i/1000));
            pSprite->Render();
            pSpriteAnimator->Render();
            glfwSwapBuffers(pWindow);

            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}