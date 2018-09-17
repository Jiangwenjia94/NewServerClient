// ThreadServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <WinSock2.h> //windows socket的头文件
#include <Windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <process.h>
#include "TerminalInterface.h"
#pragma comment(lib, "ws2_32.lib") //连接winsock2.h的静态库文件




//定义结构体用来设置
typedef struct my_file
{
	SOCKET clientSocket; //文件内部包含了一个SOCKET 用于和客户端进行通信
	sockaddr_in clientAddr; //用于保存客户端的socket地址
	int id; //文件块的序号
}F;

DWORD WINAPI transmmit(const LPVOID arg)
{
	//实际上这里为了追求并发性不应该加锁，上锁是为了方便看输出
//	m.lock();
	while (1)
	{
		F *temp = (F*)arg;
		//获取文件的序号
		//int file_id = temp->id;
		//获取客户机的端口号
		//ntohs(temp -> clientAddr.sin_port); 
		std::cout << "测试开始,等待客户端发送消息..." << std::endl;
		//从客户端处接受数据
		char Buffer[MAXBYTE] = { 0 }; //缓冲区
		recv(temp->clientSocket, Buffer, MAXBYTE, 0); //recv方法 从客户端通过clientScocket接收
		std::cout << "线程" << temp->id << "从客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口收到:" << Buffer << std::endl;

		//发送简单的字符串到客户端
		const char* s = "Server file";
		send(temp->clientSocket, s, strlen(s)*sizeof(char) + 1, NULL);
		std::cout << "线程" << temp->id << "通过客户端的" << ntohs(temp->clientAddr.sin_port) << "号端口发送:" << s << std::endl;
		//	m.unlock();
	}
	return 0;
}

my_file Order;
my_file Data;
SOCKET Socket_Order;
SOCKET Socket_Data;

void OrderCout()
{
	char Buffer[MAXBYTE] = { 0 };
	recv(Order.clientSocket, Buffer, MAXBYTE, 0);
	std::cout << "通过端口:" << ntohs(Order.clientAddr.sin_port) << "接收到:" << Buffer << std::endl;
}

struct WC
{
	wchar_t *cc;
};

void OrderCin()
{
	int num = 5;
	char *a;
	a = new char[num];
	for (int i = 0; i < num; i++)
	{
		a[i] = i;
		if (i == 24)
			std::cout << a[i] << " ";
		std::cout << a[i] << " ";
	}
	int size = num;
	int	senn = 2;
	bool isfin = false;
	while (1)
	{
		if (isfin)
			break;
		if (size < 2)
		{
			senn = size % 2;
			isfin = true;
		}
		int SendSize = send(Order.clientSocket, (char*)a, senn, 0);
		if (SOCKET_ERROR == SendSize)
			break;
		size = size - SendSize;//用于循环发送且退出功能
		a += SendSize;//用于计算已发buffer的偏移量
	}
}

void DataCout()
{
	char Buffer[MAXBYTE] = { 0 };
	recv(Data.clientSocket, Buffer, MAXBYTE, 0);
	std::cout << "通过端口:" << ntohs(Data.clientAddr.sin_port) << "接收到:" << Buffer << std::endl;
}

DWORD WINAPI RunOrderMode(LPVOID lpParam)//LAN主线程
{
	int ulRetCode = 1;
	sockaddr_in		servAddr;
	SOCKET			LocalSocket = INVALID_SOCKET;
	sockaddr_in		clntAddr;
	sockaddr		tcpaddr;
	SOCKET			ClientSocket = INVALID_SOCKET;
	int				size = 0;
	

	WSADATA		WSAData = { 0 };
	ulRetCode = WSAStartup(MAKEWORD(2, 2), &WSAData);
	LocalSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (LocalSocket == INVALID_SOCKET)
	{
		printf("=CRITICAL= | socket() call failed. WSAGetLastError = [%d]\n", WSAGetLastError());

		return ulRetCode;
	}

	memset(&servAddr, 0, sizeof(SOCKADDR)); //初始化socket地址
	servAddr.sin_family = PF_INET; //设置使用的协议族
	servAddr.sin_port = htons(3001); //设置使用的端口
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //define s_addr = S_un.S_addr

	if (SOCKET_ERROR == bind(LocalSocket, (SOCKADDR *)&servAddr, sizeof(SOCKADDR)))
	{
		printf("=CRITICAL= | bind() call failed w/socket = [0x%X]. WSAGetLastError=[%d]\n",
			LocalSocket, WSAGetLastError());
	}


	if (SOCKET_ERROR == listen(LocalSocket, SOMAXCONN))
	{

		printf("=CRITICAL= | listen() call failed w/socket = [0x%X]. WSAGetLastError=[%d]\n", LocalSocket, WSAGetLastError());

	}
	printf("3001等待连接...\n");

	size = sizeof(struct sockaddr);
	while (1)//开始循环接收Client
	{
		ClientSocket = accept(LocalSocket, (struct sockaddr *)&tcpaddr, (int *)&size);
		if (INVALID_SOCKET == ClientSocket)
		{
			printf("获取的SOCKET无效\n");
			break;
		}
		else if (INVALID_SOCKET == ClientSocket)
		{
			printf("不能获得用户连接的SOCK");
			break;
		}
		else
		{
			printf("3001连接成功\n");
			Order.clientSocket = ClientSocket;
			Order.clientAddr = servAddr;
	//		OrderCout();
			OrderCin();
		}
	}
	if (INVALID_SOCKET != LocalSocket)
		closesocket(LocalSocket);
	return 9999;//乱写的数字
}


DWORD WINAPI RunDataMode(LPVOID lpParam)//LAN主线程
{
	int ulRetCode = 1;
	sockaddr_in		servAddr;
	SOCKET			LocalSocket = INVALID_SOCKET;
	sockaddr_in		clntAddr;
	sockaddr		tcpaddr;
	SOCKET			ClientSocket = INVALID_SOCKET;
	int				size = 0;


	WSADATA		WSAData = { 0 };
	ulRetCode = WSAStartup(MAKEWORD(2, 2), &WSAData);
	LocalSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (LocalSocket == INVALID_SOCKET)
	{
		printf("=CRITICAL= | socket() call failed. WSAGetLastError = [%d]\n", WSAGetLastError());

		return ulRetCode;
	}

	memset(&servAddr, 0, sizeof(SOCKADDR)); //初始化socket地址
	servAddr.sin_family = PF_INET; //设置使用的协议族
	servAddr.sin_port = htons(3075); //设置使用的端口
	servAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //define s_addr = S_un.S_addr

	if (SOCKET_ERROR == bind(LocalSocket, (SOCKADDR *)&servAddr, sizeof(SOCKADDR)))
	{
		printf("=CRITICAL= | bind() call failed w/socket = [0x%X]. WSAGetLastError=[%d]\n",
			LocalSocket, WSAGetLastError());
	}


	if (SOCKET_ERROR == listen(LocalSocket, SOMAXCONN))
	{

		printf("=CRITICAL= | listen() call failed w/socket = [0x%X]. WSAGetLastError=[%d]\n", LocalSocket, WSAGetLastError());

	}
	printf("3075等待连接...\n");

	size = sizeof(struct sockaddr);
	while (1)//开始循环接收Client
	{
		ClientSocket = accept(LocalSocket, (struct sockaddr *)&tcpaddr, (int *)&size);
		if (INVALID_SOCKET == ClientSocket)
		{
			printf("获取的SOCKET无效\n");
			break;
		}
		else if (INVALID_SOCKET == ClientSocket)
		{
			printf("不能获得用户连接的SOCK");
			break;
		}
		else
		{
			printf("3075连接成功\n");
			Data.clientSocket = ClientSocket;
			Data.clientAddr = servAddr;
			DataCout();
		}
	}
	if (INVALID_SOCKET != LocalSocket)
		closesocket(LocalSocket);
	return 9999;//乱写的数字
}


int main()
{
	HANDLE handleOrderThread;
	HANDLE handleDataThread;
	DWORD dwThreadID = 0;
	DWORD dwThreadID2 = 0;
	handleOrderThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RunOrderMode, 0, 0, &dwThreadID);
	handleDataThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)RunDataMode, 0, 0, &dwThreadID2);
	WaitForSingleObject(handleOrderThread, INFINITE);
	WaitForSingleObject(handleDataThread, INFINITE);

	system("pause");

	return 0;
}

