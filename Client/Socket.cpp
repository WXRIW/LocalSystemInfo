/************************************************************************
 * Filename:    Socket.cpp
 * Description: Socket ∏®÷˙¿‡ µœ÷
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "Socket.h"

bool Socket::Init()
{
#ifdef _WIN32
	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
	{
		std::cerr << "WSAStartup failed." << std::endl;
		return false;
	}
#endif

	int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (client_socket < 0)
	{
		std::cerr << "Socket creation failed.\n";
		return false;
	}

#ifdef _WIN32
	int broadcast_enable = 1;
	if (setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast_enable, sizeof(broadcast_enable)) == SOCKET_ERROR)
	{
		std::cerr << "Setting broadcast option failed." << std::endl;
		return false;
	}
#else
	int broadcast_enable = 1;
	if (setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0)
	{
		std::cerr << "Setting broadcast option failed." << std::endl;
		close(client_socket);
		return false;
	}
#endif
	socketId = client_socket;

	return true;
}

void Socket::SetPort(short port)
{
	this->port = port;
}

void Socket::Broadcast(std::string data) const
{
	if (socketId < 0)
	{
		std::cerr << "Socket not created.\n";
		return;
	}

	sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

	sendto(socketId, data.c_str(), data.length(), 0, (sockaddr*)&server_addr, sizeof(server_addr));

	std::cout << "Broadcast message sent:\n" << data << std::endl;
}

void Socket::Close() const
{
	if (socketId < 0)
	{
		std::cerr << "Socket not created.\n";
		return;
	}

#ifdef _WIN32
	closesocket(socketId);
	WSACleanup();
#else
	close(socketId);
#endif
}