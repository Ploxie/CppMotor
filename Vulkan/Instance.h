#pragma once
#include <vulkan/vulkan.h>

namespace Vulkan
{
	class Instance
	{
	public:

		const Instance Create();

		void Destroy();

	private:
		VkInstance internal;
	};
}