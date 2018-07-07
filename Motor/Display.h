#pragma once

namespace Engine
{

	class Display
	{
	public:
		virtual void Create() = 0;

		virtual bool IsActive() = 0;

		virtual void Update() = 0;

		virtual void Destroy() = 0;
	};
}