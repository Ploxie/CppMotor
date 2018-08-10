#pragma once
#include "stdafx.h"
#include <vector>
#include "VulkanPhysicalDevice.h"

namespace Engine
{
	class GLFWWindow;
}

namespace Vulkan
{
	struct InstanceProperties;

	class Instance
	{
	public:
		Instance(const InstanceProperties& properties);
		
		const VkSurfaceKHR CreateSurface(Engine::GLFWWindow& window) const;


		//TODO: Add Method to find device with certain properties
		const std::vector<PhysicalDevice> GetPhysicalDevices() const;

		void Destroy();
	private:
		VkInstance internal;
	};
}