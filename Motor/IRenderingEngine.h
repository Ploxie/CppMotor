#pragma once
#include <vector>
#include <IPhysicalGraphicsDevice.h>

namespace Engine
{
	
	class IRenderingEngine
	{
	public:
		
		virtual const bool init() const = 0;

		virtual const std::vector<IPhysicalGraphicsDevice&> GetPhysicalGraphicsDevices() const = 0;



	};

}
