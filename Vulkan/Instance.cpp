#include "Instance.h"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "InstanceProperties.h"
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

		if (enableValidationLayer)
		{
			//callback = DebugReportCallback(internal);
		}

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(internal, &deviceCount, nullptr);

		if (deviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		physicalDevices = std::vector<PhysicalDevice>(deviceCount);
		vkEnumeratePhysicalDevices(internal, &deviceCount, devices.data());
		for (unsigned int i = 0; i < deviceCount; i++)
		{
			physicalDevices[i] = PhysicalDevice(devices[i]);
		}
	}

	void Instance::Destroy()
	{
		callback.Destroy(internal);

		vkDestroyInstance(internal, 0);
	}

	const std::vector<PhysicalDevice>& Instance::GetPhysicalDevices() const
	{
		return physicalDevices;
	}
	
	
}
