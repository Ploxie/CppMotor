#pragma once
#include <vulkan/vulkan.h>
#include <string>
#include <vector>
#include "QueueFamilyProperties.h"

namespace Vulkan
{
	class PhysicalDevice
	{
	public:
		PhysicalDevice();
		PhysicalDevice(const VkPhysicalDevice& physicalDevice);

		const std::string GetName() const;

		const QueueFamilyProperties* GetFirstGraphicsQueue() const;

	private:
		VkPhysicalDevice internal;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;

		std::vector<QueueFamilyProperties> queueFamilyPropertiesList;
	};
}