/************************************************************************
 * Filename:    SystemInfoHelper.cpp
 * Description: 系统信息帮助类实现
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "SystemInfoHelper.h"

SystemInfo SystemInfoHelper::GetCurrentSystemInfo()
{
    auto info = SystemInfo();
    info.HostName = SystemInfoHelper::GetHostName();
    info.IpAddress = SystemInfoHelper::GetIpAddress();
    info.ProcessorName = SystemInfoHelper::GetProcessorName();
    info.ProcessorArchitecture = SystemInfoHelper::GetProcessorArchitecture();
    info.ProcessorCores = SystemInfoHelper::GetProcessorCores();
    info.RamSize = SystemInfoHelper::GetRamInfo();
    info.DiskSize = SystemInfoHelper::GetDiskSize();
    return info;
}

std::string SystemInfoHelper::GetHostName()
{
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == 0)
    {
        return hostname;
    }
    return "Unknown";
}

std::string SystemInfoHelper::GetIpAddress()
{
    auto hostname = GetHostName();
    std::string ip_address = "Unknown";

#ifdef _WIN32
    struct addrinfo hints, * res;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    if (getaddrinfo(hostname.c_str(), nullptr, &hints, &res) == 0)
    {
        ip_address = inet_ntoa(((struct sockaddr_in*)res->ai_addr)->sin_addr);
        freeaddrinfo(res);
    }
#else
    struct addrinfo hints = {}, * res;
    hints.ai_family = AF_INET;
    if (getaddrinfo(hostname.c_str(), nullptr, &hints, &res) == 0)
    {
        struct sockaddr_in* addr = (struct sockaddr_in*)res->ai_addr;
        ip_address = inet_ntoa(addr->sin_addr);
        freeaddrinfo(res);
    }
#endif

	return ip_address;
}

std::string SystemInfoHelper::GetProcessorName()
{
    std::ostringstream info;

#ifdef _WIN32
    HKEY hKey;
    wchar_t buffer[256]{};
    DWORD buffer_size = sizeof(buffer);
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey) == ERROR_SUCCESS)
    {
        if (RegQueryValueExW(hKey, L"ProcessorNameString", nullptr, nullptr, reinterpret_cast<LPBYTE>(buffer), &buffer_size) == ERROR_SUCCESS)
        {
            info << WindowsHelper::WcharToString(buffer);
        }
        RegCloseKey(hKey);
    }
    else
    {
        info << "Unknown CPU";
    }
#elif defined(__linux__)
    std::ifstream cpuinfo("/proc/cpuinfo");
    std::string line;
    while (std::getline(cpuinfo, line))
    {
        if (line.find("model name") != std::string::npos)
        {
            info << line.substr(line.find(":") + 2);
            break;
        }
    }
    cpuinfo.close();
#elif defined(__APPLE__)
    char buffer[256];
    size_t buffer_size = sizeof(buffer);
    if (sysctlbyname("machdep.cpu.brand_string", &buffer, &buffer_size, nullptr, 0) == 0)
    {
        info << buffer;
    }
    else
    {
        info << "Unknown CPU";
    }
#else
    info << "Unknown CPU";
#endif
    return info.str();
}

std::string SystemInfoHelper::GetProcessorArchitecture()
{
#ifdef _WIN32
    SYSTEM_INFO sys_info;
    GetNativeSystemInfo(&sys_info);

    switch (sys_info.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_AMD64:
        return "x64";
    case PROCESSOR_ARCHITECTURE_INTEL:
        return "x86";
    case PROCESSOR_ARCHITECTURE_ARM64:
        return "ARM64";
    case PROCESSOR_ARCHITECTURE_ARM:
        return "ARM";
    case PROCESSOR_ARCHITECTURE_IA64:
        return "Itanium";
    default:
        return "Unknown";
    }
#elif defined(__linux__) || defined(__APPLE__)
    struct utsname sys_info;
    if (uname(&sys_info) == 0)
    {
        std::string arch = sys_info.machine;
        if (arch == "x86_64")
            return "x64";
        else if (arch == "i686" || arch == "i386")
            return "x86";
        else if (arch == "aarch64" || arch == "arm64")
            return "ARM64";
        else if (arch.find("arm") != std::string::npos)
            return "ARM";
        else
            return arch;  // 返回原始类型
    }
    return "Unknown";
#else
    return "Unknown";
#endif
}

std::string SystemInfoHelper::GetProcessorCores()
{
#ifdef _WIN32
    SYSTEM_INFO sys_info;
    GetSystemInfo(&sys_info);
    return std::to_string(sys_info.dwNumberOfProcessors);
#else
    return std::to_string(sysconf(_SC_NPROCESSORS_ONLN));
#endif
}

std::string SystemInfoHelper::GetRamInfo()
{
#ifdef _WIN32
    MEMORYSTATUSEX mem_status{};
    mem_status.dwLength = sizeof(mem_status);
    GlobalMemoryStatusEx(&mem_status);
    return std::to_string(mem_status.ullTotalPhys / (static_cast<unsigned long long>(1024) * 1024)) + " MB";
#else
    long ram = sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE) / (1024 * 1024);
    return std::to_string(ram) + " MB";
#endif
}

std::string SystemInfoHelper::GetDiskSize()
{
    std::ostringstream info;
#ifdef _WIN32
    ULARGE_INTEGER free_space, total_space;
    if (GetDiskFreeSpaceEx(L"C:\\", &free_space, &total_space, nullptr))
    {
        info << (total_space.QuadPart / (static_cast<unsigned long long>(1024) * 1024 * 1024)) << " GB";
    }
#else
    struct statvfs stat;
    if (statvfs("/", &stat) == 0)
    {
        unsigned long long total_space = stat.f_blocks * stat.f_frsize;
        unsigned long long free_space = stat.f_bfree * stat.f_frsize;
        info << (total_space / (1024 * 1024 * 1024)) << " GB";
    }
#endif
    return info.str();
}
