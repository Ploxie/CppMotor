#pragma once
#include "stdafx.h"
#include <unordered_map>
#include "VulkanQueue.h"
#include "VulkanQueueFamilyIndices.h"
#include "VulkanSwapchain.h"
#include "VulkanShaderStage.h"

#include "RenderingUtil.h"
#include "ILogicalGraphicsDevice.h"

namespace Vulkan
{
	class PhysicalDevice;

	struct QueuesInfo
	{
		int  graphicsIndex = -1;
		int  computeIndex = -1;
		int  transferIndex = -1;
		uint graphicsQueueCount = 0;
		uint computeQueueCount = 0;
		uint transferQueueCount = 0;
	};

	class LogicalDevice : public ILogicalGraphicsDevice
	{
	public:
		LogicalDevice(const VkDevice& internal, const PhysicalDevice& physicalDevice, const QueuesInfo& queuesInfo);
				
		const VkRenderPass CreateRenderPass() const;

		const VkPipeline CreatePipeline(const VkRenderPass& renderPass, const GraphicsPipelineProperties& properties);

		const Swapchain CreateSwapchain(const SwapchainProperties& properties, const Swapchain* oldSwapchain = nullptr) const;

		const VkFramebuffer CreateFrameBuffer(const VkRenderPass& renderPass, const VkExtent2D& dimensions, const std::vector<VkImageView>& attachments) const;
		
		const Image CreateImage(const ImageType& imageType, const VkFormat& format, const uint& mipLevels, const uint& arrayLevels, const uint& width, const uint& height, const uint& depth, const ImageUsageFlags& usageFlags) const;
		const VkImageView CreateImageView(const Image& image, const VkFormat& format, const VkImageAspectFlags& aspectFlags) const;

		const ShaderStage CreateShaderStage(const std::vector<char>& sourceCode, const ShaderStageType& shaderType) const;
		
		const Queue& GetDeviceQueue(const uint queueFamilyIndex, const uint queueIndex);

		void DestroyShaderStage(const ShaderStage& module);
		void DestroySwapchain(const Swapchain& swapchain);
		void Destroy();		

	protected:
		const VkDevice internal;
		const PhysicalDevice& physicalDevice;
		
		std::unordered_map<std::string, Queue> deviceQueues;

		QueuesInfo queuesInfo;
	};
}