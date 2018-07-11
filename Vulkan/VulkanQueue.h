#pragma once
#include "stdafx.h"

namespace Vulkan
{
	class Queue
	{
	public:
		inline Queue();
		Queue(const VkQueue& internal);

	private:
		VkQueue internal;
	};

	inline Queue::Queue() : internal(0)
	{

	}
}