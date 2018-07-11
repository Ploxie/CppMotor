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

		std::vector<Image> images;
		std::vector<ImageView> imageViews;
		for (uint i = 0; i < swapchainProperties.imageCount; i++)
		{
			Image image = Image(swapchainImages[i], VK_IMAGE_TYPE_2D, VK_IMAGE_LAYOUT_UNDEFINED, swapchainProperties.extent.width, swapchainProperties.extent.height, 1);
			ImageView imageView = CreateImageView(image, properties.surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT);

			images.push_back(image);
			imageViews.push_back(imageView);
		}

		return Swapchain(swapchain, swapchainProperties, images, imageViews);
	}

	const Image LogicalDevice::CreateImage(const ImageType& imageType, const ImageFormat& format, const uint& mipLevels, const uint& arrayLevels, const uint& width, const uint& height, const uint& depth, const ImageUsageFlags& usageFlags) const
	{
		ImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED;

		VkImageCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		createInfo.imageType = imageType;
		createInfo.extent.width = width;
		createInfo.extent.height = height;
		createInfo.extent.depth = depth;
		createInfo.mipLevels = mipLevels;
		createInfo.arrayLayers = arrayLevels;
		createInfo.format = format;
		createInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
		createInfo.initialLayout = layout;
		createInfo.usage = usageFlags;
		createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
		createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		VkImage image;
		VkResult result = vkCreateImage(internal, &createInfo, nullptr, &image);
		if (result != VK_SUCCESS) {
			std::cerr << "Failed to create image: " << translateVulkanResult(result) << std::endl;
		}

		return Image(image, imageType, layout, width, height, depth);
	}

	const ImageView LogicalDevice::CreateImageView(const Image& image, const ImageFormat& format, const ImageAspectFlags& aspectFlags) const
	{

		VkImageViewCreateInfo createInfo = {};
		
		createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		createInfo.image = image.GetHandle();
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = format;

		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		createInfo.subresourceRange.aspectMask = aspectFlags;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		ImageView imageView;

		VkResult result = vkCreateImageView(internal, &createInfo, nullptr, &imageView);
		if (result != VK_SUCCESS) {
			std::cerr << "Failed to create Image view: " << translateVulkanResult(result) << std::endl;
		}

		return imageView;
	}
		
	void LogicalDevice::DestroySwapchain(const Swapchain& swapchain)
	{

		for (uint i = 0; i < swapchain.GetImageViews().size(); i++)
		{
			vkDestroyImageView(internal, swapchain.GetImageViews()[i], 0);
		}
		
		vkDestroySwapchainKHR(internal, swapchain.GetHandle(), 0);
		
	}

	void LogicalDevice::Destroy()
	{
		vkDestroyDevice(internal, 0);
	}

}