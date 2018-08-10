#pragma once
#include "stdafx.h"
#include "VulkanUtil.h"

namespace Vulkan
{
	class DebugReportCallback
	{
	public:
		inline DebugReportCallback();
		inline DebugReportCallback(const VkInstance& instance);
				
		inline void Destroy(const VkInstance& instance);

	protected:
		bool created;
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
		
		return VK_FALSE;
	}

	 static VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
		auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
		if (func != nullptr) {
			return func(instance, pCreateInfo, pAllocator, pCallback);
		}
		else {
			return VK_ERROR_EXTENSION_NOT_PRESENT;
		}
	}

	 static void DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
		auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
		if (func != nullptr) {
			func(instance, callback, pAllocator);
		}
	}

	inline DebugReportCallback::DebugReportCallback()
	{
		created = false;
	}

	inline DebugReportCallback::DebugReportCallback(const VkInstance& instance)
	{		
		VkDebugReportCallbackCreateInfoEXT createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
		createInfo.pfnCallback = debugCallback;

		VkResult result = CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to setup debug callback: " + VulkanUtil::translateVulkanResult(result));
		}

		created = true;
	}

	inline void DebugReportCallback::Destroy(const VkInstance& instance)
	{
		if (created)
		{		
			DestroyDebugReportCallbackEXT(instance, callback, 0);
		}
	}

	
}