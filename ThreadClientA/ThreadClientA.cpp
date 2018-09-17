// ThreadClientA.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h> //windows socket的头文件
#include <Windows.h>
#include <iostream>
#include <thread>
#include <process.h>

#pragma comment(lib, "ws2_32.lib") //连接winsock2.h的静态库文件

using namespace std;

DWORD WINAPI ConOrder(LPVOID P)
{
	//客户端socket
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, 0);
	//初始化socket信息
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(SOCKADDR));
	//clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddr.sin_family = PF_INET;
	clientAddr.sin_port = htons(3001);
	//建立连接
	int i = connect(clientSock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));
	if (i < 0)
	{
		std::cout << "3001连接失败" << std::endl;
		return 0;
	}
	cout << "3001已建立连接。" << endl;
	while (1)
	{
		char *a = new char[100];
		memset(a, 0, sizeof(a));
		a = "123Order";
		send(clientSock, a, strlen(a)*sizeof(char) + 1, NULL);
	}
	return 0;
}

DWORD WINAPI ConData(LPVOID P)
{
	//客户端socket
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, 0);
	//初始化socket信息
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(SOCKADDR));
	//clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddr.sin_family = PF_INET;
	clientAddr.sin_port = htons(3075);
	//建立连接
	int i = connect(clientSock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));
	if (i < 0)
	{
		std::cout << "3075连接失败" << std::endl;
		return 0;
	}
		
	cout << "3075已建立连接。" << endl;
	while (1)
	{
		char *a = new char[100];
		memset(a, 0, sizeof(a));
		a = "456Data";
		send(clientSock, a, strlen(a)*sizeof(char) + 1, NULL);
	}
	return 0;
}

int main()
{
	//加载winsock库
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 3), &wsadata);

	HANDLE handleOrderThread;
	HANDLE handleDataThread;
	DWORD dwThreadID = 0;
	DWORD dwThreadID2 = 0;
	handleOrderThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ConOrder, 0, 0, &dwThreadID);
	Sleep(1000);
	handleDataThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ConData, 0, 0, &dwThreadID2);
	WaitForSingleObject(handleOrderThread, INFINITE);
	WaitForSingleObject(handleDataThread, INFINITE);
	

	system("pause");

	return 0;
}
