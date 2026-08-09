#pragma once
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

class WP_Window
{
public:
	using WindowProcessFunction = void (*)();

private:
	GLFWwindow* m_window;

	int m_currentWidth;
	int m_currentHeight;

	WindowProcessFunction m_process;

public:

	WP_Window(int width, int height,std::string name,
		WindowProcessFunction process);
	~WP_Window();

	bool RunWindow();

	bool isWindowOpen();

	static void ResizeWindow(GLFWwindow* window,
		int width, int height);
};

