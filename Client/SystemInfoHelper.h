/************************************************************************
 * Filename:    SystemInfoHelper.h
 * Description: 系统信息帮助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include "SystemInfo.h"

#ifdef _WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <ws2tcpip.h>
	#include <windows.h>
	#include <wbemidl.h>
	#include "WindowsHelper.h"
	#pragma comment(lib, "ws2_32.lib")
	#pragma comment(lib, "wbemuuid.lib")
#else
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <sys/statvfs.h>
	#include <sys/utsname.h>
#endif

#ifdef __APPLE__
	#include <sys/sysctl.h> // 用于 macOS 获取系统信息
#endif

class SystemInfoHelper
{
public:
	/// <summary>
	/// 获取当前的系统信息
	/// </summary>
	/// <returns>包含当前系统信息的系统信息类</returns>
	static SystemInfo GetCurrentSystemInfo();

	/// <summary>
	/// 获取主机名
	/// </summary>
	static std::string GetHostName();

	/// <summary>
	/// 获取 IP 地址
	/// </summary>
	static std::string GetIpAddress();

    /// <summary>
	/// 获取处理器名称（型号）
    /// </summary>
    static std::string GetProcessorName();

	/// <summary>
	/// 获取处理器架构
	/// </summary>
	static std::string GetProcessorArchitecture();

    /// <summary>
	/// 获取处理器核心数
    /// </summary>
    static std::string GetProcessorCores();

    /// <summary>
	/// 获取内存信息 (MB)
    /// </summary>
    static std::string GetRamInfo();

    /// <summary>
	/// 获取磁盘信息 (GB)
    /// </summary>
    static std::string GetDiskSize();
};

