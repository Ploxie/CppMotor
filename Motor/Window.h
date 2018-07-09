#pragma once
#include "Display.h"
#include <BasicTypes.h>
#include <string>



namespace Engine
{
	enum WindowMode
	{
		FULL_SCREEN,
		WINDOWED,
		BORDERLESS
	};

	class Window : public Display
	{
	public:	
	
		virtual void SetDimensions(const uint& width, const uint& height) = 0;

		virtual void SetTitle(const char* title) = 0;

		virtual void SetWindowMode(const WindowMode& windowMode) = 0;

		virtual const WindowHandle GetHandle() const = 0;

	protected:
		const char* title;
		int width;
		int height;

		WindowMode windowMode;
	};
}