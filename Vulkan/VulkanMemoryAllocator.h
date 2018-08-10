#pragma once
#include "stdafx.h"
#include "VulkanMemoryUsage.h"
#include "VulkanCommandBuffer.h"
#include "VulkanMemoryAllocation.h"

namespace Vulkan
{


	struct Buffer
	{
		VkBuffer buffer;
		MemoryAllocation allocation;
	};

	class PhysicalDevice;

	class VulkanMemoryAllocator
	{
	public:
		VulkanMemoryAllocator(const VkDevice& logicalDevice, const PhysicalDevice& physicalDevice);

		const Buffer CreateBuffer(const VkBufferCreateInfo& createInfo, const VulkanMemoryUsage& usage);		

	private:
		const MemoryAllocation AllocateMemory(const VulkanMemoryUsage& memoryUsage, const VkMemoryRequirements& memoryRequirement) const;
		const uint GetMemoryTypeIndex(uint memoryTypeBits, const VulkanMemoryUsage& memoryUsage) const;

		const VkDevice& logicalDevice;
		const PhysicalDevice& physicalDevice;
	};
}