// ThreadServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h> //windows socket��ͷ�ļ�
#include <Windows.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <process.h>
#include "TerminalInterface.h"
#pragma comment(lib, "ws2_32.lib") //����winsock2.h�ľ�̬���ļ�




//����ṹ����������
typedef struct my_file
{
	SOCKET clientSocket; //�ļ��ڲ�������һ��SOCKET ���ںͿͻ��˽���ͨ��
	sockaddr_in clientAddr; //���ڱ���ͻ��˵�socket��ַ
	int id; //�ļ�������
}F;

DWORD WINAPI transmmit(const LPVOID arg)
{
	//ʵ��������Ϊ��׷�󲢷��Բ�Ӧ�ü�����������Ϊ�˷��㿴���
//	m.lock();
	while (1)
	{
		F *temp = (F*)arg;
		//��ȡ�ļ������
		//int file_id = temp->id;
		//��ȡ�ͻ����Ķ˿ں�
		//ntohs(temp -> clientAddr.sin_port); 
		std::cout << "���Կ�ʼ,�ȴ��ͻ��˷�����Ϣ..." << std::endl;
		//�ӿͻ��˴���������
		char Buffer[MAXBYTE] = { 0 }; //������
		recv(temp->clientSocket, Buffer, MAXBYTE, 0); //recv���� �ӿͻ���ͨ��clientScocket����
		std::cout << "�߳�" << temp->id << "�ӿͻ��˵�" << ntohs(temp->clientAddr.sin_port) << "�Ŷ˿��յ�:" << Buffer << std::endl;

		//���ͼ򵥵��ַ������ͻ���
		const char* s = "Server file";
		send(temp->clientSocket, s, strlen(s)*sizeof(char) + 1, NULL);
		std::cout << "�߳�" << temp->id << "ͨ���ͻ��˵�" << ntohs(temp->clientAddr.sin_port) << "�Ŷ˿ڷ���:" << s << std::endl;
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
	std::cout << "ͨ���˿�:" << ntohs(Order.clientAddr.sin_port) << "���յ�:" << Buffer << std::endl;
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
		size = size - SendSize;//����ѭ���������˳�����
		a += SendSize;//���ڼ����ѷ�buffer��ƫ����
	}
}

void DataCout()
{
	char Buffer[MAXBYTE] = { 0 };
	recv(Data.clientSocket, Buffer, MAXBYTE, 0);
	std::cout << "ͨ���˿�:" << ntohs(Data.clientAddr.sin_port) << "���յ�:" << Buffer << std::endl;
}

DWORD WINAPI RunOrderMode(LPVOID lpParam)//LAN���߳�
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

	memset(&servAddr, 0, sizeof(SOCKADDR)); //��ʼ��socket��ַ
	servAddr.sin_family = PF_INET; //����ʹ�õ�Э����
	servAddr.sin_port = htons(3001); //����ʹ�õĶ˿�
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
	printf("3001�ȴ�����...\n");

	size = sizeof(struct sockaddr);
	while (1)//��ʼѭ������Client
	{
		ClientSocket = accept(LocalSocket, (struct sockaddr *)&tcpaddr, (int *)&size);
		if (INVALID_SOCKET == ClientSocket)
		{
			printf("��ȡ��SOCKET��Ч\n");
			break;
		}
		else if (INVALID_SOCKET == ClientSocket)
		{
			printf("���ܻ���û����ӵ�SOCK");
			break;
		}
		else
		{
			printf("3001���ӳɹ�\n");
			Order.clientSocket = ClientSocket;
			Order.clientAddr = servAddr;
	//		OrderCout();
			OrderCin();
		}
	}
	if (INVALID_SOCKET != LocalSocket)
		closesocket(LocalSocket);
	return 9999;//��д������
}


DWORD WINAPI RunDataMode(LPVOID lpParam)//LAN���߳�
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

	memset(&servAddr, 0, sizeof(SOCKADDR)); //��ʼ��socket��ַ
	servAddr.sin_family = PF_INET; //����ʹ�õ�Э����
	servAddr.sin_port = htons(3075); //����ʹ�õĶ˿�
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
	printf("3075�ȴ�����...\n");

	size = sizeof(struct sockaddr);
	while (1)//��ʼѭ������Client
	{
		ClientSocket = accept(LocalSocket, (struct sockaddr *)&tcpaddr, (int *)&size);
		if (INVALID_SOCKET == ClientSocket)
		{
			printf("��ȡ��SOCKET��Ч\n");
			break;
		}
		else if (INVALID_SOCKET == ClientSocket)
		{
			printf("���ܻ���û����ӵ�SOCK");
			break;
		}
		else
		{
			printf("3075���ӳɹ�\n");
			Data.clientSocket = ClientSocket;
			Data.clientAddr = servAddr;
			DataCout();
		}
	}
	if (INVALID_SOCKET != LocalSocket)
		closesocket(LocalSocket);
	return 9999;//��д������
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

