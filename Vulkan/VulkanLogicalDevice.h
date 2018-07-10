#pragma once
#include "stdafx.h"
#include "VulkanQueue.h"
#include "VulkanQueueFamilyProperties.h"
#include "VulkanQueueFamilyIndices.h"
#include "VulkanSwapchain.h"

namespace Vulkan
{
	
	class LogicalDevice
	{
	public:
		LogicalDevice(const VkDevice& internal, const QueueFamilyIndices& queueFamilyIndices);


		//const Swapchain CreateSwapchain(const SurfaceFormat& format, const PresentMode& presentMode, const VkExtent2D& extent, const Swapchain* oldSwapchain = nullptr) const;

	/*	inline const Queue* GetGraphicsQueue() const;
		inline const Queue* GetComputeQueue() const;
		inline const Queue* GetTransferQueue() const;*/

		void Destroy();

	protected:
		const VkDevice internal;

		/*Queue graphicsQueue;
		Queue computeQueue;
		Queue transferQueue;*/

		QueueFamilyIndices queueFamilyIndices;		
	};

	/*inline const Queue* LogicalDevice::GetGraphicsQueue() const
	{
		return &graphicsQueue;
	}

	inline const Queue* LogicalDevice::GetComputeQueue() const
	{
		return &computeQueue;
	}

	inline const Queue* LogicalDevice::GetTransferQueue() const
	{
		return &transferQueue;
	}*/
}