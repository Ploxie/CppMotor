#include "PhysicalDevice.h"
#include <BasicTypes.h>
#include <iostream>
#include "VulkanUtil.h"

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
			queueFamilyPropertiesList[i] = QueueFamilyProperties(i, queueFamilies[i]);
		}

	}

	const LogicalDevice PhysicalDevice::CreateLogicalDevice(const std::vector<const char*>& extensions, const std::vector<LogicalDeviceQueueCreateInfo>& createInfo) const
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(createInfo.size());
		for (uint i = 0; i < createInfo.size(); i++)
		{
			VkDeviceQueueCreateInfo queueCreateInfo = {};
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = createInfo[i].properties.GetIndex();
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = &createInfo[i].priorities;

			queueCreateInfos[i] = queueCreateInfo;
		}
		
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.queueCreateInfoCount = queueCreateInfos.size();
		deviceCreateInfo.ppEnabledExtensionNames = extensions.data();
		deviceCreateInfo.enabledExtensionCount = extensions.size();
		deviceCreateInfo.enabledLayerCount = 0;

		VkDevice device;

		VkResult result = vkCreateDevice(internal, &deviceCreateInfo, nullptr, &device);
		if (result != VK_SUCCESS) {
			std::cerr << "Failed to create logical device: " << translateVulkanResult(result) << std::endl;
		}

		return LogicalDevice(device);
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

	const VkPhysicalDevice& PhysicalDevice::GetInternal() const
	{
		return internal;
	}

}