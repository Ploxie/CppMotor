#pragma once
#include "VulkanSurface.h"
#include "VulkanSurfaceProperties.h"

namespace Vulkan
{
	typedef VkSurfaceTransformFlagBitsKHR SurfaceTransformFlags;

	struct SwapchainProperties
	{
		uint imageCount;
		Surface surface;
		SurfaceFormat surfaceFormat;
		SurfaceTransformFlags transformFlags;
		PresentMode presentMode;
		VkExtent2D extent;
	};
}