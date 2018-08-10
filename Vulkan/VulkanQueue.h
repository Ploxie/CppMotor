#pragma once
#include "stdafx.h"

namespace Vulkan
{
	class LogicalDevice;

	class Queue
	{
	public:
		Queue(const VkQueue& queue, const LogicalDevice& logicalDevice);

	private:
		const VkQueue internal;
		const LogicalDevice& logicalDevice;
	};

	
}