#include "PhysicalDevice.h"
#include <BasicTypes.h>

namespace Vulkan
{

	PhysicalDevice::PhysicalDevice()
	{
	}

	PhysicalDevice::PhysicalDevice(const VkPhysicalDevice & physicalDevice)
	{
		this->internal = physicalDevice;

		vkGetPhysicalDeviceProperties(physicalDevice, &properties);		
		vkGetPhysicalDeviceFeatures(physicalDevice, &features);

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

		queueFamilyPropertiesList = std::vector<QueueFamilyProperties>(queueFamilyCount);

		for (uint32_t i = 0; i < queueFamilyCount; i++)
		{
			queueFamilyPropertiesList[i] = QueueFamilyProperties(queueFamilies[i]);
		}

	}

	const std::string PhysicalDevice::GetName() const
	{
		return std::string(properties.deviceName);
	}

	const QueueFamilyProperties* PhysicalDevice::GetFirstGraphicsQueue() const
	{
		for(uint i = 0 ; i < queueFamilyPropertiesList.size();i++)
		{
			const QueueFamilyProperties &p = queueFamilyPropertiesList[i];
			if (p.HasGraphicsCapabilities())
			{
				return &p;
			}
		}

		return 0;
	}

}