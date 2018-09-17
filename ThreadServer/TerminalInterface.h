
#include <bitset>   
struct MsgHeader				//��Ϣͷ  12byte
{
	int begin = 1234567890;		//��Ϣ��ʼ
	int length;					//��Ϣ���ȣ�������Ϣͷ����Ϣβ��
	int id;						//����ʶ
};

int end = -1234567890;			//��Ϣβ

struct InvalidInstruction		//��Чָ����Ӧ	20byte
{
	MsgHeader header_0;			//��Ϣͷ
	int message = -1;			//��Чָ����Ϣ

	int end = -1234567890;		//��Ϣβ
};

struct RefuseInstuction			//������Ӧ
{
	MsgHeader header_0;			//��Ϣͷ

	int message = -2;			//��Чָ����Ϣ

	int end = -1234567890;		//��Ϣβ
};
//����ָ��
struct DataQuery_0				//3.5.1 �����㼶�����б��ѯָ��,��128���ֽ�
{
	MsgHeader header_0;			//��Ϣͷ
	int id;						//ģ��ID
	int request_id;				//������
	int requirement;			//��ѯ������ͨ������bitλ�õ�int��
	wchar_t satellite[20];		//������
	int time_begin[2];			//���յ����ݵĿ�ʼʱ��
	int time_begin_years;		//���յ����ݵĿ�ʼ���
	int time_end[2];			//���յ����ݵĽ���ʱ��
	int time_end_years;			//���յ����ݵĽ������
	int range_begin;			//Ҫ���յĵ���Χ��ʼֵ
	int range_end;				//Ҫ���յĵ���Χ����ֵ
	int list_max;				//��ѯ������б�����(1-100)
	int retention[6];			//����ֵ
	int end = -1234567890;		//��Ϣβ
};

struct Data_0
{
	wchar_t satellite[20];		//��һ�����ݵ�������
	int time_begin[2];			//��һ�����ݵĿ�ʼʱ��
	int time_begin_years;		//��һ�����ݵĿ�ʼ���
	int time_end[2];			//��һ�����ݵĽ���ʱ��
	int time_end_years;			//��һ�����ݵĽ������
	int range_begin;			//��һ�����ݵĵ���Χ��ʼֵ
	int range_end;				//��һ�����ݵĵ���Χ����ֵ
	float data_size;			//��һ�����ݵ�������
	int tm_number;				//��һ�������е�TM������
	int tm_size;				//��һ�������е�TM���С
	int frame_lenght;			//��һ�������е�֡��
	int frame_header_length;	//��һ�������е�֡ͷ��
	int task_number;			//��һ�����ݵ������
	int record;					//��һ�����ݵļ�¼�κ�
	int retention2[7];			//����ֵ
};

struct DataQuery_0_Response		//3.5.2 �����㼶�����б��ѯ��Ӧ
{
	MsgHeader header_0;			//��Ϣͷ
	int id;						//ģ��ID
	int request_id;				//������
	int retention1[3];			//����ֵ
	int list_number;			//��ѯ���б�����
	/*
	������ݣ����Data_0�ṹ�壩
	��Ϣβ
	*/
};
//����ָ��

struct DataRecv					//3.6.1 ���ݽ���ָ�� length = 256
{
	MsgHeader header_0;			//��Ϣͷ
	int port;					//ͨ����
	int request_id;				//������ 4��ʵʱ���ݽ��� 3���º����ݽ���
	int requirement;			//��ѯ������ͨ������bitλ�õ�int��
	wchar_t satellite[20];		//������
	int time_begin[2];			//���յ����ݵĿ�ʼʱ��
	int time_begin_years;		//���յ����ݵĿ�ʼ���
	int time_end[2];			//���յ����ݵĽ���ʱ��
	int time_end_years;			//���յ����ݵĽ������
	int range_begin;			//Ҫ���յĵ���Χ��ʼֵ
	int range_end;				//Ҫ���յĵ���Χ����ֵ
	int retention[39];			//����ֵ
	int end = -1234567890;		//��Ϣβ
};

struct DataRecvFaile_Response	//3.6.2 ����ʧ����Ӧ length = 24
{
	MsgHeader header_0;			//��Ϣͷ,���ȵ���24
	int id = 0xFFFFFFFF;		//��ʶ�� -1
	int error_code;				//������
	int end = -1234567890;		//��Ϣβ
};

struct DataRecv_RT_Response_1		//3.6.3 ʵʱ���ݽ�����Ӧ-1  length = 80;
{
	MsgHeader header_0;			//��Ϣͷ,���ȵ���24
	int id = 0xEEEEEEE1;		//��ʶ��
	wchar_t satellite[20];		//������
	int trace = 1;				//���Ǹ���׼��
	int retention[4];			//����ֵ
	int end = -1234567890;		//��Ϣβ
};

struct DataRecv_RT_Response_2		//3.6.4 ʵʱ���ݽ�����Ӧ-2  length = 80;
{
	MsgHeader header_0;			//��Ϣͷ,���ȵ���24
	int id = 0xEEEEEEE2;		//��ʶ��
	wchar_t satellite[20];		//������
	int trace = 2;				//���Ǹ���׼��
	int retention[4];			//����ֵ
	int end = -1234567890;		//��Ϣβ
};

struct DataRecv_RT_Response_3		//3.6.5 ʵʱ���ݽ�����Ӧ-3  length = 80;
{
	MsgHeader header_0;			//��Ϣͷ
	int id = 0xEEEEEEE3;		//��ʶ��
	wchar_t satellite[20];		//������
	int trace = 3;				//���Ǹ���׼��
	int retention[4];			//����ֵ
	int end = -1234567890;		//��Ϣβ
};

struct DataRecv_RT_Response_4		//3.6.6 ʵʱ���ݽ�����Ӧ-4
{
	MsgHeader header_0;			//��Ϣͷ
	int id = 0xEEEEEEE4;		//��ʶ��
	wchar_t satellite[20];		//������
	int frame_header_length;	//֡ͷ��
	int frame_lenght;			//֡��
	int timeblock_length;		//ʱ��������
	int tm_stateblock_length;	//TM��״̬������
	int tm_length;				//TM�鳤��
	int tm_number;				//TM����
	int tm_header_length = 0;	//TM�ļ�ͷ����(��֪��Ϊʲô����Ϊ0)
	/*
	����
	���TM���ݽṹ��
	��Ϣβ
	*/

};

struct TMBlock					//���ĵ�������N��ʼ
{
	int	lastdata;				//���<=8�ֽ�����+���ܴ��ڵ����������
	int tm_time;				//TM��ʱ��
	int tm_state;				//TM��״̬
	int retention;				//����ֵ

};

struct DataRecv_RT_Response_5		//3.6.7 ʵʱ���ݽ�����Ӧ-5
{
	MsgHeader header_0;			//��Ϣͷ
	int id = 0xEEEEEEE5;		//��ʶ��
	wchar_t satellite[20];		//������
	int transcomple = 1;		//�������ݴ������
	int retention[4];			//����ֵ
	int end = -1234567890;		//��Ϣβ
};

struct DataRecv_AW_Response_1	//3.6.8 �º����ݽ�����Ӧ-1
{
	MsgHeader header_0;			//��Ϣͷ
	int id = 0xDDDDDDD4;		//��ʶ��
	wchar_t satellite[20];		//������
	int frame_header_length;	//֡ͷ��
	int frame_lenght;			//֡��
	int timeblock_length;		//ʱ��������
	int tm_stateblock_length;	//TM��״̬������
	int tm_length;				//TM�鳤��
	int tm_number;				//TM����
	int tm_header_length = 0;	//TM�ļ�ͷ����(��֪��Ϊʲô����Ϊ0)
	/*
	����
	���TM���ݽṹ��
	��Ϣβ
	*/
};

struct DataRecv_AW_Response_2		//3.6.7 ʵʱ���ݽ�����Ӧ-5
{
	MsgHeader header_0;		//��Ϣͷ
	int id = 0xDDDDDDD5;		//��ʶ��
	wchar_t satellite[20];		//������
	int transcomple = 5;		//�������ݴ������
	int retention[4];			//����ֵ
	int end = -1234567890;		//��Ϣβ
};

int BitSet(int a, int b, int c)//�ֱ���0��8��16bitλ
{
	std::bitset<32> temp;
	if (a == 1)
		temp.set(0);
	if (b == 1)
		temp.set(8);
	if (c == 1)
		temp.set(16);
//	std::cout << temp.to_string() << std::endl;
	int result = temp.to_ulong();

	return result;
}
