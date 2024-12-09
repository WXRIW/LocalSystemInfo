#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "SystemInfo.h"

const int PORT = 12345;
const int BUFFER_SIZE = 1024;

int main()
{
#ifdef _WIN32
    WSADATA wsa_data;
    if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0)
    {
        std::cerr << "WSAStartup failed." << std::endl;
        return 1;
    }
#endif

    int client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0)
    {
		std::cerr << "Socket creation failed.\n";
		return 1;
	}

#ifdef _WIN32
	int broadcast_enable = 1;
	if (setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast_enable, sizeof(broadcast_enable)) == SOCKET_ERROR)
	{
		std::cerr << "Setting broadcast option failed." << std::endl;
		return 1;
	}
#else
	int broadcast_enable = 1;
	if (setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, &broadcast_enable, sizeof(broadcast_enable)) < 0)
	{
		std::cerr << "Setting broadcast option failed." << std::endl;
		close(client_socket);
		return 1;
	}
#endif

	sockaddr_in server_addr;
	std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

	auto system_info = SystemInfo::GetCurrentSystemInfo();
	auto output = system_info.GetFullOutput();
    sendto(client_socket, output.c_str(), output.length(), 0, (sockaddr*)&server_addr, sizeof(server_addr));

    std::cout << "Broadcast message sent:\n"
              << output << std::endl;

#ifdef _WIN32
    closesocket(client_socket);
    WSACleanup();
#else
    close(client_socket);
#endif

    return 0;
}