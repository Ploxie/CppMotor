#pragma once
#include "stdafx.h"
#include "VulkanSwapchainProperties.h"
#include "VulkanImage.h"
#include "VulkanImageView.h"

namespace Vulkan
{

	class Swapchain
	{
	public:
		inline Swapchain(const VkSwapchainKHR& swapchain, const SwapchainProperties& properties, const std::vector<Image>& images, const std::vector<ImageView>& imageViews);

		inline const VkSwapchainKHR& GetHandle() const;
		inline const SwapchainProperties& GetProperties() const;
		inline const std::vector<Image>& GetImages() const;
		inline const std::vector<ImageView>& GetImageViews() const;

	private:
		const VkSwapchainKHR internal;
		const SwapchainProperties properties;
		const std::vector<Image> images;
		const std::vector<ImageView> imageViews;
	};

	inline Swapchain::Swapchain(const VkSwapchainKHR& swapchain, const SwapchainProperties& properties, const std::vector<Image>& images, const std::vector<ImageView>& imageViews) : internal(swapchain), properties(properties), images(images), imageViews(imageViews)
	{

	}

	inline const VkSwapchainKHR& Swapchain::GetHandle() const
	{
		return internal;
	}

	inline const SwapchainProperties& Swapchain::GetProperties() const
	{
		return properties;
	}

	inline const std::vector<Image>& Swapchain::GetImages() const
	{
		return images;
	}

	inline const std::vector<ImageView>& Swapchain::GetImageViews() const
	{
		return imageViews;
	}

}