#include <WP_Graphics.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

	std::cout << "GLEW initialized successfully!\n";
	std::cout << "GLEW version: "
		<< glewGetString(GLEW_VERSION) << '\n';

}

bool WP_Graphics::GetIsGlewInit()
{
	return s_glewInit;
}

void WP_Graphics::Cleanup()
{
	glfwTerminate();
}