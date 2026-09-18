#include <WP_Window.h>
#include <stdexcept>
#include <WP_Graphics.h>
#include <iostream>

WP_Window::WP_Window(int width, int height,std::string name,
	WindowProcessFunction process, const WP_Window* windowToShareContextWith):
	m_currentWidth(width),
	m_currentHeight(height),
	m_process(process)
{
	m_window = glfwCreateWindow(m_currentWidth, m_currentHeight, 
		name.c_str(), nullptr,
		windowToShareContextWith ? windowToShareContextWith->m_window : nullptr);
	glViewport(0, 0, m_currentWidth, m_currentHeight);

	if (!m_window)
	{
		throw std::runtime_error("Failed to create openglWindow");
	}


	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);
	glfwSetFramebufferSizeCallback(m_window, ResizeWindow);


	if (!WP_Graphics::GetIsGlewInit())
	{
		WP_Graphics::InitialiseGlew();
	}

}

WP_Window::~WP_Window()
{
	glfwDestroyWindow(m_window);
}

bool WP_Window::RunWindow()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwMakeContextCurrent(m_window);
	m_process();
	glfwPollEvents();
	glfwSwapBuffers(m_window);

	if (glfwWindowShouldClose(m_window))
	{
		return false;
	}
	return true;
}

void WP_Window::ResizeWindow(GLFWwindow* window,
	int width, int height)
{
	WP_Window* currentWindow = 
		static_cast<WP_Window*>(glfwGetWindowUserPointer(window));
	currentWindow->m_currentWidth = width;
	currentWindow->m_currentHeight = height;
	glViewport(0, 0, currentWindow->m_currentWidth,
		currentWindow->m_currentHeight);
}