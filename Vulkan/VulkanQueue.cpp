#include "stdafx.h"
#include "VulkanQueue.h"
#include "VulkanLogicalDevice.h"

namespace Vulkan
{

	

	Queue::Queue(const VkQueue &queue, const LogicalDevice& logicalDevice) : internal(queue), logicalDevice(logicalDevice)
	{

	}

	



}
