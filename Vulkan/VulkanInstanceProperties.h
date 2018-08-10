#pragma once
#include "stdafx.h"
#include "VulkanApplicationInfo.h"
#include <vector>

namespace Vulkan
{

	struct InstanceProperties
	{
		ApplicationInfo applicationInfo;
		std::vector<const char*> extensions;		
		std::vector<const char*> layers;
	};

}