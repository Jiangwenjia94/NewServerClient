// ThreadClientA.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h> //windows socket��ͷ�ļ�
#include <Windows.h>
#include <iostream>
#include <thread>
#include <process.h>

#pragma comment(lib, "ws2_32.lib") //����winsock2.h�ľ�̬���ļ�

using namespace std;

DWORD WINAPI ConOrder(LPVOID P)
{
	//�ͻ���socket
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, 0);
	//��ʼ��socket��Ϣ
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(SOCKADDR));
	//clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddr.sin_family = PF_INET;
	clientAddr.sin_port = htons(3001);
	//��������
	int i = connect(clientSock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));
	if (i < 0)
	{
		std::cout << "3001����ʧ��" << std::endl;
		return 0;
	}
	cout << "3001�ѽ������ӡ�" << endl;
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
	//�ͻ���socket
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, 0);
	//��ʼ��socket��Ϣ
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(SOCKADDR));
	//clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddr.sin_family = PF_INET;
	clientAddr.sin_port = htons(3075);
	//��������
	int i = connect(clientSock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));
	if (i < 0)
	{
		std::cout << "3075����ʧ��" << std::endl;
		return 0;
	}
		
	cout << "3075�ѽ������ӡ�" << endl;
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
	//����winsock��
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
