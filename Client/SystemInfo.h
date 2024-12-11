/************************************************************************
 * Filename:    SystemInfo.h
 * Description: 系统信息类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once
#include <sstream>
#include <string>

class SystemInfo
{
public:
	std::string HostName;
	std::string IpAddress;
	std::string ProcessorName;
	std::string ProcessorArchitecture;
	std::string ProcessorCores;
	std::string RamSize;
	std::string DiskSize;

	/// <summary>
	/// 获取完整的字符串输出
	/// </summary>
	/// <returns>字符串输出</returns>
	std::string GetFullOutput() const;
};
