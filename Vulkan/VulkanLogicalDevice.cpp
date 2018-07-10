#pragma once
#include "stdafx.h"
#include "VulkanLogicalDevice.h"
#include "VulkanUtil.h"
#include <iostream>
#include "VulkanPhysicalDevice.h"

namespace Vulkan
{
	
	LogicalDevice::LogicalDevice(const VkDevice& internal, const QueueFamilyIndices& queueFamilyIndices) : internal(internal), queueFamilyIndices(queueFamilyIndices)
	{

	}

	//const Swapchain LogicalDevice::CreateSwapchain(const SurfaceFormat& format, const PresentMode& presentMode, const VkExtent2D& extent, const Swapchain* oldSwapchain = nullptr) const

		
	void LogicalDevice::Destroy()
	{
		vkDestroyDevice(internal, 0);
	}

}