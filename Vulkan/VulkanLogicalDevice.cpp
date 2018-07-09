#pragma once
#include "VulkanLogicalDevice.h"
#include "VulkanUtil.h"
#include <iostream>

namespace Vulkan
{

	LogicalDevice::LogicalDevice(const VkDevice& internal) : internal(internal)
	{

	}

	const Queue& LogicalDevice::GetQueue(const uint& queueFamilyIndex, const uint& queueIndex)
	{
		std::string cacheKey = std::to_string(queueFamilyIndex) + " : " + std::to_string(queueIndex);

		if (queues.find(cacheKey) == queues.end())
		{
			VkQueue graphicsQueue;
			vkGetDeviceQueue(internal, queueFamilyIndex, queueIndex, &graphicsQueue);
			queues.insert(std::pair<std::string, Queue>(cacheKey, Queue(graphicsQueue)));
		}

		return queues.at(cacheKey);
	}

	void LogicalDevice::Destroy()
	{
		vkDestroyDevice(internal, 0);
	}

}