#include "VulkanPhysicalDevice.h"
#include "stdafx.h"
#include <iostream>
#include "VulkanUtil.h"
#include "VulkanQueueFamilyIndices.h"

namespace Vulkan
{

	PhysicalDevice::PhysicalDevice(const VkPhysicalDevice& physicalDevice) : internal(physicalDevice)
	{

		vkGetPhysicalDeviceProperties(physicalDevice, &properties);		
		vkGetPhysicalDeviceFeatures(physicalDevice, &features);
		
		vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);

		uint32_t queueFamilyCount = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

		queueFamilyProperties.resize(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());
				
		uint32_t extensionCount = 0;
		vkEnumerateDeviceExtensionProperties(physicalDevice, 0, &extensionCount, 0);
		if (extensionCount > 0)
		{
			supportedExtensions.resize(extensionCount);
			vkEnumerateDeviceExtensionProperties(physicalDevice, 0, &extensionCount, supportedExtensions.data());
		}
	}

	const LogicalDevice PhysicalDevice::CreateLogicalDevice(const PhysicalDeviceFeatures& enabledFeatures, const std::vector<const char*>& extensions, const QueueFlags& queueFlags) const
	{
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = {};
		const float queuePriority = 0.0f;
		
		QueueFamilyIndices queueFamilyIndices = {};

		if (queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			queueFamilyIndices.graphics = GetQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);

			VkDeviceQueueCreateInfo queueInfo = {};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queueFamilyIndices.graphics;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueInfo);
		}

		if (queueFlags & VK_QUEUE_COMPUTE_BIT)
		{
			queueFamilyIndices.compute = GetQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);

			VkDeviceQueueCreateInfo queueInfo = {};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queueFamilyIndices.compute;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueInfo);
		}
		else
		{
			queueFamilyIndices.compute = queueFamilyIndices.graphics;
		}

		if (queueFlags & VK_QUEUE_TRANSFER_BIT)
		{
			queueFamilyIndices.transfer = GetQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);

			VkDeviceQueueCreateInfo queueInfo = {};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queueFamilyIndices.transfer;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueInfo);
		}
		else
		{
			queueFamilyIndices.transfer = queueFamilyIndices.graphics;
		}
				
		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint>(queueCreateInfos.size());		
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.enabledExtensionCount = static_cast<uint>(extensions.size());
		deviceCreateInfo.ppEnabledExtensionNames = extensions.data();
		deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

		VkDevice device;

		VkResult result = vkCreateDevice(internal, &deviceCreateInfo, nullptr, &device);
		if (result != VK_SUCCESS) {
			std::cerr << "Failed to create logical device: " << translateVulkanResult(result) << std::endl;
		}

		return LogicalDevice(device,*this, queueFamilyIndices);
	}

	const SurfaceProperties PhysicalDevice::GetSurfaceProperties(const Surface& surface) const
	{
		SurfaceProperties properties = {};
		VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(internal, surface, &properties.capabilities);
		if (result != VK_SUCCESS)
		{
			std::cerr << "Failed to get Surface capabilities: " << translateVulkanResult(result) << std::endl;
		}

		uint presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(internal, surface, &presentModeCount, 0);

		properties.presentModes.resize(presentModeCount);
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(internal, surface, &presentModeCount, properties.presentModes.data());
		if (result != VK_SUCCESS)
		{
			std::cerr << "Failed to get Surface present Modes: " << translateVulkanResult(result) << std::endl;
		}

		uint formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(internal, surface, &formatCount, 0);

		properties.formats.resize(formatCount);
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(internal, surface, &formatCount, properties.formats.data());
		if (result != VK_SUCCESS)
		{
			std::cerr << "Failed to get Surface Formats: " << translateVulkanResult(result) << std::endl;
		}

		return properties;
	}

	const uint PhysicalDevice::GetQueueFamilyIndex(const VkQueueFlags& queueFlags) const
	{
		if (queueFlags & VK_QUEUE_COMPUTE_BIT && !(queueFlags & VK_QUEUE_GRAPHICS_BIT))
		{
			for (uint i = 0; i < queueFamilyProperties.size(); i++)
			{
				const VkQueueFlags& flags = queueFamilyProperties[i].queueFlags;
				bool hasGraphicsBit = (flags & VK_QUEUE_GRAPHICS_BIT) != 0;

				if ((flags & queueFlags) && !hasGraphicsBit)
				{
					return i;
				}
			}
		}

		if (queueFlags & VK_QUEUE_TRANSFER_BIT && !(queueFlags & VK_QUEUE_GRAPHICS_BIT) && !(queueFlags & VK_QUEUE_COMPUTE_BIT))
		{
			for (uint i = 0; i < queueFamilyProperties.size(); i++)
			{
				const VkQueueFlags& flags = queueFamilyProperties[i].queueFlags;
				bool hasGraphicsBit = (flags & VK_QUEUE_GRAPHICS_BIT) != 0;
				bool hasComputeBit = (flags & VK_QUEUE_COMPUTE_BIT) != 0;

				if ((flags & queueFlags) && !hasGraphicsBit && !hasComputeBit)
				{
					return i;
				}
			}
		}

		for (uint i = 0; i < queueFamilyProperties.size(); i++) {
			const VkQueueFlags& flags = queueFamilyProperties[i].queueFlags;
			if (flags & queueFlags) {
				return i;
			}
		}

		return -1;
	}

	const bool PhysicalDevice::IsExtensionSupported(const char* extension, const uint& minVersion) const
	{
		for (uint i = 0; i < supportedExtensions.size(); i++)
		{
			const ExtensionProperties& ext = supportedExtensions[i];
			if (std::strcmp(ext.extensionName, extension) && ext.specVersion >= minVersion)
			{
				return true;
			}
		}
		return false;
	}

	const int PhysicalDevice::GetPresentQueueFamilyIndex(const Surface& surface) const
	{
		int index = -1;

		for (uint i = 0; i < queueFamilyProperties.size(); i++)
		{
			VkBool32 hasSupport = false;
			vkGetPhysicalDeviceSurfaceSupportKHR(internal, i, surface, &hasSupport);
			if (hasSupport)
			{
				return i;
			}
		}

		return index;
	}
	
	

}