#pragma once
#include <vulkan/vulkan.h>

namespace Vulkan
{
	class Surface
	{
	public:
		Surface(const VkSurfaceKHR& surface);

	private:
		VkSurfaceKHR surface;
	};
}