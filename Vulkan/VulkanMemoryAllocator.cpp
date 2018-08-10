#include "stdafx.h"
#include "VulkanMemoryAllocator.h"
#include "VulkanUtil.h"
#include "VulkanPhysicalDevice.h"
#include <FastMath.h>

namespace Vulkan
{
	VulkanMemoryAllocator::VulkanMemoryAllocator(const VkDevice& logicalDevice, const PhysicalDevice& physicalDevice) : logicalDevice(logicalDevice), physicalDevice(physicalDevice)
	{

	}

	const Buffer VulkanMemoryAllocator::CreateBuffer(const VkBufferCreateInfo& createInfo, const VulkanMemoryUsage& usage)
	{
		Buffer buffer;
		
		VkResult result = vkCreateBuffer(logicalDevice, &createInfo, 0, &buffer.buffer);
		if (result != VK_SUCCESS) 
		{
			Logging::showError("Failed to create buffer: " + VulkanUtil::translateVulkanResult(result));
		}

		VkMemoryRequirements memoryRequirement;
		vkGetBufferMemoryRequirements(logicalDevice, buffer.buffer, &memoryRequirement);

		buffer.allocation = AllocateMemory(usage, memoryRequirement);
		return buffer;
	}

	const MemoryAllocation VulkanMemoryAllocator::AllocateMemory(const VulkanMemoryUsage& memoryUsage, const VkMemoryRequirements& memoryRequirement) const
	{
		const uint memoryTypeIndex = GetMemoryTypeIndex(memoryRequirement.memoryTypeBits, memoryUsage);
		
		VkMemoryAllocateInfo allocateInfo = {};
		allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocateInfo.pNext = 0;
		allocateInfo.allocationSize = -1;
		allocateInfo.memoryTypeIndex = memoryTypeIndex;

		MemoryAllocation allocation = {};
		VkResult result = vkAllocateMemory(logicalDevice, &allocateInfo, 0, &allocation.deviceMemory);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to allocate memory: " + VulkanUtil::translateVulkanResult(result));
		}

		return allocation;
	}

	const uint VulkanMemoryAllocator::GetMemoryTypeIndex(uint memoryTypeBits, const VulkanMemoryUsage& memoryUsage) const
	{
		uint32_t requiredFlags = 0;
		uint32_t preferredFlags = 0;

		switch (memoryUsage) {
		case VulkanMemoryUsage::GPU_ONLY:
			preferredFlags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			break;
		case VulkanMemoryUsage::CPU_ONLY:
			requiredFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
			requiredFlags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
			break;
		case VulkanMemoryUsage::CPU_TO_GPU:
			requiredFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
			preferredFlags |= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
			break;
		case VulkanMemoryUsage::GPU_TO_CPU:
			requiredFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT;
			preferredFlags |= VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT;
			break;
		default:
			break;
		}

		uint memoryTypeIndex = UINT32_MAX;
		uint maxBitsMissing = UINT32_MAX;

		const VkPhysicalDeviceMemoryProperties& memoryProperties = physicalDevice.GetMemoryProperties();
		uint memoryTypeCount = memoryProperties.memoryTypeCount;

		for (uint i = 0; i < memoryTypeCount; i++) {
			if ((memoryTypeBits & (1 << i)) != 0) {
				uint propertyFlags = memoryProperties.memoryTypes[i].propertyFlags;
				if ((requiredFlags & ~propertyFlags) == 0) {
					uint bitsMissing = Math::countBitsSet(preferredFlags & ~propertyFlags);
					if (bitsMissing < maxBitsMissing) {
						memoryTypeIndex = i;
						if (bitsMissing == 0) {
							return memoryTypeIndex;
						}
						maxBitsMissing = bitsMissing;
					}
				}
			}
		}
		if (memoryTypeIndex == UINT32_MAX) {
			return -1;
		}
		return memoryTypeIndex;
	}

}
