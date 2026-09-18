#include <WP_Graphics.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <WP_Logger.h>

bool WP_Graphics::s_glewInit = false;

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

void WP_Graphics::LoadShader(const std::string& _shaderName,
	const std::string& _vertexPath, const std::string& _fragmentPath)
{
	WP_ShaderManager::GetInstance().LoadShader(_shaderName, _vertexPath, _fragmentPath);
}

std::optional<WP_Shader> WP_Graphics::GetShader(const std::string& _shaderName)
{
	return WP_ShaderManager::GetInstance().GetShader(_shaderName);
}

bool WP_Graphics::GetIsGlewInit()
{
	return s_glewInit;
}

void WP_Graphics::Cleanup()
{
	WP_ShaderManager::GetInstance().CleanUp();
	glfwTerminate();
}