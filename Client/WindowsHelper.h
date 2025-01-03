/************************************************************************
 * Filename:    WindowsHelper.h
 * Description: Windows �����ඨ��
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
	/// �����ַ�ת��Ϊ�ַ���
	/// </summary>
	/// <param name="wstr">���ַ�</param>
	/// <returns>�ַ���</returns>
	static std::string WcharToString(const wchar_t* wstr);
};

#endif
