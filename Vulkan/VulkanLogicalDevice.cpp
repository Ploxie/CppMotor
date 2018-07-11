#pragma once
#include "stdafx.h"
#include "VulkanLogicalDevice.h"
#include "VulkanUtil.h"
#include <iostream>
#include "VulkanPhysicalDevice.h"

namespace Vulkan
{
	
	LogicalDevice::LogicalDevice(const VkDevice& internal, const PhysicalDevice& physicalDevice, const QueueFamilyIndices& queueFamilyIndices) : internal(internal), physicalDevice(physicalDevice), queueFamilyIndices(queueFamilyIndices)
	{
		VkQueue graphicsQueue;
		VkQueue computeQueue;
		VkQueue transferQueue;
		
		vkGetDeviceQueue(internal, queueFamilyIndices.graphics, 0, &graphicsQueue);
		vkGetDeviceQueue(internal, queueFamilyIndices.compute, 0, &computeQueue);
		vkGetDeviceQueue(internal, queueFamilyIndices.transfer, 0, &transferQueue);

		this->graphicsQueue = Queue(graphicsQueue);
		this->computeQueue = Queue(computeQueue);
		this->transferQueue = Queue(transferQueue);
	}

	const Swapchain LogicalDevice::CreateSwapchain(const SwapchainProperties& properties, const Swapchain* oldSwapchain) const
	{
		VkSwapchainCreateInfoKHR createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		createInfo.surface = properties.surface;
		
		createInfo.minImageCount = properties.imageCount;
		createInfo.imageFormat = properties.surfaceFormat.format;
		createInfo.imageColorSpace = properties.surfaceFormat.colorSpace;
		createInfo.imageExtent = properties.extent;
		createInfo.imageArrayLayers = 1;
		createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

		const int presentQueueIndex = physicalDevice.GetPresentQueueFamilyIndex(properties.surface);
		
		if (queueFamilyIndices.graphics == -1)
		{
			std::cerr << "Device does not have Swapchain support!" << std::endl;
		}

		uint queueFamilyIndices[] =
		{
			static_cast<uint>(this->queueFamilyIndices.graphics),
			static_cast<uint>(presentQueueIndex)
		};

		if (this->queueFamilyIndices.graphics != presentQueueIndex) {
			createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			createInfo.queueFamilyIndexCount = 2;
			createInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else {
			createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		}

		createInfo.preTransform = properties.transformFlags;
		createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		createInfo.presentMode = properties.presentMode;
		createInfo.clipped = VK_TRUE;
		createInfo.oldSwapchain = oldSwapchain != nullptr ? oldSwapchain->GetHandle() : VK_NULL_HANDLE;

		VkSwapchainKHR swapchain = VK_NULL_HANDLE;

		VkResult result = vkCreateSwapchainKHR(internal, &createInfo, nullptr, &swapchain);
		if (result != VK_SUCCESS) {
			std::cerr << "Failed to create swapchain: " << translateVulkanResult(result) << std::endl;
		}

		SwapchainProperties swapchainProperties = properties;

		vkGetSwapchainImagesKHR(internal, swapchain, &swapchainProperties.imageCount, nullptr);
		std::vector<VkImage> swapchainImages(swapchainProperties.imageCount);
		vkGetSwapchainImagesKHR(internal, swapchain, &swapchainProperties.imageCount, swapchainImages.data());

		return Swapchain(swapchain, swapchainProperties, swapchainImages);
	}

		
	void LogicalDevice::DestroySwapchain(const Swapchain& swapchain)
	{
		vkDestroySwapchainKHR(internal, swapchain.GetHandle(), 0);
	}

	void LogicalDevice::Destroy()
	{
		vkDestroyDevice(internal, 0);
	}

}