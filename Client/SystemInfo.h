/************************************************************************
 * Filename:    SystemInfo.h
 * Description: 系统信息类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once
#include "SystemInfoHelper.h"

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

	/// <summary>
	/// 获取当前的系统信息
	/// </summary>
	/// <returns>包含当前系统信息的系统信息类</returns>
	static SystemInfo GetCurrentSystemInfo();
};
