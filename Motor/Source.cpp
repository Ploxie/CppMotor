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
	
	system("pause");
	return 0;
}