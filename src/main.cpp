#include <iostream>
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

WP_ShaderID currentShaderID;
WP_MeshID currentMeshID;

unsigned int VAO;
unsigned int VBO;


void UpdateLoop()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

	WP_Graphics::GetShader(currentShaderID).Use();

    glBindVertexArray(WP_Graphics::GetMesh(currentMeshID).p_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{

    WP_Validation::RunAllValidations();
    WP_Graphics::InitialiseGLFW();
    {
        std::unique_ptr<WP_Window> mainWindow = std::make_unique<WP_Window>(
            800, 600,
            "mainWindow",
            UpdateLoop,
            nullptr
        );

        WP_Logger() << std::filesystem::current_path() << '\n';
        WP_Graphics::LoadShader("defaultShader", 
            "Assets/Shader/DefaultShader/DefaultVert.vert", 
            "Assets/Shader/DefaultShader/DefaultFrag.frag");

        std::optional<WP_ShaderID> shaderID = WP_Graphics::GetShaderID("defaultShader");
        if (!shaderID.has_value())
        {
			WP_Logger(WP_LogLevel::Error) << "Cannot find default shader";
            return 0;
        }
        else
        {
            currentShaderID = shaderID.value();
        }

        WP_Graphics::LoadMesh();

		std::optional<WP_MeshID> meshID = WP_Graphics::GetMeshID("testMesh");
        if (!meshID.has_value())
		{
            WP_Logger(WP_LogLevel::Error) << "Cannot find test mesh";
            return 0;
        }
        else
        {
            currentMeshID = meshID.value();
		}


        WP_Graphics::GetShader(currentShaderID).Use();

        /*
        std::unique_ptr <WP_Window> subWindow = std::make_unique<WP_Window>(
            800, 600,
            "subWindow",
            UpdateLoop2,
            mainWindow.get()
        );*/

        while (mainWindow->RunWindow())
        {
            /*
            if (subWindow && !subWindow->RunWindow())
            {
                subWindow.reset();
            }*/
        }

        WP_LogManager::GetInstance().Stop();
    }
    return 0;
}