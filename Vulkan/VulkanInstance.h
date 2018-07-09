#pragma once
#include <vulkan/vulkan.h>
#include <vector>
#include "VulkanPhysicalDevice.h"
#include "VulkanDebugReportCallback.h"
#include "VulkanSurface.h"
#include <BasicTypes.h>

namespace Vulkan
{
	struct InstanceProperties;

	class Instance
	{
	public:
		Instance(const InstanceProperties& properties);
		
		void Destroy();

 		const Surface CreateWindowSurface(const WindowHandle& windowHandle) const;

		const std::vector<PhysicalDevice>& GetPhysicalDevices() const;

	private:

		VkInstance internal;
		std::vector<PhysicalDevice> physicalDevices;

		DebugReportCallback callback;
	};
}