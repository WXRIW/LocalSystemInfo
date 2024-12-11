/************************************************************************
 * Filename:    WindowsHelper.h
 * Description: Windows °ïÖúÀà¶¨Òå
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#ifdef _WIN32

#include <vector>
#include <string>
#include <windows.h>

class WindowsHelper
{
public:
	/// <summary>
	/// ½«¿í×Ö·û×ª»»Îª×Ö·û´®
	/// </summary>
	/// <param name="wstr">¿í×Ö·û</param>
	/// <returns>×Ö·û´®</returns>
	static std::string WcharToString(const wchar_t* wstr);
};

#endif
