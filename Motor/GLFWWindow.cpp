#include "GLFWWindow.h"
#include <GLFW/glfw3.h>

namespace Engine
{

	GLFWWindow::GLFWWindow()
	{
		SetTitle("Title");			
		SetDimensions(800, 600);
		SetWindowMode(WINDOWED);
	}

	GLFWWindow::GLFWWindow(const uint& width, const uint& height, const char* title, const WindowMode& windowMode)
	{
		SetTitle(title);
		SetDimensions(width, height);
		SetWindowMode(windowMode);
	}

	void GLFWWindow::Create()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		if (windowMode == BORDERLESS)
		{
			glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		}
		else
		{
			glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
		}

		GLFWmonitor* monitor = 0;
		if (windowMode == FULL_SCREEN)
		{
			monitor = glfwGetPrimaryMonitor();
		}

		this->window = glfwCreateWindow(width, height, title, monitor, 0);
	}

	bool GLFWWindow::IsActive()
	{
		return !glfwWindowShouldClose(window);
	}

	void GLFWWindow::Update()
	{
		glfwPollEvents();
	}

	void GLFWWindow::Destroy()
	{
		glfwDestroyWindow(window);
	}

	void GLFWWindow::SetDimensions(const uint& width, const uint& height)
	{
		this->width = width;
		this->height = height;
	}

	void GLFWWindow::SetTitle(const char* title)
	{
		this->title = title;
	}

	void GLFWWindow::SetWindowMode(const WindowMode& windowMode)
	{
		this->windowMode = windowMode;
	}



}