#include <WP_Graphics.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <WP_Logger.h>

bool WP_Graphics::s_glewInit = false;
WP_ShaderManager WP_Graphics::s_shaderManager;

void WP_Graphics::InitialiseGLFW()
{
	if (!glfwInit())
	{
		throw std::runtime_error("GLFWInit failed");
	}
}

void WP_Graphics::InitialiseGlew()
{
	s_glewInit = true;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		std::string errorMsg = "GLEW init failed: " +
			std::string(reinterpret_cast<const char*>(glewGetErrorString(err)));

		throw std::runtime_error(errorMsg);
	}

	WP_Logger() << "GLEW initialized successfully!\n";
	WP_Logger() << "GLEW version: "
		<< glewGetString(GLEW_VERSION) << '\n';

}

void WP_Graphics::LoadShader(const std::string& shaderName,
	const std::string& vertexPath, const std::string& fragmentPath)
{
	s_shaderManager.LoadShader(shaderName, vertexPath, fragmentPath);
}

std::optional<WP_Shader> WP_Graphics::GetShader(const std::string& shaderName)
{
	return s_shaderManager.GetShader(shaderName);
}

bool WP_Graphics::GetIsGlewInit()
{
	return s_glewInit;
}

void WP_Graphics::Cleanup()
{
	s_shaderManager.CleanUp();
	glfwTerminate();
}