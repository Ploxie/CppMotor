#pragma once
#include <vulkan/vulkan.h>
#include <iostream>
#include "VulkanUtil.h"

namespace Vulkan
{
	class DebugReportCallback
	{
	public:
		DebugReportCallback();
		DebugReportCallback(const VkInstance& instance);
				
		inline void Destroy(const VkInstance& instance);

	protected:
		VkDebugReportCallbackEXT callback;
	};

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData) {

		std::cerr << "validation layer: " << msg << std::endl;

		return VK_FALSE;
	}

	VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	DebugReportCallback::DebugReportCallback()
	{

	}

	DebugReportCallback::DebugReportCallback(const VkInstance& instance)
	{		
		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		VkResult result = CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback);
		if (result != VK_SUCCESS)
		{
			std::cerr << "Failed to setup debug callback: " << translateVulkanResult(result) << std::endl;
		}
	}

	inline void DebugReportCallback::Destroy(const VkInstance& instance)
	{
		DestroyDebugReportCallbackEXT(instance, callback, 0);
	}

	
}