#pragma once
#include <vector>
#include "QueueFamilyProperties.h"
#include <vulkan/vulkan.h>

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

		void Destroy();

	private:
		VkDevice internal;

	};
}