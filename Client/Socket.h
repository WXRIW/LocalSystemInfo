/************************************************************************
 * Filename:    Socket.h
 * Description: Socket �����ඨ��
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
	/// ��ʼ�� Socket
	/// </summary>
	/// <returns>��ʼ���Ƿ�ɹ�</returns>
	bool Init();

	/// <summary>
	/// ���÷��Ͷ˿�
	/// </summary>
	/// <param name="port">�˿ں�</param>
	void SetPort(short port);

	/// <summary>
	/// �㲥��Ϣ
	/// </summary>
	/// <param name="data">Ҫ�㲥����Ϣ</param>
	void Broadcast(std::string data) const;

	/// <summary>
	/// �ر� Socket
	/// </summary>
	void Close() const;
};
