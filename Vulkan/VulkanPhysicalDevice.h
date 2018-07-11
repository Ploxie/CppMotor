#pragma once
#include "stdafx.h"
#include "VulkanPhysicalDeviceProperties.h"
#include "VulkanPhysicalDeviceFeatures.h"
#include "VulkanPhysicalDeviceMemoryProperties.h"
#include "VulkanQueueFlags.h"
#include "VulkanExtensionProperties.h"
#include <vector>
#include "VulkanQueueFamilyProperties.h"
#include "VulkanLogicalDevice.h"
#include "VulkanSurface.h"
#include "VulkanSurfaceProperties.h"


namespace Vulkan
{
	class PhysicalDevice
	{
	public:
		inline PhysicalDevice();
		PhysicalDevice(const VkPhysicalDevice& physicalDevice);
		
		const LogicalDevice CreateLogicalDevice(const PhysicalDeviceFeatures& enabledFeatures, const std::vector<const char*>& extensions, const QueueFlags& queueFlags) const;

		const SurfaceProperties GetSurfaceProperties(const Surface& surface) const;
				
		const uint GetQueueFamilyIndex(const VkQueueFlags& flagBit) const;
		const bool IsExtensionSupported(const char* extension, const uint& minVersion) const;
		const int GetPresentQueueFamilyIndex(const Surface& surface) const;

		inline const PhysicalDeviceProperties& GetProperties() const;
		inline const PhysicalDeviceFeatures& GetFeatures() const;
		inline const PhysicalDeviceMemoryProperties& GetMemoryProperties() const;
		inline const std::vector<QueueFamilyProperties>& GetQueueFamilyProperties() const;
		inline const std::vector<ExtensionProperties>& GetSupportedExtensions() const;

	protected:
		VkPhysicalDevice internal;
		PhysicalDeviceProperties properties;
		PhysicalDeviceFeatures features;
		PhysicalDeviceMemoryProperties memoryProperties;

		std::vector<QueueFamilyProperties> queueFamilyProperties;
		std::vector<ExtensionProperties> supportedExtensions;
	};

	inline PhysicalDevice::PhysicalDevice() : internal(0)
	{

	}

	inline const PhysicalDeviceProperties& PhysicalDevice::GetProperties() const
	{
		return properties;
	}

	inline const PhysicalDeviceFeatures& PhysicalDevice::GetFeatures() const
	{
		return features;
	}

	inline const PhysicalDeviceMemoryProperties& PhysicalDevice::GetMemoryProperties() const
	{
		return memoryProperties;
	}

	inline const std::vector<QueueFamilyProperties>& PhysicalDevice::GetQueueFamilyProperties() const
	{
		return queueFamilyProperties;
	}

	inline const std::vector<ExtensionProperties>& PhysicalDevice::GetSupportedExtensions() const
	{
		return supportedExtensions;
	}

}