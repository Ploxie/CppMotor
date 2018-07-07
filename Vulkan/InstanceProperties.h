#pragma once
#include "ApplicationInfo.h"
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