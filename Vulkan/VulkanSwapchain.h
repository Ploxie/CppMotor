#pragma once
#include "stdafx.h"
#include "VulkanSwapchainProperties.h"

namespace Vulkan
{
	//typedef VkSwapchainKHR Swapchain;

	class Swapchain
	{
	public:
		inline Swapchain(const VkSwapchainKHR& swapchain, const SwapchainProperties& properties, const std::vector<VkImage>& images);

		inline const VkSwapchainKHR& GetHandle() const;

	private:
		const VkSwapchainKHR internal;
		const SwapchainProperties properties;
		const std::vector<VkImage> images;
	};

	inline Swapchain::Swapchain(const VkSwapchainKHR& swapchain, const SwapchainProperties& properties, const std::vector<VkImage>& images) : internal(swapchain), properties(properties), images(images)
	{

	}

	inline const VkSwapchainKHR& Swapchain::GetHandle() const
	{
		return internal;
	}

}