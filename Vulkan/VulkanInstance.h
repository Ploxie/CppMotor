#pragma once
#include "stdafx.h"
#include <vector>
#include "VulkanPhysicalDevice.h"
#include "VulkanSurface.h"

namespace Vulkan
{
	struct InstanceProperties;

	class Instance
	{
	public:
		Instance(const InstanceProperties& properties);
		
		const Surface CreateSurface(const WindowHandle& window) const;


		//TODO: Add Method to find device with certain properties
		const std::vector<PhysicalDevice> GetPhysicalDevices() const;

		void Destroy();
	private:
		VkInstance internal;
	};
}