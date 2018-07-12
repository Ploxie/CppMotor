#pragma once
#include "stdafx.h"
#include "VulkanShaderStage.h"
#include <vector>


namespace Vulkan
{
	struct VertexInputInfo
	{
		uint vertexBindingDescriptionCount;
		uint vertexAttributeDescriptionCount;
		VkVertexInputBindingDescription* pVertexBindingDescriptions;
		VkVertexInputAttributeDescription* pVertexAttributeDescriptions;
	};

	struct InputAssemblyState
	{
		VkPrimitiveTopology topology;
		bool primitiveRestartEnable;
	};

	typedef VkViewport Viewport;
	typedef VkRect2D Rect2D;

	struct ViewportState
	{
		uint viewportCount;
		Viewport*	pViewports;
		uint scissorCount;
		Rect2D* pScissors;
	};

	struct RasterizationStateInfo
	{
		bool depthClampEnable;
		bool rasterizerDiscardEnable;
		VkPolygonMode polygonMode;
		VkCullModeFlags cullMode;
		VkFrontFace frontFace;
		bool depthBiasEnable;
		float lineWidth;
	};

	struct MultisampleState
	{
		VkSampleCountFlagBits rasterizationSamples;
		bool sampleShadingEnable;
	};

	typedef VkPipelineColorBlendAttachmentState ColorBlendAttachmentState;

	struct ColorBlendState
	{
		bool logicOpEnable;
		VkLogicOp logicOp;
		uint attachmentCount;
		float blendConstants[4];
	};

	struct LayoutInfo
	{
		uint setLayoutCount;
		uint pushConstantRangeCount;
	};

	struct PipelineProperties
	{
		VertexInputInfo vertexInputInfo;
		InputAssemblyState inputAssemblyState;
		ViewportState viewportState;
		RasterizationStateInfo rasterizationStateInfo;
		MultisampleState multisampleState;
		ColorBlendAttachmentState colorBlendAttachmentState;
		ColorBlendState colorBlendState;
		LayoutInfo layoutInfo;
		std::vector<ShaderStage> shaderStages;
	};
}