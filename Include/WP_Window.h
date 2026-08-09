#pragma once
#include <GLFW/glfw3.h>
#include <memory>

class WP_Window
{
	GLFWwindow* window;

	int currentWidth;
	int currentHeight;

public:
	using WindowProcessFunction = void (*)();

	WP_Window(int width, int height);
	~WP_Window();
	void RunWindow(WindowProcessFunction process);
};

