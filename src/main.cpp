#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Renderer/ShaderManager.h"
#include "Renderer/TextureManager.h"
#include "Resources/ResourceManager.h"

GLfloat points[] =
{
   0.0f, 50.f, 0.0f,
   50.f, -50.f, 0.0f,
   -50.f, -50.f, 0.0f,
};

GLfloat colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};

GLfloat texturePoints[] =
{
    0.5f, 1.0f,
    1.0f, 0.0f,
    0.0f, 0.0f 
};

glm::ivec2 windowSize(640, 480);

void glfwWindowSizeCallback(GLFWwindow* pWindow,  int width, int height)
{
    windowSize.x = width;
    windowSize.y = height;
    glViewport(0, 0, windowSize.x, windowSize.y);
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
    ResourceManager resourceManager(argv[0]);
    GLFWwindow* pWindow;

    if (!glfwInit())
    {
        std::cout << "glwnInit failed" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    pWindow = glfwCreateWindow(windowSize.x, windowSize.y, "Welcome to the club, body!", NULL, NULL);
    if (!pWindow)
    {
        std::cout << "glfwCreateWindow failed" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwKeyCallback);
    glfwMakeContextCurrent(pWindow);

    if (!gladLoadGL())
    {
        std::cout << "Can't load GLAD";
        return -1;
    }
    std::cout << "Renderer:" << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version OpenGL:" << glGetString(GL_VERSION) << std::endl;
    {
    glClearColor(1, 1, 0, 1);

    ResourceManager resourceManager(argv[0]);
    auto pDefaultShaderProgram = resourceManager.LoadShaderManager("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
    
    auto texture = resourceManager.LoadTexture("DefaultTexture", "res/textures/assets.png");
    //std::string vertexShader(vertex_shader);
    //std::string fragmentShader(fragment_shader);

    //Renderer::ShaderManager shaderManager (vertexShader, fragmentShader);    

    GLuint points_vbo = 0;
    glGenBuffers(1, &points_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint colors_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint textures_vbo = 0;
    glGenBuffers(1, &colors_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, textures_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texturePoints), texturePoints, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    
    //Текстуры
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, textures_vbo);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    pDefaultShaderProgram->UseShader();
    pDefaultShaderProgram->SetInt("textures", 0);

    glm::mat4 modelMatrix1 = glm::mat4(1.f);
    modelMatrix1 = glm::translate(modelMatrix1, glm::vec3(1.f, 2.f, 0.f));

    glm::mat4 modelMatrix2 = glm::mat4(1.f);
    modelMatrix2 = glm::translate(modelMatrix2, glm::vec3(5.f, 2.f, 0.f));
     
    glm::mat4 projectionMatrix = glm::ortho(0.f, (float)windowSize.x, 0.f, (float)windowSize.y, -1.f, 1.f);

    pDefaultShaderProgram->SetMatrix4x4("projectionMat", projectionMatrix);

    while (!glfwWindowShouldClose(pWindow))
    {

        glClear(GL_COLOR_BUFFER_BIT);
        pDefaultShaderProgram->UseShader();
        glBindVertexArray(vao);
        texture->Bind();

        pDefaultShaderProgram->SetMatrix4x4("modelMat", modelMatrix1);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        pDefaultShaderProgram->SetMatrix4x4("modelMat", modelMatrix2);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }
}
    glfwTerminate();
    return 0;
}