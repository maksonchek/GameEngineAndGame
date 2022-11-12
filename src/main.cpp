#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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
int main(void)
{
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

    glClearColor(1, 1, 0, 1);



    while (!glfwWindowShouldClose(pWindow))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(pWindow);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}