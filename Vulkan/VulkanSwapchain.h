#pragma once
#include "stdafx.h"
#include "VulkanSwapchainProperties.h"
#include "VulkanImage.h"

namespace Vulkan
{
	//typedef VkSwapchainKHR Swapchain;

	class Swapchain
	{
	public:
		inline Swapchain(const VkSwapchainKHR& swapchain, const SwapchainProperties& properties, const std::vector<Image>& images);

		inline const VkSwapchainKHR& GetHandle() const;
		inline const SwapchainProperties& GetProperties() const;
		inline const std::vector<Image>& GetImages() const;

	private:
		const VkSwapchainKHR internal;
		const SwapchainProperties properties;
		const std::vector<Image> images;
	};

	inline Swapchain::Swapchain(const VkSwapchainKHR& swapchain, const SwapchainProperties& properties, const std::vector<Image>& images) : internal(swapchain), properties(properties), images(images)
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

}