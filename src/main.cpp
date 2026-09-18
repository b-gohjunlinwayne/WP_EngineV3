#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <WP_Window.h>
#include <WP_Graphics.h>
#include <WP_Math.h>
#include <WP_Validation.h>
#include <filesystem>
#include <WP_Logger.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


WP_Vec3f Triangle[] =
{
    WP_Vec3f(-0.5,-0.5,0),
    WP_Vec3f(0.5,-0.5,0),
    WP_Vec3f(0,0.5f,0)
};

unsigned int VAO;
unsigned int VBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

void UpdateLoop()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void UpdateLoop2()
{

}

int main()
{

    WP_Validation::RunAllValidations();
    WP_Graphics::InitialiseGLFW();
    {
        std::unique_ptr<WP_Window> mainWindow = std::make_unique<WP_Window>(
            800, 600,
            "mainWindow",
            UpdateLoop
        );

        WP_Logger() << std::filesystem::current_path() << '\n';
        WP_Graphics::LoadShader("defaultShader", 
            "Assets/Shader/DefaultShader/DefaultVert.vert", 
            "Assets/Shader/DefaultShader/DefaultFrag.frag");

        std::optional<WP_Shader> shader = WP_Graphics::GetShader("defaultShader");
        if (!shader.has_value())
        {
			WP_Logger(WP_LogLevel::Error) << "Cannot find default shader";
        }
        shader.value().Use();

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
            sizeof(Triangle), Triangle, GL_STATIC_DRAW);

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // 0. copy our vertices array in a buffer for OpenGL to use
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle), Triangle, GL_STATIC_DRAW);
        // 1. then set the vertex attributes pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // 2. use our shader program when we want to render an object
        glUseProgram(shaderProgram);

        std::unique_ptr <WP_Window> subWindow = std::make_unique<WP_Window>(
            800, 600,
            "subWindow",
            UpdateLoop2
        );

        while (mainWindow->RunWindow())
        {
            if (subWindow && !subWindow->RunWindow())
            {
                subWindow.reset();
            }
        }


        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }
    return 0;
}