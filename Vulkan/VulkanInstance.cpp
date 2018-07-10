#include "stdafx.h"
#include "VulkanInstance.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "VulkanInstanceProperties.h"
#include "VulkanUtil.h"

namespace Vulkan
{

	Instance::Instance(const InstanceProperties& properties)
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = properties.applicationInfo.applicationName;
		appInfo.applicationVersion = properties.applicationInfo.applicationVersion.GetVersion();
		appInfo.pEngineName = properties.applicationInfo.engineName;
		appInfo.engineVersion = properties.applicationInfo.engineVersion.GetVersion();
		appInfo.apiVersion = properties.applicationInfo.apiVersion.GetVersion();

		uint32_t glfwExtensionCount;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> extensions(glfwExtensionCount + properties.extensions.size());

		uint32_t extensionIndex = 0;
		for (; extensionIndex < properties.extensions.size(); extensionIndex++)
		{
			extensions[extensionIndex]  = (properties.extensions[extensionIndex]);
		}

		for (uint32_t i = 0; i < glfwExtensionCount;i++)
		{
			extensions[extensionIndex+i] = (glfwExtensions[i]);
		}
		
		std::vector<const char*> layers(properties.layers.size());

		for (uint32_t i = 0; i < properties.layers.size(); i++)
		{
			layers[i] = (properties.layers[i]);
		}

#ifdef NDEBUG
		const bool enableValidationLayer = false;
#else
		const bool enableValidationLayer = true; // FIX
#endif		
		
		if (enableValidationLayer)
		{
			extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
			layers.push_back("VK_LAYER_LUNARG_standard_validation");
		}
		

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = extensions.size();
		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.enabledLayerCount = layers.size();
		createInfo.ppEnabledLayerNames = layers.data();

		VkResult result = vkCreateInstance(&createInfo, 0, &internal);
		if (result != VK_SUCCESS)
		{
			std::cerr << "Failed to create Vulkan Instance: " << translateVulkanResult(result) << std::endl;
		}
	}

	void Instance::Destroy()
	{
		vkDestroyInstance(internal, 0);
	}

	const Surface Instance::CreateSurface(const WindowHandle& window) const
	{
		VkWin32SurfaceCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
		createInfo.hwnd = window;
		createInfo.hinstance = GetModuleHandle(nullptr);

		auto CreateWin32SurfaceKHR = (PFN_vkCreateWin32SurfaceKHR)vkGetInstanceProcAddr(internal, "vkCreateWin32SurfaceKHR");

		if (!CreateWin32SurfaceKHR) {
			std::cerr << "Failed to find function: vkCreateWin32SurfaceKHR" << std::endl;
		}

		Surface surface;

		VkResult result = CreateWin32SurfaceKHR(internal, &createInfo, 0, &surface);
		if (result != VK_SUCCESS) {
			std::cerr << "Failed to create window surface: " << translateVulkanResult(result) << std::endl;
		}

		return surface;
	}
	
	const std::vector<PhysicalDevice> Instance::GetPhysicalDevices() const
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(internal, &deviceCount, nullptr);

		if (deviceCount == 0) {			
			std::cerr << "Failed to find Devices with Vulkan support!" << std::endl;
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		std::vector<PhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(internal, &deviceCount, devices.data());
		for (unsigned int i = 0; i < deviceCount; i++)
		{
			physicalDevices[i] = PhysicalDevice(devices[i]);
		}

		return physicalDevices;
	}
	
	
}
