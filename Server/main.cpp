#include <iostream>
#include <cstring>
#include <cstdlib>

#ifdef _WIN32
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

const int PORT = 12345;
const int BUFFER_SIZE = 1024;

static void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
    if (bytes_received > 0)
    {
        buffer[bytes_received] = '\0';
        std::cout << "Received from client:\n" << buffer << std::endl;
    }

#ifdef _WIN32
    closesocket(client_socket);
#else
    close(client_socket);
#endif
}

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

    int server_socket = socket(AF_INET, SOCK_DGRAM, 0);  // 使用UDP协议
    if (server_socket == -1)
    {
        std::cerr << "Socket creation failed." << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Bind failed." << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << "..." << std::endl << std::endl;

    while (true)
    {
        sockaddr_in client_addr{};
        socklen_t client_addr_len = sizeof(client_addr);
		char buffer[BUFFER_SIZE];

		int bytes_received = recvfrom(server_socket, buffer, BUFFER_SIZE - 1, 0, (sockaddr*)&client_addr, &client_addr_len);
		if (bytes_received >= 0 && bytes_received < BUFFER_SIZE)
		{
			buffer[bytes_received] = '\0';
			std::cout << "Received message from " << inet_ntoa(client_addr.sin_addr) << ": " << std::endl << buffer << std::endl;

			// 发送响应
			const char* response = "Server received your message.";
			sendto(server_socket, response, std::strlen(response), 0, (sockaddr*)&client_addr, client_addr_len);
		}
	}

#ifdef _WIN32
	closesocket(server_socket);
	WSACleanup();
#else
    close(server_socket);
#endif

    return 0;
}
