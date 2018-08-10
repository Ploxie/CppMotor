#pragma once
#include "BasicTypes.h"
#include "Rectangle.h"

class ICommandBuffer
{
public:
	struct ViewportProperties {
		float    x;
		float    y;
		float    width;
		float    height;
		float    minDepth;
		float    maxDepth;
	};

	virtual void Begin() const = 0;
	virtual void End() const = 0;
	//virtual void reset() = 0;

	virtual void BeginRenderPass() const = 0;
	virtual void NextSubpass() const  = 0;
	virtual void EndRenderPass() const  = 0;

	virtual void SetScissor(const uint scissorIndex, const Math::Rectangle& rectangle) const  = 0;
	virtual void SetViewport(const uint viewportIndex, const ViewportProperties& viewportProperties) const  = 0;
	virtual void SetLineWidth(const float lineWidth) const  = 0;

	virtual void ExecuteCommands(ICommandBuffer* commandBuffers) const = 0;

	//virtual void setDepthBias() = 0;
	//virtual void setBlendConstants() = 0;
	//virtual void setStencilCompareMask() = 0;
	//virtual void setStencilWriteMask() = 0;
	//virtual void setStencilReference() = 0;

	//virtual void bindPipeline() = 0;
	//virtual void bindDescriptorSets() = 0;
	//virtual void bindIndexBuffer() = 0;
	//virtual void bindVertexBuffers() = 0;

	//virtual void pushConstants() = 0;

	//virtual void draw() = 0;
	//virtual void drawIndexed() = 0;
	//virtual void drawIndirect() = 0;
	//virtual void drawIndexedIndirect() = 0;

	// ---- COMPUTE ----
	//virtual void dispatch() = 0;
	//virtual void dispatchIndirect() = 0;

	//virtual void copyBuffer() = 0;
	//virtual void copyImage() = 0;
	//virtual void blitImage() = 0;
	//virtual void copyBufferToImage() = 0;
	//virtual void copyImageToBuffer() = 0;
	//virtual void updateBuffer() = 0;
	//virtual void fillBuffer() = 0;
	//virtual void clearColorImage() = 0;
	//virtual void clearDepthStencilImage() = 0;
	//virtual void clearAttachments() = 0;
	//virtual void resolveImage() = 0;
	//virtual void setEvent() = 0;
	//virtual void resetEvent() = 0;
	//virtual void waitEvents() = 0;
	//virtual void pipelineBarrier() = 0;
	//virtual void beginQuery() = 0;
	//virtual void endQuery() = 0;
	//virtual void resetQueryPool() = 0;
	//virtual void writeTimestamp() = 0;
	//virtual void copyQueryPoolResults() = 0;

};