#include "Logging.h"
#if defined(_WIN32)
#include <windows.h>
#endif

#include <iostream>



namespace Logging
{

	void showError(const std::string& message)
	{

#if defined(_WIN32)
		MessageBox(0, message.c_str(), 0, MB_OK | MB_ICONERROR);

#endif

		std::cerr << message << std::endl;

	}

}