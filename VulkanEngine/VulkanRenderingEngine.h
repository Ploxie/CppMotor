#pragma once
#include <IRenderingEngine.h>


namespace VulkanEngine
{

	class VulkanRenderingEngine : public Engine::IRenderingEngine
	{
	public:

		const bool Init() const override;

		const std::vector<IPhysicalGraphicsDevice&> GetPhysicalGraphicsDevices() const override;

	};

}
