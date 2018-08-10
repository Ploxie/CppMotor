#pragma once
#include "stdafx.h"

namespace Vulkan
{
	struct MemoryAllocation
	{
		uint memoryTypeflags;
		VkDeviceMemory deviceMemory;
		uint64 offset;
		uint64 size;
	};
}
