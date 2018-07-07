#include "Instance.h"

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <vector>

namespace Vulkan
{

	const Instance Instance::Create()
	{

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Application";
		appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.pEngineName = "Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		uint32_t glfwExtensionCount;
		const char** glfwExtensions;
		glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		std::vector<const char*> layers =
		{
			"VK_LAYER_LUNARG_standard_validation"
		};
		

		VkInstanceCreateInfo createInfo = {  };
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;
		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;
		createInfo.enabledLayerCount = layers.size();
		createInfo.ppEnabledLayerNames = layers.data();

		VkResult result = vkCreateInstance(&createInfo, 0, &internal);
		if (result != VK_SUCCESS)
		{
			throw std::runtime_error("Failed to create Vulkan Instance");
		}

		VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
		
		uint32_t deviceCount = 0;
		vkEnumeratePhysicalDevices(internal, &deviceCount, nullptr);

		if (deviceCount == 0) {
			throw std::runtime_error("failed to find GPUs with Vulkan support!");
		}

		std::vector<VkPhysicalDevice> devices(deviceCount);
		vkEnumeratePhysicalDevices(internal, &deviceCount, devices.data());


	}	

	void Instance::Destroy()
	{
		vkDestroyInstance(internal, 0);
	}
}
