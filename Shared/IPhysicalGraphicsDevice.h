#pragma once
#include <string>
#include <vector>
#include "BasicTypes.h"

class ILogicalGraphicsDevice;

class IPhysicalGraphicsDevice
{
public:

	virtual const std::string GetName() const = 0;
	virtual const uint GetDriverVersion() const = 0;
	virtual const uint GetVendorId() const = 0;
	virtual const uint GetDeviceId() const = 0;

	virtual const ILogicalGraphicsDevice CreateLogicalDevice(const std::vector<std::string>& extensions, const uint graphicsQueueCount, const uint computeQueueCount) const = 0;
};
