#pragma once
#include <iostream>
#include "Instance.h"
#include <GLFW/glfw3.h>
#include "InstanceProperties.h"


int main() 
{
	glfwInit();

	Vulkan::ApplicationInfo appInfo = {};
	appInfo.applicationName = "Application";
	appInfo.engineName = "Engine";
	appInfo.applicationVersion = Vulkan::Version { 1 , 0, 0};
	appInfo.engineVersion = Vulkan::Version{ 1 , 0, 0 };
	appInfo.apiVersion = Vulkan::Version{ 1 , 0, 0 };

	Vulkan::InstanceProperties properties = {};
	properties.applicationInfo = appInfo;
	properties.extensions = {"VK_EXT_DEBUG_REPORT_EXTENSION_NAME"};
	properties.layers = {};

	Vulkan::Instance instance(properties);

	std::cout << instance.GetPhysicalDevices()[0].GetName() << std::endl;
	
	instance.Destroy();
	system("pause");
	return 0;
}