#pragma once

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include <Windows.h>
using WindowHandle = HWND;
#endif


using uint = unsigned int;