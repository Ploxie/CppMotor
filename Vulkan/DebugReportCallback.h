#pragma once
#include <vulkan/vulkan.h>

namespace Vulkan
{
	class DebugReportCallback
	{
	public:

		virtual VKAPI_ATTR VkBool32 VKAPI_CALL invoke(VkDebugReportFlagsEXT flags,
			VkDebugReportObjectTypeEXT objType,
			uint64_t obj,
			size_t location,
			int32_t code,
			const char* layerPrefix,
			const char* msg,
			void* userData) = 0;

	};
}