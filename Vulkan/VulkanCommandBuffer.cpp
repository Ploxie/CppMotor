#include "stdafx.h"
#include "VulkanCommandBuffer.h"
#include "VulkanUtil.h"

namespace Vulkan
{

	CommandBuffer::CommandBuffer(const VkCommandBuffer& commandBuffer) : internal(commandBuffer)
	{

	}

	void CommandBuffer::Begin() const
	{
		VkCommandBufferBeginInfo beginInfo = { };
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = 0;

		VkResult result = vkBeginCommandBuffer(internal, &beginInfo);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to begin commandBuffer: " + VulkanUtil::translateVulkanResult(result));
		}
	}

	void CommandBuffer::End() const
	{
		VkResult result = vkEndCommandBuffer(internal);
		if (result != VK_SUCCESS)
		{
			Logging::showError("Failed to end commandBuffer: " + VulkanUtil::translateVulkanResult(result));
		}
	}

	void CommandBuffer::BeginRenderPass() const
	{

	}

	void CommandBuffer::NextSubpass() const
	{

	}

	void CommandBuffer::EndRenderPass() const
	{
		vkCmdEndRenderPass(internal);
	}

	void CommandBuffer::SetScissor(const uint scissorIndex, const Math::Rectangle& rectangle) const
	{
		VkRect2D scissor = {};
		scissor.offset.x = rectangle.x;
		scissor.offset.y = rectangle.y;
		scissor.extent.width = rectangle.width;
		scissor.extent.height = rectangle.height;
		vkCmdSetScissor(internal, scissorIndex, 1, &scissor);
	}

	void CommandBuffer::SetViewport(const uint viewportIndex, const ViewportProperties& viewportProperties) const
	{
		VkViewport viewport = {};
		viewport.x = viewportProperties.x;
		viewport.y = viewportProperties.y;
		viewport.width = viewportProperties.width;
		viewport.height = viewportProperties.height;
		viewport.minDepth = viewportProperties.minDepth;
		viewport.maxDepth = viewportProperties.maxDepth;
		vkCmdSetViewport(internal, viewportIndex, 1, &viewport);
	}

	void CommandBuffer::SetLineWidth(float lineWidth) const
	{
		vkCmdSetLineWidth(internal, lineWidth);
	}

	void CommandBuffer::beginRenderPassInternal(const VkRenderPass& renderPass, const VkFramebuffer& framebuffer, const Math::Rectangle& renderArea, const bool inlineCommands) const
	{
		VkRenderPassBeginInfo renderPassBeginInfo = {};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_DEVICE_GROUP_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.pNext = nullptr;
		renderPassBeginInfo.renderPass = renderPass;
		renderPassBeginInfo.framebuffer = framebuffer;
		renderPassBeginInfo.renderArea.offset = { renderArea.x, renderArea.y };
		renderPassBeginInfo.renderArea.extent = { (uint)renderArea.width, (uint)renderArea.height };

		//use clear() instead
		renderPassBeginInfo.clearValueCount = 0;
		renderPassBeginInfo.pClearValues = nullptr;

		vkCmdBeginRenderPass(internal, &renderPassBeginInfo, inlineCommands ? VK_SUBPASS_CONTENTS_INLINE : VK_SUBPASS_CONTENTS_SECONDARY_COMMAND_BUFFERS);
	}

}