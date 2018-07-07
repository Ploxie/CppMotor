#pragma once
#include "Window.h"
#include <BasicTypes.h>

struct GLFWwindow;

namespace Engine
{
	class GLFWWindow : public Window
	{
	public:
		GLFWWindow();
		GLFWWindow(const uint& width, const uint& height, const char* title, const WindowMode& windowMode);

		void Create() override;
		
		bool IsActive() override;

		void Update() override;

		void Destroy() override;

		void SetDimensions(const uint& width, const uint& height) override;

		void SetTitle(const char* title) override;

		void SetWindowMode(const WindowMode& windowMode) override;

	private:
		GLFWwindow * window;
	};
};