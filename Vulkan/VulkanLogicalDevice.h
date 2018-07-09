#pragma once
#include <vector>
#include "VulkanQueueFamilyProperties.h"
#include <vulkan/vulkan.h>
#include <map>
#include "VulkanQueue.h"

namespace Vulkan
{

	struct LogicalDeviceQueueCreateInfo
	{
		QueueFamilyProperties properties;
		float priorities;
	};

	class LogicalDevice
	{
	public:
		LogicalDevice(const VkDevice& internal);

		const Queue& GetQueue(const uint& queueFamilyIndex, const uint& queueIndex);

		void Destroy();

	private:
		VkDevice internal;
		std::map<std::string, Queue> queues;
		
	};
}