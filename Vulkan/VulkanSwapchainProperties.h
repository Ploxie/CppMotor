#pragma once
#include "stdafx.h"
#include "VulkanSurfaceProperties.h"

namespace Vulkan
{
	struct SwapchainProperties
	{
		uint imageCount;
		VkSurfaceKHR surface;
		VkSurfaceFormatKHR surfaceFormat;
		VkSurfaceTransformFlagBitsKHR transformFlags;
		VkPresentModeKHR presentMode;
		VkExtent2D extent;
	};
}