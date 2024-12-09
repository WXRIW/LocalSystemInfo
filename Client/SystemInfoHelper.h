/************************************************************************
 * Filename:    SystemInfoHelper.h
 * Description: 系统信息帮助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once

#include <sstream>

#ifdef _WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#include <windows.h>
	#include <wbemidl.h>
	#include "WindowsHelper.h"
	#pragma comment(lib, "ws2_32.lib")
	#pragma comment(lib, "wbemuuid.lib")
#else
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>
	#include <netdb.h>
	#include <sys/types.h>
	#include <ifaddrs.h>
	#include <fstream>
	#include <sys/statvfs.h>
	#include <sys/types.h>
#endif

#ifdef __APPLE__
	#include <sys/sysctl.h> // 用于 macOS 获取系统信息
#endif

class SystemInfoHelper
{
public:
	static std::string GetHostName();

	static std::string GetIpAddress();

    static std::string GetProcessorName();

	static std::string GetProcessorArchitecture();

    static std::string GetProcessorCores();

    static std::string GetRamInfo();

    static std::string GetDiskSize();
};

