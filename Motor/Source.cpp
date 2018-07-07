#pragma once
#include <iostream>
#include "GLFWWindow.h"

using namespace Engine;

int main()
{
	Window* window = new GLFWWindow(50, 50 , "ASD", WINDOWED);
	window->Create();



	std::cout << "hasdj" << std::endl;

	system("pause");
	return 0;
}