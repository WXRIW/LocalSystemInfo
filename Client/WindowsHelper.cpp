/************************************************************************
 * Filename:    WindowsHelper.cpp
 * Description: Windows ������ʵ��
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "WindowsHelper.h"

#ifdef _WIN32

std::string WindowsHelper::WcharToString(const wchar_t* wstr)
{
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    std::vector<char> buffer(size_needed);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buffer.data(), size_needed, nullptr, nullptr);
    return std::string(buffer.data());
}

#endif
