#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer/ShaderManager.h"
#include "Resources/ResourceManager.h"

GLfloat points[] =
{
    0.0f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
};

GLfloat colors[] =
{
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
};



int XWindowSize = 640;
int YWindowSize = 480;

void glfwWindowSizeCallback(GLFWwindow* pWindow,  int width, int height)
{
    XWindowSize = width;
    YWindowSize = height;
    glViewport(0, 0, XWindowSize, YWindowSize);
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

    pWindow = glfwCreateWindow(XWindowSize, YWindowSize, "Welcome to the club, body!", NULL, NULL);
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

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    while (!glfwWindowShouldClose(pWindow))
    {

        glClear(GL_COLOR_BUFFER_BIT);
        pDefaultShaderProgram->UseShader();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }
}
    glfwTerminate();
    return 0;
}