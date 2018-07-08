#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "PhysicalDevice.h"


namespace Vulkan
{
	struct InstanceProperties;
	class DebugReportCallback;

	class Instance
	{
	public:
		Instance(const InstanceProperties& properties);
		
		void Destroy();

		const std::vector<PhysicalDevice>& GetPhysicalDevices() const;

	private:

		VkInstance internal;
		std::vector<PhysicalDevice> physicalDevices;

		DebugReportCallback* callback;
	};
}