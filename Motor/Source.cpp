#pragma once
#include <iostream>
#include "GLFWWindow.h"

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

using namespace Engine;

int main()
{
	glfwInit();

	Window* window = new GLFWWindow(50, 50 , "ASD", WINDOWED);
	window->Create();
	
	WindowHandle handle = window->GetHandle();

	std::cout << handle << std::endl;

	system("pause");
	return 0;
}