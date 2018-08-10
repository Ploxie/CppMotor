#pragma once
#include "stdafx.h"
#include <vector>
#include "VulkanLogicalDevice.h"
#include "VulkanSurfaceProperties.h"

#include "IPhysicalGraphicsDevice.h"


namespace Vulkan
{
	class PhysicalDevice : public IPhysicalGraphicsDevice
	{
	public:
		inline PhysicalDevice();
		PhysicalDevice(const VkPhysicalDevice& physicalDevice);
		
		const ILogicalGraphicsDevice CreateLogicalDevice(const std::vector<std::string>& extensions, const uint graphicsQueueCount, const uint computeQueueCount) const override;

		const SurfaceProperties GetSurfaceProperties(const VkSurfaceKHR& surface) const;
				
		const uint GetQueueFamilyIndex(const VkQueueFlags& flagBit) const;
		const bool IsExtensionSupported(const char* extension, const uint& minVersion) const;
		const int GetPresentQueueFamilyIndex(const VkSurfaceKHR& surface) const;

		inline const VkPhysicalDeviceProperties& GetProperties() const;
		inline const VkPhysicalDeviceFeatures& GetFeatures() const;
		inline const VkPhysicalDeviceMemoryProperties& GetMemoryProperties() const;
		inline const std::vector<VkQueueFamilyProperties>& GetQueueFamilyProperties() const;
		inline const std::vector<VkExtensionProperties>& GetSupportedExtensions() const;


		inline const std::string GetName() const override;
		inline const uint GetDriverVersion() const override;
		inline const uint GetVendorId() const override;
		inline const uint GetDeviceId() const override;

	protected:
		VkPhysicalDevice internal;
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		VkPhysicalDeviceMemoryProperties memoryProperties;

		std::vector<VkQueueFamilyProperties> queueFamilyProperties;
		std::vector<VkExtensionProperties> supportedExtensions;
	};

	inline PhysicalDevice::PhysicalDevice() : internal(0)
	{

	}

	inline const VkPhysicalDeviceProperties& PhysicalDevice::GetProperties() const
	{
		return properties;
	}

	inline const VkPhysicalDeviceFeatures& PhysicalDevice::GetFeatures() const
	{
		return features;
	}

	inline const VkPhysicalDeviceMemoryProperties& PhysicalDevice::GetMemoryProperties() const
	{
		return memoryProperties;
	}

	inline const std::vector<VkQueueFamilyProperties>& PhysicalDevice::GetQueueFamilyProperties() const
	{
		return queueFamilyProperties;
	}

	inline const std::vector<VkExtensionProperties>& PhysicalDevice::GetSupportedExtensions() const
	{
		return supportedExtensions;
	}

	inline const std::string PhysicalDevice::GetName() const
	{
		return std::string(properties.deviceName);
	}

	inline const uint PhysicalDevice::GetDriverVersion() const
	{
		return properties.driverVersion;
	}

	inline const uint PhysicalDevice::GetVendorId() const
	{
		return properties.vendorID;
	}

	inline const uint PhysicalDevice::GetDeviceId() const
	{
		return properties.deviceID;
	}

}