#pragma once
#include <iostream>
#include "Instance.h"
#include <GLFW/glfw3.h>

int main() 
{
	glfwInit();

	Vulkan::Instance instance;
	instance.Create();


	std::cout << "asd" << std::endl;
	
	system("pause");
	return 0;
}