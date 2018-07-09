#pragma once
#include <vulkan/vulkan.h>

namespace Vulkan
{
	class Queue
	{
	public:
		Queue(const VkQueue& internal);

	private:
		VkQueue internal;
	};
}