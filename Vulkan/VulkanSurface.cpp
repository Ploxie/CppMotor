#pragma once
#include "VulkanSurface.h"

namespace Vulkan
{
	Surface::Surface(const VkSurfaceKHR& surface)
	{
		this->surface = surface;
	}
}