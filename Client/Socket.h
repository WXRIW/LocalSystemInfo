/************************************************************************
 * Filename:    Socket.h
 * Description: Socket 辅助类定义
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
	#define _WINSOCK_DEPRECATED_NO_WARNINGS
	#include <winsock2.h>
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
	#include <sys/utsname.h>
#endif

class Socket
{
private:
	int socketId;
	short port;

public:
	Socket() : socketId(-1), port(12345) {}

	/// <summary>
	/// 初始化 Socket
	/// </summary>
	/// <returns>初始化是否成功</returns>
	bool Init();

	/// <summary>
	/// 设置发送端口
	/// </summary>
	/// <param name="port">端口号</param>
	void SetPort(short port);

	/// <summary>
	/// 广播信息
	/// </summary>
	/// <param name="data">要广播的信息</param>
	void Broadcast(std::string data) const;

	/// <summary>
	/// 关闭 Socket
	/// </summary>
	void Close() const;
};

