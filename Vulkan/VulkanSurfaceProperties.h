#pragma once
#include "stdafx.h"
#include <vector>

namespace Vulkan
{
	typedef VkSurfaceCapabilitiesKHR SurfaceCapabilities;
	typedef VkSurfaceFormatKHR SurfaceFormat;
	typedef VkPresentModeKHR PresentMode;

	struct SurfaceProperties
	{
		SurfaceCapabilities capabilities;
		std::vector<SurfaceFormat> formats;
		std::vector<PresentMode> presentModes;
	};
}