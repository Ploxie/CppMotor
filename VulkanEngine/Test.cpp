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

	Vulkan::PhysicalDevice physicalDevice = instance.GetPhysicalDevices()[0];

	Vulkan::QueueFamilyProperties graphicsQueue = *physicalDevice.GetFirstGraphicsQueue();

	Vulkan::LogicalDevice logicalDevice = physicalDevice.CreateLogicalDevice({ VK_KHR_SWAPCHAIN_EXTENSION_NAME }, { { graphicsQueue,  1.0f } });

	Vulkan::Queue queue = logicalDevice.GetQueue(graphicsQueue.GetIndex(), 0);

	Vulkan::Surface surface = instance.CreateWindowSurface(window->GetHandle());

	std::cout << instance.GetPhysicalDevices()[0].GetName() << std::endl;
	



	logicalDevice.Destroy();
	instance.Destroy();
	system("pause");
	return 0;
}