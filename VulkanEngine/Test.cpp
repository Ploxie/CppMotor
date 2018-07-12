#pragma once
#include <iostream>
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <VulkanInstance.h>
#include <GLFWWindow.h>
#include "VulkanInstanceProperties.h"

#include <VulkanFileUtil.h>

using namespace Engine;

Vulkan::SurfaceFormat GetSurfaceFormat(const std::vector<Vulkan::SurfaceFormat>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
		return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

Vulkan::PresentMode GetPresentMode(const std::vector<Vulkan::PresentMode>& availablePresentModes)
{
	Vulkan::PresentMode bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		}
		else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availablePresentMode;
		}
	}

	return bestMode;
}

int main()
{

	glfwInit();

	Window* window = new GLFWWindow(800, 600, "ASD", WINDOWED);
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

	Vulkan::SurfaceProperties surfaceProperties = physicalDevices[0].GetSurfaceProperties(surface);
	
	std::vector<const char*> extensions = 
	{
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	
	};
	Vulkan::LogicalDevice logicalDevice = physicalDevices[0].CreateLogicalDevice(physicalDevices[0].GetFeatures(), extensions, VK_QUEUE_GRAPHICS_BIT);

	uint imageCount = surfaceProperties.capabilities.minImageCount + 1;
	uint maxImageCount = surfaceProperties.capabilities.maxImageCount;
	if (maxImageCount > 0 && imageCount > maxImageCount)
	{
		imageCount = maxImageCount;
	}

	Vulkan::SwapchainProperties swapchainProperties = {};
	swapchainProperties.imageCount = imageCount;
	swapchainProperties.surface = surface;
	swapchainProperties.surfaceFormat = GetSurfaceFormat(surfaceProperties.formats);
	swapchainProperties.transformFlags = surfaceProperties.capabilities.currentTransform;
	swapchainProperties.presentMode = GetPresentMode(surfaceProperties.presentModes);
	swapchainProperties.extent = VkExtent2D {800,600};
	
	Vulkan::Swapchain swapchain = logicalDevice.CreateSwapchain(swapchainProperties);

	auto images = swapchain.GetImages();

	std::cout << "Swapchain Images: " << std::endl;
	for (uint i = 0; i < images.size(); i++)
	{
		std::cout << "-----------------------------------" << std::endl;
		std::cout << images[i].GetHandle() << std::endl;
		std::cout << "Type: " << images[i].GetType() << std::endl;
		std::cout << "Layout: " << images[i].GetLayout() << std::endl;
		std::cout << "Width: " << images[i].GetWidth() << std::endl;
		std::cout << "Height: " << images[i].GetHeight() << std::endl;
		std::cout << "Depth: " << images[i].GetDepth() << std::endl;
		std::cout << "-----------------------------------" << std::endl;
		std::cout << std::endl;
	}

	auto vertShaderCode = Vulkan::IO::readFile("D:/Programming/C++/Motor/Motor/quad.vert.spv");
	
	Vulkan::ShaderStage vertShader = logicalDevice.CreateShaderStage(vertShaderCode, VK_SHADER_STAGE_VERTEX_BIT);


	//Vulkan::QueueFamilyProperties graphicsQueue = *physicalDevice.GetFirstGraphicsQueue();

	//Vulkan::LogicalDevice logicalDevice = physicalDevice.CreateLogicalDevice({ VK_KHR_SWAPCHAIN_EXTENSION_NAME }, { { graphicsQueue,  1.0f } });

	//Vulkan::Queue queue = logicalDevice.GetQueue(graphicsQueue.GetIndex(), 0);

	//Vulkan::Surface surface = instance.CreateWindowSurface(window->GetHandle());
	

	
	system("pause");
	logicalDevice.DestroyShaderStage(vertShader);
	logicalDevice.DestroySwapchain(swapchain);
	logicalDevice.Destroy();
	instance.Destroy();
	system("pause");
	return 0;
}