#pragma once
#include <BasicTypes.h>
#include "Version.h"

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