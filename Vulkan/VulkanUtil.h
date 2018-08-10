#pragma once
#include "stdafx.h"
#include <string>
#include <RenderingUtil.h>

namespace Vulkan 
{
	namespace VulkanUtil
	{
		std::string translateVulkanResult(VkResult result);

		VkPrimitiveTopology getTopology(PrimitiveTopology topology);

		VkPolygonMode getPolygonDrawMode(PolygonDrawMode drawMode);

		VkFrontFace getFrontFaceVertexWinding(FrontFaceVertexWinding vertexWinding);

		VkCullModeFlagBits getCullMode(CullFaceSide cullFaceSide);

		VkCompareOp getCompareOp(CompareOp compareOp);

		VkBlendFactor getBlendFactor(BlendFactor blendFactor);

		VkBlendOp getBlendOp(BlendOp blendOp);

		VkVertexInputRate getVertexInputRate(VertexInputRate vertexInputRate);

		VkFormat getColorFormat(ColorFormat colorFormat);

	}
};