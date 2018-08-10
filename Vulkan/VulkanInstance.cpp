#include "stdafx.h"
#include "VulkanInstance.h"
#include <GLFW/glfw3.h>
#include "VulkanInstanceProperties.h"
#include "VulkanUtil.h"
#include "GLFWWindow.h"

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
		createInfo.enabledExtensionCount = static_cast<uint>(extensions.size());
		createInfo.ppEnabledExtensionNames = extensions.data();
		createInfo.enabledLayerCount = static_cast<uint>(layers.size());
		createInfo.ppEnabledLayerNames = layers.data();

		VkResult result = vkCreateInstance(&createInfo, 0, &internal);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to create Vulkan Instance: " + VulkanUtil::translateVulkanResult(result));
		}
	}

	void Instance::Destroy()
	{
		vkDestroyInstance(internal, 0);
	}

	const VkSurfaceKHR Instance::CreateSurface(Engine::GLFWWindow& window) const
	{
		VkSurfaceKHR surface;

		glfwCreateWindowSurface(internal, window.GetInternal(), 0, &surface);
		return surface;
	}
	
	const std::vector<PhysicalDevice> Instance::GetPhysicalDevices() const
	{
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(internal, &deviceCount, nullptr);

		if (deviceCount == 0) {			
			Logging::showError("Failed to find Devices with Vulkan support!");
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
