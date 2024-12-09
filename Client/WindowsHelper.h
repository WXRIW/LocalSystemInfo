#pragma once

#ifdef _WIN32

#include <vector>
#include <string>
#include <windows.h>

class WindowsHelper
{
public:
	static std::string wchar_to_string(const wchar_t* wstr);
};

#endif
