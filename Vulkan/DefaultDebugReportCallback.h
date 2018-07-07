#pragma once
#include "DebugReportCallback.h"
#include <iostream>

namespace Vulkan
{
	class DefaultDebugReportCallback : public DebugReportCallback
	{
	public:

		inline VKAPI_ATTR VkBool32 VKAPI_CALL invoke(VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* msg,
			void* userData) override;

	};

	inline VKAPI_ATTR VkBool32 VKAPI_CALL DefaultDebugReportCallback::invoke(VkDebugReportFlagsEXT flags,
		VkDebugReportObjectTypeEXT objType,
		uint64_t obj,
		size_t location,
		int32_t code,
		const char* layerPrefix,
		const char* msg,
		void* userData)
	{

		std::cerr << "validation layer: " << msg << std::endl;

		return VK_FALSE;

	}
}