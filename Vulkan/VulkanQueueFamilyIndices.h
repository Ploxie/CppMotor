#pragma once

namespace Vulkan
{
	struct QueueFamilyIndices
	{
		int graphics = -1;
		int compute = -1;
		int transfer = -1;
		int present = -1;
	};
}