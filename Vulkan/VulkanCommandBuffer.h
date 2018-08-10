#pragma once
#include "stdafx.h"
#include <ICommandBuffer.h>
#include <Rectangle.h>


namespace Vulkan
{
	class CommandBuffer : public ICommandBuffer
	{
	public:
		CommandBuffer(const VkCommandBuffer& commandBuffer);

		void Begin() const override;
		void End() const override;
		//No reset because begin resets

		void BeginRenderPass() const override;
		void NextSubpass() const override;
		void EndRenderPass() const override;

		//wipe color, depth and stencil in one go
		//void clear

		void SetScissor(const uint scissorIndex, const Math::Rectangle& rectangle) const override;
		void SetViewport(const uint viewportIndex, const ViewportProperties& viewportProperties) const override;
		void SetLineWidth(float lineWidth) const override;

	private:
		void beginRenderPassInternal(const VkRenderPass& renderPass, const VkFramebuffer& framebuffer, const Math::Rectangle& renderArea,const bool inlineCommands) const;

		const VkCommandBuffer internal;
	};
}
