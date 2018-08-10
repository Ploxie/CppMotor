#include "stdafx.h"
#include "VulkanPhysicalDevice.h"
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
	
	const ILogicalGraphicsDevice PhysicalDevice::CreateLogicalDevice(const std::vector<std::string>& extensions, const uint graphicsQueueCount, const uint computeQueueCount) const
	{
		VkQueueFlags requestedQueueTypes = VK_QUEUE_TRANSFER_BIT;
		if (graphicsQueueCount > 0)
		{
			requestedQueueTypes |= VK_QUEUE_GRAPHICS_BIT;
		}
		if (computeQueueCount > 0)
		{
			requestedQueueTypes |= VK_QUEUE_COMPUTE_BIT;
		}

		VkPhysicalDeviceFeatures enabledFeatures = features;

		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos = {};
		const float queuePriority = 0.0f;

		QueuesInfo queuesInfo = {};

		if (requestedQueueTypes & VK_QUEUE_GRAPHICS_BIT)
		{
			queuesInfo.graphicsIndex = GetQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
			queuesInfo.graphicsQueueCount = graphicsQueueCount;

			VkDeviceQueueCreateInfo queueInfo = {};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queuesInfo.graphicsIndex;
			queueInfo.queueCount = graphicsQueueCount;
			queueInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueInfo);
		}

		if (requestedQueueTypes & VK_QUEUE_COMPUTE_BIT)
		{
			queuesInfo.computeIndex = GetQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
			queuesInfo.computeQueueCount = computeQueueCount;

			VkDeviceQueueCreateInfo queueInfo = {};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queuesInfo.computeIndex;
			queueInfo.queueCount = computeQueueCount;
			queueInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueInfo);
		}
		else
		{
			queuesInfo.computeIndex = queuesInfo.graphicsIndex;
			queuesInfo.computeQueueCount = graphicsQueueCount;
		}

		if (requestedQueueTypes & VK_QUEUE_TRANSFER_BIT)
		{
			queuesInfo.transferIndex = GetQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
			queuesInfo.transferQueueCount = 1;

			VkDeviceQueueCreateInfo queueInfo = {};
			queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueInfo.queueFamilyIndex = queuesInfo.transferIndex;
			queueInfo.queueCount = 1;
			queueInfo.pQueuePriorities = &queuePriority;

			queueCreateInfos.push_back(queueInfo);
		}
		else
		{
			queuesInfo.transferIndex = queuesInfo.graphicsIndex;
			queuesInfo.transferQueueCount = graphicsQueueCount;
		}
		
		uint extensionSize = static_cast<uint>(extensions.size());
		std::vector<const char*> enabledExtensions(extensionSize);
		for (uint i = 0; i < extensionSize; i++) {
			enabledExtensions[i] = extensions[i].c_str();
		}

		VkDeviceCreateInfo deviceCreateInfo = {};
		deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
		deviceCreateInfo.pEnabledFeatures = &enabledFeatures;
		deviceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(extensionSize);
		deviceCreateInfo.ppEnabledExtensionNames = enabledExtensions.data();

		VkDevice device;

		VkResult result = vkCreateDevice(internal, &deviceCreateInfo, nullptr, &device);
		if (result != VK_SUCCESS) {
			Logging::showError("Failed to create logical device: " + VulkanUtil::translateVulkanResult(result));
		}

		return LogicalDevice(device, *this, queuesInfo);
	}

	const SurfaceProperties PhysicalDevice::GetSurfaceProperties(const VkSurfaceKHR& surface) const
	{
		SurfaceProperties properties = {};
		VkResult result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(internal, surface, &properties.capabilities);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to get Surface capabilities: " + VulkanUtil::translateVulkanResult(result));
		}

		uint presentModeCount = 0;
		vkGetPhysicalDeviceSurfacePresentModesKHR(internal, surface, &presentModeCount, 0);

		properties.presentModes.resize(presentModeCount);
		result = vkGetPhysicalDeviceSurfacePresentModesKHR(internal, surface, &presentModeCount, properties.presentModes.data());
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to get Surface present Modes: " + VulkanUtil::translateVulkanResult(result));
		}

		uint formatCount = 0;
		vkGetPhysicalDeviceSurfaceFormatsKHR(internal, surface, &formatCount, 0);

		properties.formats.resize(formatCount);
		result = vkGetPhysicalDeviceSurfaceFormatsKHR(internal, surface, &formatCount, properties.formats.data());
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to get Surface Formats: " + VulkanUtil::translateVulkanResult(result));
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
			const VkExtensionProperties& ext = supportedExtensions[i];
			if (std::strcmp(ext.extensionName, extension) && ext.specVersion >= minVersion)
			{
				return true;
			}
		}
		return false;
	}

	const int PhysicalDevice::GetPresentQueueFamilyIndex(const VkSurfaceKHR& surface) const
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