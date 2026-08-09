#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "GLFW init failed\n";
        return 1;
    }

    GLFWwindow* window =
        glfwCreateWindow(800, 600, "GLEW Test", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Window creation failed\n";
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLenum err = glewInit();

    if (err != GLEW_OK)
    {
        std::cerr << "GLEW init failed: "
            << glewGetErrorString(err) << '\n';
        glfwDestroyWindow(window);
        glfwTerminate();
        return 1;
    }

    std::cout << "GLEW initialized successfully!\n";
    std::cout << "GLEW version: "
        << glewGetString(GLEW_VERSION) << '\n';

    glViewport(0, 0, 800, 600);
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}