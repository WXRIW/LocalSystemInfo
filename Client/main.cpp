#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <vector>

#ifdef _WIN32
    #define _WINSOCK_DEPRECATED_NO_WARNINGS
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <windows.h>
    #include <wbemidl.h>
    #pragma comment(lib, "ws2_32.lib")
    #pragma comment(lib, "wbemuuid.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <ifaddrs.h>
    #include <fstream>
#endif

const int PORT = 12345;
const int BUFFER_SIZE = 1024;

#ifdef _WIN32
std::string wchar_to_string(const wchar_t* wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    std::vector<char> buffer(size_needed);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, buffer.data(), size_needed, nullptr, nullptr);
    return std::string(buffer.data());
}
#endif

std::string get_processor_info() {
    std::ostringstream info;
#ifdef _WIN32
    HKEY hKey;
    wchar_t buffer[256];
    DWORD buffer_size = sizeof(buffer);
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExW(hKey, L"ProcessorNameString", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &buffer_size) == ERROR_SUCCESS) {
            info << wchar_to_string(buffer);
        }
        RegCloseKey(hKey);
    }
#else
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line)) {
        if (line.find("model name") != std::string::npos) {
            info << line.substr(line.find(":") + 2);
            break;
        }
    }
    cpuinfo.close();
#endif
    return info.str();
}

std::string get_system_info()
{
    std::ostringstream info;

    // 获取主机名和 IP 地址
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        info << "Hostname: " << hostname << "\n";
    }
    else
    {
        info << "Hostname: Unknown\n";
    }

#ifdef _WIN32
    struct addrinfo hints, * res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    if (getaddrinfo(hostname, nullptr, &hints, &res) == 0)
    {
        info << "IP Address: " << inet_ntoa(((struct sockaddr_in*)res->ai_addr)->sin_addr) << "\n";
        freeaddrinfo(res);
    }

    // 获取处理器信息
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    info << "Processor: " << get_processor_info() << "\n";
    info << "Processor Cores: " << sys_info.dwNumberOfProcessors << "\n";

    // 获取内存信息
    MEMORYSTATUSEX mem_status;
    mem_status.dwLength = sizeof(mem_status);
    GlobalMemoryStatusEx(&mem_status);
    info << "Total RAM: " << (mem_status.ullTotalPhys / (1024 * 1024)) << " MB\n";

    // 获取存储信息
    ULARGE_INTEGER free_space, total_space;
    if (GetDiskFreeSpaceEx(L"C:\\", &free_space, &total_space, nullptr))
    {
        info << "Total Storage: " << (total_space.QuadPart / (1024 * 1024 * 1024)) << " GB\n";
        info << "Free Storage: " << (free_space.QuadPart / (1024 * 1024 * 1024)) << " GB\n";
    }

#else
    struct addrinfo hints, * res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    if (getaddrinfo(hostname, nullptr, &hints, &res) == 0)
    {
        info << "IP Address: " << inet_ntoa(((struct sockaddr_in*)res->ai_addr)->sin_addr) << "\n";
        freeaddrinfo(res);
    }

    // 获取内存信息
    struct sysinfo sys_info;
    if (sysinfo(&sys_info) == 0)
    {
        info << "Total RAM: " << (sys_info.totalram / (1024 * 1024)) << " MB\n";
    }

    // 获取处理器信息 (Linux/macOS 上只能简化实现)
    info << "Processor Cores: " << sysconf(_SC_NPROCESSORS_ONLN) << "\n";
#endif

    return info.str();
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

    SOCKET client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed." << std::endl;
        return 1;
    }

    int broadcast_enable = 1;
    if (setsockopt(client_socket, SOL_SOCKET, SO_BROADCAST, (const char*)&broadcast_enable, sizeof(broadcast_enable)) == SOCKET_ERROR)
    {
        std::cerr << "Setting broadcast option failed." << std::endl;
        return 1;
    }

    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("255.255.255.255");

    std::string system_info = get_system_info();
    sendto(client_socket, system_info.c_str(), system_info.length(), 0, (sockaddr*)&server_addr, sizeof(server_addr));

    std::cout << "Broadcast message sent:\n" << system_info << std::endl;

#ifdef _WIN32
    closesocket(client_socket);
    WSACleanup();
#else
    close(client_socket);
#endif

    return 0;
}