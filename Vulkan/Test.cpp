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
	properties.extensions = {};
	properties.layers = {};

	Vulkan::Instance instance(properties);

	Vulkan::PhysicalDevice physicalDevice = instance.GetPhysicalDevices()[0];

	Vulkan::QueueFamilyProperties graphicsQueue = *physicalDevice.GetFirstGraphicsQueue();

	std::vector<const char*> extensions = 
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};
	std::vector<Vulkan::LogicalDeviceQueueCreateInfo> deviceQueueCreateInfo = 
	{
		{graphicsQueue,  1.0f }
	};


	Vulkan::LogicalDevice logicalDevice = physicalDevice.CreateLogicalDevice(extensions, deviceQueueCreateInfo);

	std::cout << instance.GetPhysicalDevices()[0].GetName() << std::endl;
	
	logicalDevice.Destroy();
	instance.Destroy();
	system("pause");
	return 0;
}