
#include <bitset>   
struct MsgHeader				//信息头  12byte
{
	int begin = 1234567890;		//消息开始
	int length;					//消息长度（包含信息头和信息尾）
	int id;						//流标识
};

int end = -1234567890;			//消息尾

struct InvalidInstruction		//无效指令响应	20byte
{
	MsgHeader header_0;			//消息头
	int message = -1;			//无效指令信息

	int end = -1234567890;		//消息尾
};

struct RefuseInstuction			//拒收响应
{
	MsgHeader header_0;			//消息头

	int message = -2;			//无效指令信息

	int end = -1234567890;		//消息尾
};
//控制指令
struct DataQuery_0				//3.5.1 本地零级数据列表查询指令,共128个字节
{
	MsgHeader header_0;			//消息头
	int id;						//模块ID
	int request_id;				//请求码
	int requirement;			//查询条件（通过设置bit位得到int）
	wchar_t satellite[20];		//卫星名
	int time_begin[2];			//接收的数据的开始时间
	int time_begin_years;		//接收的数据的开始年份
	int time_end[2];			//接收的数据的结束时间
	int time_end_years;			//接收的数据的结束年份
	int range_begin;			//要接收的地域范围开始值
	int range_end;				//要接收的地域范围结束值
	int list_max;				//查询的最大列表数量(1-100)
	int retention[6];			//保留值
	int end = -1234567890;		//消息尾
};

struct Data_0
{
	wchar_t satellite[20];		//第一个数据的卫星名
	int time_begin[2];			//第一个数据的开始时间
	int time_begin_years;		//第一个数据的开始年份
	int time_end[2];			//第一个数据的结束时间
	int time_end_years;			//第一个数据的结束年份
	int range_begin;			//第一个数据的地域范围开始值
	int range_end;				//第一个数据的地域范围结束值
	float data_size;			//第一个数据的数据量
	int tm_number;				//第一个数据中的TM块数量
	int tm_size;				//第一个数据中的TM块大小
	int frame_lenght;			//第一个数据中的帧长
	int frame_header_length;	//第一个数据中的帧头长
	int task_number;			//第一个数据的任务号
	int record;					//第一个数据的记录段号
	int retention2[7];			//保留值
};

struct DataQuery_0_Response		//3.5.2 本地零级数据列表查询响应
{
	MsgHeader header_0;			//消息头
	int id;						//模块ID
	int request_id;				//请求码
	int retention1[3];			//保留值
	int list_number;			//查询到列表数量
	/*
	多个数据（多个Data_0结构体）
	消息尾
	*/
};
//控制指令

struct DataRecv					//3.6.1 数据接收指令 length = 256
{
	MsgHeader header_0;			//消息头
	int port;					//通道号
	int request_id;				//请求码 4：实时数据接收 3：事后数据接收
	int requirement;			//查询条件（通过设置bit位得到int）
	wchar_t satellite[20];		//卫星名
	int time_begin[2];			//接收的数据的开始时间
	int time_begin_years;		//接收的数据的开始年份
	int time_end[2];			//接收的数据的结束时间
	int time_end_years;			//接收的数据的结束年份
	int range_begin;			//要接收的地域范围开始值
	int range_end;				//要接收的地域范围结束值
	int retention[39];			//保留值
	int end = -1234567890;		//消息尾
};

struct DataRecvFaile_Response	//3.6.2 接收失败响应 length = 24
{
	MsgHeader header_0;			//消息头,长度等于24
	int id = 0xFFFFFFFF;		//标识号 -1
	int error_code;				//错误码
	int end = -1234567890;		//消息尾
};

struct DataRecv_RT_Response_1		//3.6.3 实时数据接收响应-1  length = 80;
{
	MsgHeader header_0;			//消息头,长度等于24
	int id = 0xEEEEEEE1;		//标识号
	wchar_t satellite[20];		//卫星名
	int trace = 1;				//卫星跟踪准备
	int retention[4];			//保留值
	int end = -1234567890;		//消息尾
};

struct DataRecv_RT_Response_2		//3.6.4 实时数据接收响应-2  length = 80;
{
	MsgHeader header_0;			//消息头,长度等于24
	int id = 0xEEEEEEE2;		//标识号
	wchar_t satellite[20];		//卫星名
	int trace = 2;				//卫星跟踪准备
	int retention[4];			//保留值
	int end = -1234567890;		//消息尾
};

struct DataRecv_RT_Response_3		//3.6.5 实时数据接收响应-3  length = 80;
{
	MsgHeader header_0;			//消息头
	int id = 0xEEEEEEE3;		//标识号
	wchar_t satellite[20];		//卫星名
	int trace = 3;				//卫星跟踪准备
	int retention[4];			//保留值
	int end = -1234567890;		//消息尾
};

struct DataRecv_RT_Response_4		//3.6.6 实时数据接收响应-4
{
	MsgHeader header_0;			//消息头
	int id = 0xEEEEEEE4;		//标识号
	wchar_t satellite[20];		//卫星名
	int frame_header_length;	//帧头长
	int frame_lenght;			//帧长
	int timeblock_length;		//时间区长度
	int tm_stateblock_length;	//TM块状态区长度
	int tm_length;				//TM块长度
	int tm_number;				//TM块数
	int tm_header_length = 0;	//TM文件头长度(不知道为什么定义为0)
	/*
	保留
	多个TM数据结构体
	消息尾
	*/

};

struct TMBlock					//从文档描述的N开始
{
	int	lastdata;				//最后<=8字节数据+可能存在的零填充数据
	int tm_time;				//TM块时间
	int tm_state;				//TM块状态
	int retention;				//保留值

};

struct DataRecv_RT_Response_5		//3.6.7 实时数据接收响应-5
{
	MsgHeader header_0;			//消息头
	int id = 0xEEEEEEE5;		//标识号
	wchar_t satellite[20];		//卫星名
	int transcomple = 1;		//卫星数据传输完成
	int retention[4];			//保留值
	int end = -1234567890;		//消息尾
};

struct DataRecv_AW_Response_1	//3.6.8 事后数据接收响应-1
{
	MsgHeader header_0;			//消息头
	int id = 0xDDDDDDD4;		//标识号
	wchar_t satellite[20];		//卫星名
	int frame_header_length;	//帧头长
	int frame_lenght;			//帧长
	int timeblock_length;		//时间区长度
	int tm_stateblock_length;	//TM块状态区长度
	int tm_length;				//TM块长度
	int tm_number;				//TM块数
	int tm_header_length = 0;	//TM文件头长度(不知道为什么定义为0)
	/*
	保留
	多个TM数据结构体
	消息尾
	*/
};

struct DataRecv_AW_Response_2		//3.6.7 实时数据接收响应-5
{
	MsgHeader header_0;		//消息头
	int id = 0xDDDDDDD5;		//标识号
	wchar_t satellite[20];		//卫星名
	int transcomple = 5;		//卫星数据传输完成
	int retention[4];			//保留值
	int end = -1234567890;		//消息尾
};

int BitSet(int a, int b, int c)//分别是0，8，16bit位
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
