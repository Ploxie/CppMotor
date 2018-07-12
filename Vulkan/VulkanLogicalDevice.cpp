#pragma once
#include "stdafx.h"
#include "VulkanLogicalDevice.h"
#include "VulkanUtil.h"
#include <iostream>
#include "VulkanPhysicalDevice.h"

namespace Vulkan
{
	
	LogicalDevice::LogicalDevice(const VkDevice& internal, const PhysicalDevice& physicalDevice, const QueueFamilyIndices& queueFamilyIndices)
		: internal(internal), physicalDevice(physicalDevice), queueFamilyIndices(queueFamilyIndices)
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

	const Vulkan::Pipeline LogicalDevice::CreatePipeline(const PipelineProperties& properties)
	{
		
		std::vector<VkPipelineShaderStageCreateInfo> shaderStages(properties.shaderStages.size());
		for (uint i = 0; i < shaderStages.size(); i++)
		{
			shaderStages[i] = properties.shaderStages[i].GetStageInfo();
		}

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.vertexBindingDescriptionCount = properties.vertexInputInfo.vertexBindingDescriptionCount;
		vertexInputInfo.pVertexBindingDescriptions = properties.vertexInputInfo.pVertexBindingDescriptions;
		vertexInputInfo.vertexAttributeDescriptionCount = properties.vertexInputInfo.vertexAttributeDescriptionCount;
		vertexInputInfo.pVertexAttributeDescriptions = properties.vertexInputInfo.pVertexAttributeDescriptions;

		VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = properties.inputAssemblyState.topology;
		inputAssembly.primitiveRestartEnable = properties.inputAssemblyState.primitiveRestartEnable;
		
		VkPipelineViewportStateCreateInfo viewportState = {};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = properties.viewportState.viewportCount;
		viewportState.pViewports = properties.viewportState.pViewports;
		viewportState.scissorCount = properties.viewportState.scissorCount;
		viewportState.pScissors = properties.viewportState.pScissors;

		VkPipelineRasterizationStateCreateInfo rasterizer = {};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = properties.rasterizationStateInfo.depthClampEnable;
		rasterizer.rasterizerDiscardEnable = properties.rasterizationStateInfo.rasterizerDiscardEnable;
		rasterizer.polygonMode = properties.rasterizationStateInfo.polygonMode;
		rasterizer.cullMode = properties.rasterizationStateInfo.cullMode;
		rasterizer.frontFace = properties.rasterizationStateInfo.frontFace;
		rasterizer.depthBiasEnable = properties.rasterizationStateInfo.depthBiasEnable;
		rasterizer.lineWidth = properties.rasterizationStateInfo.lineWidth;

		VkPipelineMultisampleStateCreateInfo multisampling = {};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.rasterizationSamples = properties.multisampleState.rasterizationSamples;
		multisampling.sampleShadingEnable = properties.multisampleState.sampleShadingEnable;
		
		VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
		colorBlendAttachment.blendEnable = properties.colorBlendAttachmentState.blendEnable;
		colorBlendAttachment.srcColorBlendFactor = properties.colorBlendAttachmentState.srcColorBlendFactor;
		colorBlendAttachment.dstColorBlendFactor = properties.colorBlendAttachmentState.dstColorBlendFactor;
		colorBlendAttachment.colorBlendOp = properties.colorBlendAttachmentState.colorBlendOp;
		colorBlendAttachment.srcAlphaBlendFactor = properties.colorBlendAttachmentState.srcAlphaBlendFactor;
		colorBlendAttachment.dstAlphaBlendFactor = properties.colorBlendAttachmentState.dstAlphaBlendFactor;
		colorBlendAttachment.alphaBlendOp = properties.colorBlendAttachmentState.alphaBlendOp;
		colorBlendAttachment.colorWriteMask = properties.colorBlendAttachmentState.colorWriteMask;

		VkPipelineColorBlendStateCreateInfo colorBlending = {};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = properties.colorBlendState.logicOpEnable;
		colorBlending.logicOp = properties.colorBlendState.logicOp;
		colorBlending.attachmentCount = properties.colorBlendState.attachmentCount;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = properties.colorBlendState.blendConstants[0];
		colorBlending.blendConstants[1] = properties.colorBlendState.blendConstants[1];
		colorBlending.blendConstants[2] = properties.colorBlendState.blendConstants[2];
		colorBlending.blendConstants[3] = properties.colorBlendState.blendConstants[3];

		VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = properties.layoutInfo.setLayoutCount;
		pipelineLayoutInfo.pushConstantRangeCount = properties.layoutInfo.pushConstantRangeCount;
		
		VkPipelineLayout pipelineLayout;

		if (vkCreatePipelineLayout(internal, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}

		VkGraphicsPipelineCreateInfo pipelineInfo = {};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages.data();
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.layout = pipelineLayout;
		//pipelineInfo.renderPass = renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

		Pipeline pipeline;

		if (vkCreateGraphicsPipelines(internal, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline) != VK_SUCCESS) {
			throw std::runtime_error("failed to create graphics pipeline!");
		}

		for (uint i = 0; i < properties.shaderStages.size(); i++)
		{
			DestroyShaderStage(properties.shaderStages[i]);
		}

		return Pipeline();
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

	const ShaderStage LogicalDevice::CreateShaderStage(const std::vector<char>& sourceCode, const ShaderStageType& shaderType) const
	{
		VkShaderModuleCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = sourceCode.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(sourceCode.data());

		VkShaderModule shaderModule;

		VkResult result = vkCreateShaderModule(internal, &createInfo, nullptr, &shaderModule);
		if (result != VK_SUCCESS) {
			std::cerr << "Failed to create Shader Module: " << translateVulkanResult(result) << std::endl;
		}

		return ShaderStage(shaderModule, shaderType);
	}
		
	void LogicalDevice::DestroyShaderStage(const ShaderStage& module)
	{
		vkDestroyShaderModule(internal, module.GetModule(), 0);
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