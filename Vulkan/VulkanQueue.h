#pragma once
#include "stdafx.h"

namespace Vulkan
{
	class Queue
	{
	public:
		Queue(const VkQueue& internal);

	private:
		VkQueue internal;
	};
}