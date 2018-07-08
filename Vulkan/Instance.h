#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "PhysicalDevice.h"
#include "DebugReportCallback.h"

namespace Vulkan
{
	struct InstanceProperties;

	class Instance
	{
	public:
		Instance(const InstanceProperties& properties);
		
		void Destroy();

		const std::vector<PhysicalDevice>& GetPhysicalDevices() const;

	private:

		VkInstance internal;
		std::vector<PhysicalDevice> physicalDevices;

		DebugReportCallback callback;
	};
}