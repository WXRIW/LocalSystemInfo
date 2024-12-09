#include "SystemInfo.h"

std::string SystemInfo::GetFullOutput() const
{
	std::stringstream ss;
	ss << "Host Name: " << HostName << std::endl;
	ss << "IP Address: " << IpAddress << std::endl;
	ss << "Processor Name: " << ProcessorName << std::endl;
	ss << "Processor Architecture: " << ProcessorArchitecture << std::endl;
	ss << "Processor Cores: " << ProcessorCores << std::endl;
	ss << "RAM Size: " << RamSize << std::endl;
	ss << "Disk Size: " << DiskSize << std::endl;
	return ss.str();
}

SystemInfo SystemInfo::GetCurrentSystemInfo()
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
