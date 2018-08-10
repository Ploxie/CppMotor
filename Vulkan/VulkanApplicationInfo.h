#pragma once
#include "stdafx.h"
#include "VulkanVersion.h"

namespace Vulkan
{
	struct ApplicationInfo
	{
		const char* applicationName;
		const char* engineName;
		Version applicationVersion;
		Version engineVersion;
		Version apiVersion;
	};
}