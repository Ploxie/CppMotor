#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "VulkanQueueFamilyProperties.h"
#include "VulkanLogicalDevice.h"

namespace Vulkan
{
	class PhysicalDevice
	{
	public:
		PhysicalDevice();
		PhysicalDevice(const VkPhysicalDevice& physicalDevice);

		const LogicalDevice CreateLogicalDevice(const std::vector<const char*>& extensions, const std::vector<LogicalDeviceQueueCreateInfo>& createInfo) const;

		const std::string GetName() const;

		const QueueFamilyProperties* GetFirstGraphicsQueue() const;

		const VkPhysicalDevice& GetInternal() const;

	private:
		VkPhysicalDevice internal;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;

		std::vector<QueueFamilyProperties> queueFamilyPropertiesList;
	};
}