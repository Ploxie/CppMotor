#pragma once
#include "LogicalDevice.h"
#include "VulkanUtil.h"
#include <iostream>

namespace Vulkan
{

	LogicalDevice::LogicalDevice(const VkDevice& internal) : internal(internal)
	{
		
	}

	void LogicalDevice::Destroy()
	{
		vkDestroyDevice(internal, 0);
	}

}