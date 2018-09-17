// ThreadClientA.cpp : �������̨Ӧ�ó������ڵ㡣
//


#include "stdafx.h"

#include <WinSock2.h> //windows socket��ͷ�ļ�
#include <Windows.h>
#include <iostream>
#include <thread>
#include <process.h>
#include <string>
#include <cstring>
#define MAX_DATA_SIZE                     1000
#define CXN_BDADDR_STR_LEN                17   // 6 two-digit hex values plus 5 colons
#define CXN_MAX_INQUIRY_RETRY             3
#define CXN_DELAY_NEXT_INQUIRY            15
#define CXN_SUCCESS                       0
#define CXN_ERROR                         1
#define MAX_SIZE_LENGTH                   1000
#define END_OF_DATA                       '\0'
#define MAX_NUM_OF_DEVICES                100

//����
#define C_LINK							  12345
#define C_HEART_LIVE_NOTICE				  9999
#define C_HEART_IMAGE_ASK				  8888
#define C_HEART_IMAGE_READLY			  7777
#define C_HEART_IMAGE_REFUSE			  -1
#define C_HEART_IMAGE_SUCCESS			  6666
#define C_HEART_IMAGE_FAIL				  -2
#define C_HEART_NOTIC_READLY			  5555
#define C_HEART_NOTIC_REFUSE			  -5
#define C_HEART_NOTIC_SUCCESS			  4444
#define C_HEART_NOTIC_FAIL				  -6
#define C_HEART_NOTIC_ASK				  3333
#define C_HEART_ORBIT_ASK				  2222
#define C_HEART_ORBIT_SUCCESS			  1111
#define C_HEART_ORBIT_FAIL				  -7
#define C_HEART_ORBIT_READLY			  8
#define C_HEART_ORBIT_REFUSE			  -8
//����
#define S_LINK							  12345
#define S_HEART_LIVE_FEED				  0
#define S_HEART_ASK_RECEIVE				  1
#define S_HEART_ASK_REFUSE				  -1
#define S_HEART_ASK_SUCCESS				  2
#define S_HEART_ASK_FAIL				  0
#define S_HEART_IMAGE_READLY			  3
#define S_HEART_NOTIC_READLY			  4
#define S_HEART_ORDER_RECEIVE			  5
#define S_HEART_ERROR					  -9999

#pragma comment(lib, "ws2_32.lib") //����winsock2.h�ľ�̬���ļ�

using namespace std;

char *orderinfo;
string tempname;

int recvCurPic(SOCKET &localSocket, char *FileName)
{
	if (FileName == NULL)
		return 1;
	UINT result = 0;
	char buffer[1010];
	char temp[1010];
	memset(buffer, 0, sizeof(buffer));
	memset(temp, 0, sizeof(temp));
	
	int lFileSize = 0;
	int rcv = 0;
	rcv = recv(localSocket, (char *)&lFileSize, sizeof(int), 0);
	cout << "�ļ����ڽ���...." << endl;
	//����������//	
	//���ܲ������ļ���
	CString strFileName = FileName;
	strFileName += ".jpg";
	LPCTSTR path = strFileName ;
	CFile file(path, CFile::modeCreate | CFile::modeWrite);
	long iTemp = 0;
	int p = 0;
	Sleep(100);
	while (1)
	{

		rcv = recv(localSocket, buffer, 1010, 0);
		if (rcv == 0)
		{
			break;
		}
		//if(iTemp % 1024 != 0)
		//	cout<<"p";
		
		file.Write(buffer, rcv);
		iTemp += rcv;
		p++;
		cout << iTemp << " : " << rcv << " : " << p << endl;

		char *pszData = "t";
		send(localSocket, pszData, strlen(pszData), 0);
		if (iTemp == lFileSize)
			break;
	}
	file.Close();
	if (iTemp != lFileSize)
	{
		cout << "�ļ�����ʧ�ܣ�" << endl;
		result = 1;
		return result;
	}
	//	ShowPIC();
	cout << "�ļ����ճɹ���" << endl;
	//	shutdown(param->serverSocket, SD_BOTH);
	//	closesocket(param->serverSocket);
	return result;

}

char * setUserNum(char &A)
{
	char *tmp = new char[64];
	memset(tmp,0,sizeof(tmp));
	for (int t = 0; t < 64; t++)
	{
		tmp[t] = A;
		//	cout<<user_num[t]<<endl;
	}
	return tmp;
}
int ordernum = 123;//����˷�����Ψһָ����
int sendCurHrt(SOCKET &LocalSocket, bool fir,char &Num)
{
	int r_order = C_LINK;
	int s_order = -9999;
	
	int sen = 0;
	int rec = 0;
	int datalength = 100;//���������ָ�����������Ϣ
	//	char *orderinfo;

	char *user_num;
	user_num = new char[64];
	memset(user_num, 0, sizeof(user_num));
	if (fir == true)
	{
		user_num = setUserNum(Num);
		orderinfo = new char[datalength];
		memset(orderinfo, 0, sizeof(orderinfo));
		orderinfo = "test.jpg*9202";

		cout << "��һ������" << endl;
		s_order = C_LINK;
		sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0); //������֤��Ϣ
		if (sen <= 0)
			return -9998;
		rec = recv(LocalSocket, (char *)&r_order, sizeof(int), 0);
		if (rec <= 0)
			return -9999;
		sen = send(LocalSocket, user_num, 64, 0);
		if (sen <= 0)
			return -9998;
		rec = recv(LocalSocket, user_num, 64, 0);
		if (rec != 64)
			return -9999;
	}
	if (r_order == S_LINK)	//��֤ͨ��
	{

		//�û���֤��Ψһ��ȷ�������ӳɹ�

		//��ʼ���������ݴ���
		cout << "��������" << endl;
		cin>>s_order;	//��һ��������������s_order
		sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0);
		if (sen <= 0)
			return -9998;

		rec = recv(LocalSocket, (char *)&r_order, sizeof(int), 0);//���շ���
		if (rec <= 0)
			return -9999;
		switch (r_order)
		{
		case S_HEART_LIVE_FEED:				//s_orderΪ9999
		{
			//Ӧ�ص�s_order = makeOrder();
			break;
		}
		case S_HEART_ASK_RECEIVE:				//����˽���ͼƬָ������
		{
			rec = recv(LocalSocket, (char *)&r_order, sizeof(int), 0);//����Ψһָ����
			if (rec <= 0)
				break;
			if (r_order == S_HEART_ASK_FAIL)	//��ʾ����˾ܾ�����ָ��
			{
				s_order = C_HEART_IMAGE_ASK;
				break;
			}
			ordernum = r_order;

			cout << "����ͼƬ���ƣ�" << endl;

			cin >> tempname;
			orderinfo = (char *)tempname.data();
			datalength = strlen(orderinfo) + 1;
			sen = send(LocalSocket, (char *)&datalength, sizeof(int), 0); //����ָ���
			if (sen <= 0)
				break;
			orderinfo[datalength - 1] = '\0';
			sen = send(LocalSocket, orderinfo, datalength, 0);
			if (sen <= 0)
				break;

			rec = recv(LocalSocket, (char *)&r_order, sizeof(int), 0);//���ճɹ������
			if (rec <= 0)
				break;
			if (r_order == S_HEART_ASK_FAIL)
			{
				s_order = C_HEART_IMAGE_ASK;
				break;
			}
			//ת������
			s_order = C_HEART_LIVE_NOTICE;
			break;

		}
		case S_HEART_IMAGE_READLY: //�����ͼƬ׼����ϣ����Է���
		{
			s_order = C_HEART_IMAGE_READLY;	//��C_HEART_IMAGE_REFUSE����makeOrder()����
			//	s_order = makeOrder();
			sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0);
			if (sen <= 0)
				break;
			rec = recv(LocalSocket, (char *)&r_order, sizeof(int), 0);
			if (rec <= 0 /*|| r_order != ordernum*/)//��Ҫ����һ�����յ���order_num�Ƿ��ǵ�ǰ�ͻ�������������жϺ���
				break;
			char order_num[10];
			sprintf(order_num,"%d",r_order);
			int result = recvCurPic(LocalSocket, order_num);//��user_num��Ϊ�ļ���
		//	int result = recvCurPic(LocalSocket, orderinfo);//�ڶ�������������Ҫһ���ý�ȡ�����ݶ�Ϊ����
		//	int result = 0;
			if (result != 0)//����ʧ��
			{
				s_order = C_HEART_IMAGE_FAIL;
				send(LocalSocket, (char *)&s_order, sizeof(int), 0);
				break;
			}
			s_order = C_HEART_IMAGE_SUCCESS;
			sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0);
			if (sen <= 0)
				break;
			s_order = C_HEART_LIVE_NOTICE;//ת������
			break;
		}
		case S_HEART_NOTIC_READLY://����״̬��Ϣ��������
		{
			s_order = C_HEART_NOTIC_READLY;
			sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0);
			if (sen <= 0)
				break;
			char *stainfo;
			int length = 0;
			rec = recv(LocalSocket, (char *)&length, sizeof(int), 0); //����״̬��Ϣ����
			if (rec <= 0)
				break;
			if (length > 0)
			{
				stainfo = new char[length];
				memset(stainfo, 0, sizeof(stainfo));
			}
			rec = recv(LocalSocket, stainfo, length, 0); //����״̬��Ϣ
			if (rec <= 0)
				break;
			if (length != rec)
			{
				s_order = C_HEART_NOTIC_FAIL;
				send(LocalSocket, (char *)&s_order, sizeof(int), 0);
				break;
			}
			cout << stainfo << endl;
			s_order = C_HEART_NOTIC_SUCCESS;//�ݶ��ɹ�
			sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0);
			if (sen <= 0)
				break;
			s_order = C_HEART_LIVE_NOTICE;
			break;
		}
		case S_HEART_ORDER_RECEIVE://����״̬��Ϣ��������
		{
			int inq_num;
			cout << "�����ѯ�����ţ�";
			cin >> inq_num;
		//	sen = send(LocalSocket, (char *)&ordernum, sizeof(int), 0);
			sen = send(LocalSocket, (char *)&inq_num, sizeof(int), 0);
			if (sen <= 0)
				break;

			char *stainfo;
			int length = 0;
			rec = recv(LocalSocket, (char *)&length, sizeof(int), 0); //����״̬��Ϣ����
			if (rec <= 0)
				break;
			if (length > 0)
			{
				stainfo = new char[length];
				memset(stainfo, 0, sizeof(stainfo));
			}
			rec = recv(LocalSocket, stainfo, length, 0); //����״̬��Ϣ
			if (rec <= 0)
				break;
			if (length != rec)
			{
				s_order = C_HEART_NOTIC_FAIL;
				send(LocalSocket, (char *)&s_order, sizeof(int), 0);
				break;
			}
			cout << stainfo << endl;
			s_order = C_HEART_NOTIC_SUCCESS;//�ݶ��ɹ�
			sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0);
			if (sen <= 0)
				break;
			s_order = C_HEART_LIVE_NOTICE;

		}
		case C_HEART_ORBIT_READLY:
		{
			double time[8] = { 2018, 8, 24, 0, 0, 0, 4, 10 };//6λʱ�䣬ʱ�䵥λ��ʱ�䳤��
			double pos[3] = { 0.0 };
			int sta = C_HEART_ORBIT_SUCCESS;
			sen = send(LocalSocket, (char *)time, sizeof(time), 0);
			if (sen <= 0)
				break;
			for (int i = 0; i < 10; i++)
			{
				rec = recv(LocalSocket, (char *)pos, sizeof(pos), 0);
				if (rec <= 0)
					break;
			//	cout << pos[0] << " " << pos[1] << " " << pos[2] << endl;
				printf("%18.4f %18.4f %18.4f\n", pos[0], pos[1], pos[2]);
			}
			sen = send(LocalSocket, (char *)&sta, sizeof(sta), 0);
			if (sen <= 0)
				break;
		}
		default:			///����˾ܾ�ͼƬ����-1
			break;
		}
		if (s_order == C_HEART_LIVE_NOTICE)
		{
			sen = send(LocalSocket, (char *)&s_order, sizeof(int), 0); //������֤��Ϣ
			if (sen <= 0)
				return -9998;
			rec = recv(LocalSocket, (char *)&r_order, sizeof(int), 0);
			if (rec <= 0)
				return -9999;
		}
	}
}

void startRecvThread()
{
	int count = 0;
	bool flag = true;//0 for msg,1 for pic
	while (true)
	{
	//	sendCurHrt(flag);
		flag = false;
		
	}
	printf("thread out\n");

}

int main()
{
	//����winsock��
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 3), &wsadata);

	//�ͻ���socket
	SOCKET clientSock = socket(PF_INET, SOCK_STREAM, 0);
	//��ʼ��socket��Ϣ
	sockaddr_in clientAddr;
	memset(&clientAddr, 0, sizeof(SOCKADDR));
	//clientAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	clientAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	clientAddr.sin_family = PF_INET;
	clientAddr.sin_port = htons(2017);
	//��������
	int c = connect(clientSock, (SOCKADDR*)&clientAddr, sizeof(SOCKADDR));

	cout << "�ѽ������ӡ�" << endl;
	bool flag = true;
	char A = 'c';
	while (1)
	{
		sendCurHrt(clientSock, flag,A);
		flag = false;
	}
	closesocket(clientSock);
	WSACleanup();

	cout << "�ͻ��������ѹرա�" << endl;
	system("pause");

	return 0;
}
