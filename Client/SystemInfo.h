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
	std::string GetFullOutput() const;

	static SystemInfo GetCurrentSystemInfo();
};
