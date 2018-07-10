#pragma once
#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <VulkanInstance.h>
#include <GLFWWindow.h>
#include "VulkanInstanceProperties.h"


using namespace Engine;

int main()
{

	glfwInit();

	Window* window = new GLFWWindow(50, 50, "ASD", WINDOWED);
	window->Create();

	Vulkan::ApplicationInfo appInfo = {};
	appInfo.applicationName = "Application";
	appInfo.engineName = "Engine";
	appInfo.applicationVersion = Vulkan::Version{ 1 , 0, 0 };
	appInfo.engineVersion = Vulkan::Version{ 1 , 0, 0 };
	appInfo.apiVersion = Vulkan::Version{ 1 , 0, 0 };

	Vulkan::InstanceProperties properties = {};
	properties.applicationInfo = appInfo;
	properties.extensions = {};
	properties.layers = {};

	Vulkan::Instance instance(properties);
	Vulkan::Surface surface = instance.CreateSurface(window->GetHandle());

	std::vector<Vulkan::PhysicalDevice> physicalDevices = instance.GetPhysicalDevices();

	for (uint i = 0; i < physicalDevices.size(); i++)
	{
		std::cout << "-----------------------------------" << std::endl;
		std::cout << physicalDevices[i].GetProperties().deviceName << std::endl;
		auto properties = physicalDevices[i].GetQueueFamilyProperties();

		std::cout << "Properties: " << std::endl;
		for (uint i = 0; i < properties.size(); i++)
		{
			std::cout << "Queue count: " << properties[i].queueCount << std::endl;
			std::cout << "Queue flags: " << properties[i].queueFlags << std::endl << std::endl;
		}

		auto extensions = physicalDevices[i].GetSupportedExtensions();
		std::cout << "Extensions: " << std::endl;
		for (uint i = 0; i < extensions.size(); i++)
		{
			std::cout << extensions[i].extensionName << std::endl;
		}

		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl << std::endl;
	}



	//Vulkan::QueueFamilyProperties graphicsQueue = *physicalDevice.GetFirstGraphicsQueue();

	//Vulkan::LogicalDevice logicalDevice = physicalDevice.CreateLogicalDevice({ VK_KHR_SWAPCHAIN_EXTENSION_NAME }, { { graphicsQueue,  1.0f } });

	//Vulkan::Queue queue = logicalDevice.GetQueue(graphicsQueue.GetIndex(), 0);

	//Vulkan::Surface surface = instance.CreateWindowSurface(window->GetHandle());
	


	


	//logicalDevice.Destroy();
	//instance.Destroy();
	system("pause");
	return 0;
}