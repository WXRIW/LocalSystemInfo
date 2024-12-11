/************************************************************************
 * Filename:    main.cpp
 * Description: Client 程序入口点
 * Author:      XY Wang
 * Repository:  https://github.com/WXRIW/LocalSystemInfo
 * License:     MIT license
 * Copyright:   Copyright 2024 WXRIW
 ************************************************************************/

#include "Socket.h"
#include "SystemInfoHelper.h"

int main()
{
	// 定义并初始化 Socket
	auto socket = Socket();
	socket.Init();

	// 获取系统信息
	auto system_info = SystemInfoHelper::GetCurrentSystemInfo();
	auto output = system_info.GetFullOutput();

	// 广播系统信息
	socket.Broadcast(output);

	// 关闭 Socket
	socket.Close();

    return 0;
}
