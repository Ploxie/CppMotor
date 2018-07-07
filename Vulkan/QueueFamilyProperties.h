#pragma once
#include <vulkan/vulkan.h>
#include <BasicTypes.h>

namespace Vulkan
{
	class QueueFamilyProperties
	{
	public:
		inline QueueFamilyProperties();
		inline QueueFamilyProperties(const VkQueueFamilyProperties& properties);

		inline const uint32_t& GetQueueCount() const;

		inline const bool HasGraphicsCapabilities() const;
		inline const bool HasComputeCapabilities() const;
		inline const bool HasTransferCapabilties() const;
		inline const bool HasSparseBindingCapabilities() const;

	private:
		inline const bool HasBit(const uint& bit) const;

		VkQueueFamilyProperties internal;
	};

	inline QueueFamilyProperties::QueueFamilyProperties() : internal()
	{

	}

	inline QueueFamilyProperties::QueueFamilyProperties(const VkQueueFamilyProperties& properties) : internal(properties)
	{

	}

	inline const uint32_t& QueueFamilyProperties::GetQueueCount() const
	{
		return internal.queueCount;
	}

	inline const bool QueueFamilyProperties::HasBit(const uint& bit) const
	{
		return (internal.queueFlags & bit) != 0;
	}

	inline const bool QueueFamilyProperties::HasGraphicsCapabilities() const
	{
		return HasBit(VK_QUEUE_GRAPHICS_BIT);
	}
	inline const bool QueueFamilyProperties::HasComputeCapabilities() const
	{
		return HasBit(VK_QUEUE_COMPUTE_BIT);
	}
	inline const bool QueueFamilyProperties::HasTransferCapabilties() const
	{
		return HasBit(VK_QUEUE_TRANSFER_BIT);
	}
	inline const bool QueueFamilyProperties::HasSparseBindingCapabilities() const
	{
		return HasBit(VK_QUEUE_SPARSE_BINDING_BIT);
	}
}