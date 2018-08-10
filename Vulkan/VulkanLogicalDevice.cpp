#include "stdafx.h"
#include "VulkanLogicalDevice.h"
#include "VulkanUtil.h"
#include "VulkanPhysicalDevice.h"

namespace Vulkan
{
	
	LogicalDevice::LogicalDevice(const VkDevice& internal, const PhysicalDevice& physicalDevice, const QueuesInfo& queuesInfo) : internal(internal), physicalDevice(physicalDevice), queuesInfo(queuesInfo)
	{
	}

	const VkRenderPass LogicalDevice::CreateRenderPass() const
	{
		VkAttachmentDescription colorAttachment = {};
		colorAttachment.format = VK_FORMAT_B8G8R8A8_SNORM; // CHANGE
		colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
		colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
		colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;		
		colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
		colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

		VkAttachmentReference colorAttachmentRef = {};
		colorAttachmentRef.attachment = 0;
		colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

		VkSubpassDescription subpass = {};
		subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
		subpass.colorAttachmentCount = 1;
		subpass.pColorAttachments = &colorAttachmentRef;

		VkRenderPassCreateInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		renderPassInfo.attachmentCount = 1;
		renderPassInfo.pAttachments = &colorAttachment;
		renderPassInfo.subpassCount = 1;
		renderPassInfo.pSubpasses = &subpass;

		VkRenderPass renderPass;
		VkResult result = vkCreateRenderPass(internal, &renderPassInfo, 0, &renderPass);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to create render pass: " + VulkanUtil::translateVulkanResult(result));
		}

		return renderPass;
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
		
		const uint graphicsQueueFamilyIndex = physicalDevice.GetQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);

		if (queuesInfo.graphicsIndex == -1)
		{
			Logging::showError("Device does not have swapchain support!");
		}

		uint queueFamilyIndices[] =
		{
			static_cast<uint>(this->queuesInfo.graphicsIndex),
			static_cast<uint>(presentQueueIndex)
		};

		if (queuesInfo.graphicsIndex != presentQueueIndex) {
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
			Logging::showError("Failed to create swapchain: " + VulkanUtil::translateVulkanResult(result));
		}

		SwapchainProperties swapchainProperties = properties;

		vkGetSwapchainImagesKHR(internal, swapchain, &swapchainProperties.imageCount, nullptr);
		std::vector<VkImage> swapchainImages(swapchainProperties.imageCount);
		vkGetSwapchainImagesKHR(internal, swapchain, &swapchainProperties.imageCount, swapchainImages.data());

		std::vector<Image> images;
		std::vector<VkImageView> imageViews;
		for (uint i = 0; i < swapchainProperties.imageCount; i++)
		{
			Image image = Image(swapchainImages[i], VK_IMAGE_TYPE_2D, VK_IMAGE_LAYOUT_UNDEFINED, swapchainProperties.extent.width, swapchainProperties.extent.height, 1);
			VkImageView imageView = CreateImageView(image, properties.surfaceFormat.format, VK_IMAGE_ASPECT_COLOR_BIT);

			images.push_back(image);
			imageViews.push_back(imageView);
		}

		return Swapchain(swapchain, swapchainProperties, images, imageViews);
	}

	const VkFramebuffer LogicalDevice::CreateFrameBuffer(const VkRenderPass& renderPass, const VkExtent2D& dimensions, const std::vector<VkImageView>& attachments) const
	{
		VkFramebufferCreateInfo frameBufferInfo = {};
		frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		frameBufferInfo.renderPass = renderPass;
		frameBufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
		frameBufferInfo.pAttachments = attachments.data();
		frameBufferInfo.width = dimensions.width;
		frameBufferInfo.height = dimensions.height;
		frameBufferInfo.layers = 1;

		VkFramebuffer frameBuffer;
		VkResult result = vkCreateFramebuffer(internal, &frameBufferInfo, 0, &frameBuffer);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to create Frame Buffer: " + VulkanUtil::translateVulkanResult(result));
		}

		return frameBuffer;
	}

	const VkPipeline LogicalDevice::CreatePipeline(const VkRenderPass& renderPass, const GraphicsPipelineProperties& properties)
	{
		
		/*std::vector<VkPipelineShaderStageCreateInfo> shaderStages(properties.shaderStages.size());
		for (uint i = 0; i < shaderStages.size(); i++)
		{
			shaderStages[i] = properties.shaderStages[i].GetStageInfo();
		}*/

		VkPipelineInputAssemblyStateCreateInfo inputAssemblyStateInfo = {};
		inputAssemblyStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssemblyStateInfo.flags = 0;
		inputAssemblyStateInfo.topology = VulkanUtil::getTopology(properties.topology);
		inputAssemblyStateInfo.primitiveRestartEnable = false;

		uint vertexInputBindingDescriptionSize = static_cast<uint>(properties.vertexInputInfo.bindingDescriptions.size());
		std::vector<VkVertexInputBindingDescription> bindingDescriptions(vertexInputBindingDescriptionSize);
		for (uint i = 0; i < vertexInputBindingDescriptionSize; i++)
		{
			const BindingDescription& bindingDescription = properties.vertexInputInfo.bindingDescriptions[i];
			VkVertexInputBindingDescription vertexInputBindingDescription = {};
			vertexInputBindingDescription.binding = bindingDescription.binding;
			vertexInputBindingDescription.stride = bindingDescription.stride;
			vertexInputBindingDescription.inputRate = VulkanUtil::getVertexInputRate(bindingDescription.inputRate);
			bindingDescriptions[i] = vertexInputBindingDescription;
		}

		uint vertexInputAttributeDescriptionSize = static_cast<uint>(properties.vertexInputInfo.attributeDescriptions.size());
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions(vertexInputAttributeDescriptionSize);
		for (uint i = 0; i < vertexInputAttributeDescriptionSize; i++)
		{
			const AttributeDescription& attributeDescription = properties.vertexInputInfo.attributeDescriptions[i];
			VkVertexInputAttributeDescription vertexInputAttributeDescription = {};
			vertexInputAttributeDescription.binding = attributeDescription.binding;
			vertexInputAttributeDescription.location = attributeDescription.location;
			vertexInputAttributeDescription.format = VulkanUtil::getColorFormat(attributeDescription.format);
			vertexInputAttributeDescription.offset = attributeDescription.offset;
			attributeDescriptions[i] = vertexInputAttributeDescription;
		}

		VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
		vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		vertexInputInfo.flags = 0;
		vertexInputInfo.vertexBindingDescriptionCount = vertexInputBindingDescriptionSize;
		vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();
		vertexInputInfo.vertexAttributeDescriptionCount = vertexInputAttributeDescriptionSize;
		vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
		
		VkPipelineViewportStateCreateInfo viewportStateInfo = {};
		viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportStateInfo.viewportCount = 1;
		viewportStateInfo.pViewports = 0;
		viewportStateInfo.scissorCount = 1;
		viewportStateInfo.pScissors = 0;

		VkPipelineRasterizationStateCreateInfo rasterizationStateInfo = {};
		rasterizationStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizationStateInfo.depthClampEnable = false;
		rasterizationStateInfo.rasterizerDiscardEnable = false;
		rasterizationStateInfo.polygonMode = VulkanUtil::getPolygonDrawMode(properties.polygonDrawMode);
		rasterizationStateInfo.cullMode = VulkanUtil::getCullMode(properties.cullFaceSide);
		rasterizationStateInfo.frontFace = VulkanUtil::getFrontFaceVertexWinding(properties.frontFaceVertexWinding);
		rasterizationStateInfo.depthBiasEnable = false;
		rasterizationStateInfo.lineWidth = properties.lineWidth;

		uint attachmentColorBlendPropertiesSize = static_cast<uint>(properties.attachmentColorBlendProperties.size());
		std::vector<VkPipelineColorBlendAttachmentState> colorWriteMasks(attachmentColorBlendPropertiesSize);
		for (uint i = 0; i < attachmentColorBlendPropertiesSize; i++)
		{
			const AttachmentColorBlendProperties& attachmentColorBlendProperties = properties.attachmentColorBlendProperties[i];
			uint colorMask = 0;
			if (attachmentColorBlendProperties.colorWriteMaskR)
			{
				colorMask |= VK_COLOR_COMPONENT_R_BIT;
			}
			if (attachmentColorBlendProperties.colorWriteMaskG)
			{
				colorMask |= VK_COLOR_COMPONENT_G_BIT;
			}
			if (attachmentColorBlendProperties.colorWriteMaskB)
			{
				colorMask |= VK_COLOR_COMPONENT_B_BIT;
			}
			if (attachmentColorBlendProperties.colorWriteMaskA)
			{
				colorMask |= VK_COLOR_COMPONENT_A_BIT;
			}

			VkPipelineColorBlendAttachmentState colorWriteMask = { };
			colorWriteMask.blendEnable = attachmentColorBlendProperties.blendEnable;
			colorWriteMask.srcColorBlendFactor = VulkanUtil::getBlendFactor(attachmentColorBlendProperties.srcColorBlendFactor);
			colorWriteMask.dstColorBlendFactor = VulkanUtil::getBlendFactor(attachmentColorBlendProperties.dstColorBlendFactor);
			colorWriteMask.colorBlendOp = VulkanUtil::getBlendOp(attachmentColorBlendProperties.colorBlendOp);
			colorWriteMask.srcAlphaBlendFactor = VulkanUtil::getBlendFactor(attachmentColorBlendProperties.srcAlphaBlendFactor);
			colorWriteMask.dstAlphaBlendFactor = VulkanUtil::getBlendFactor(attachmentColorBlendProperties.dstAlphaBlendFactor);
			colorWriteMask.alphaBlendOp = VulkanUtil::getBlendOp(attachmentColorBlendProperties.alphaBlendOp);
			colorWriteMask.colorWriteMask = colorMask;

			colorWriteMasks[i] = (colorWriteMask);
		}

		VkPipelineColorBlendStateCreateInfo colorBlendStateInfo = {};
		colorBlendStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlendStateInfo.pNext = 0;
		colorBlendStateInfo.pAttachments = colorWriteMasks.data();
		colorBlendStateInfo.attachmentCount = attachmentColorBlendPropertiesSize;

		VkPipelineMultisampleStateCreateInfo multisampleStateInfo = {};
		multisampleStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampleStateInfo.pNext = 0;
		multisampleStateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		multisampleStateInfo.pSampleMask = 0;
		
		VkPipelineDepthStencilStateCreateInfo depthStencilStateInfo = { };
		depthStencilStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		depthStencilStateInfo.pNext = NULL;
		depthStencilStateInfo.depthTestEnable = properties.depthTestEnable;
		depthStencilStateInfo.depthWriteEnable = properties.depthWriteEnable;
		depthStencilStateInfo.depthCompareOp = VulkanUtil::getCompareOp(properties.depthCompareOp);
		depthStencilStateInfo.depthBoundsTestEnable = properties.depthBoundsTestEnable;
		depthStencilStateInfo.minDepthBounds = properties.minDepthBounds;
		depthStencilStateInfo.maxDepthBounds = properties.maxDepthBounds;

		std::vector<VkDynamicState> dynamicStates;
		if (properties.dynamicViewPort)
		{
			dynamicStates.push_back(VK_DYNAMIC_STATE_VIEWPORT);
		}
		if (properties.dynamicScissor) {
			dynamicStates.push_back(VK_DYNAMIC_STATE_SCISSOR);
		}
		if (properties.dynamicLineWidth) {
			dynamicStates.push_back(VK_DYNAMIC_STATE_LINE_WIDTH);
		}
		if (properties.dynamicDepthBias) {
			dynamicStates.push_back(VK_DYNAMIC_STATE_DEPTH_BIAS);
		}
		if (properties.dynamicBlendConstants) {
			dynamicStates.push_back(VK_DYNAMIC_STATE_BLEND_CONSTANTS);
		}
		if (properties.dynamicDepthBounds) {
			dynamicStates.push_back(VK_DYNAMIC_STATE_DEPTH_BOUNDS);
		}

		VkPipelineDynamicStateCreateInfo dynamicStateCreateInfo = {};
		dynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicStateCreateInfo.pNext = NULL;
		dynamicStateCreateInfo.flags = 0;
		dynamicStateCreateInfo.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicStateCreateInfo.pDynamicStates = dynamicStates.data();

		/*if (vkCreatePipelineLayout(internal, VK_NULL_HANDLE, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("failed to create pipeline layout!");
		}*/

		VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
		pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineCreateInfo.pNext = NULL;
		pipelineCreateInfo.layout = NULL; // TODO
		pipelineCreateInfo.renderPass = renderPass;
		pipelineCreateInfo.pVertexInputState = &vertexInputInfo;
		pipelineCreateInfo.pInputAssemblyState = &inputAssemblyStateInfo;
		pipelineCreateInfo.pRasterizationState = &rasterizationStateInfo;
		pipelineCreateInfo.pColorBlendState = &colorBlendStateInfo;
		pipelineCreateInfo.pMultisampleState = &multisampleStateInfo;
		pipelineCreateInfo.pViewportState = &viewportStateInfo;
		pipelineCreateInfo.pDepthStencilState = &depthStencilStateInfo;
		pipelineCreateInfo.pStages = NULL; // TODO
		pipelineCreateInfo.pDynamicState = &dynamicStateCreateInfo;

		VkPipeline pipeline;

		VkResult result = vkCreateGraphicsPipelines(internal, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &pipeline);
		if (result != VK_SUCCESS) {
			Logging::showError("Failed to create graphics pipeline: " + VulkanUtil::translateVulkanResult(result));			
		}

		/*for (uint i = 0; i < properties.shaderStages.size(); i++)
		{
			DestroyShaderStage(properties.shaderStages[i]);
		}*/

		return VkPipeline();
	}

	const Image LogicalDevice::CreateImage(const ImageType& imageType, const VkFormat& format, const uint& mipLevels, const uint& arrayLevels, const uint& width, const uint& height, const uint& depth, const ImageUsageFlags& usageFlags) const
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
			Logging::showError("Failed to create image: " + VulkanUtil::translateVulkanResult(result));
		}

		return Image(image, imageType, layout, width, height, depth);
	}

	const VkImageView LogicalDevice::CreateImageView(const Image& image, const VkFormat& format, const VkImageAspectFlags& aspectFlags) const
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

		VkImageView imageView;

		VkResult result = vkCreateImageView(internal, &createInfo, nullptr, &imageView);
		if (result != VK_SUCCESS) {
			Logging::showError("Failed to create Image view: " + VulkanUtil::translateVulkanResult(result));
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
			Logging::showError("Failed to create Shader Module: " + VulkanUtil::translateVulkanResult(result));
		}

		

		return ShaderStage(shaderModule, shaderType);
	}
		
	const Queue& LogicalDevice::GetDeviceQueue(const uint queueFamilyIndex, const uint queueIndex)
	{
		std::string key = queueFamilyIndex + ":" + queueIndex;
		auto iter = deviceQueues.find(key);
		if (iter == deviceQueues.end())
		{
			VkQueue internalQueue;
			vkGetDeviceQueue(internal, queueFamilyIndex, queueIndex, &internalQueue); 
			const Queue queue = Queue(internalQueue, *this);
			deviceQueues.emplace(key, queue);

			return queue;
		}

		return iter->second;
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