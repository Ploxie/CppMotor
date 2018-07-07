#pragma once
#include <BasicTypes.h>
#include <vulkan/vulkan.h>

namespace Vulkan
{
	struct Version
	{
		uint major;
		uint minor;
		uint patch;

		const uint GetVersion() const { return VK_MAKE_VERSION(major, minor, patch); }
	};
}
