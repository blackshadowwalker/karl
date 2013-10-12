#if !defined(_COMMON_HEADER_INCLUDED)
#define _COMMON_HEADER_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// 定义信息结构体,用于请求命令
#define IP_LENGTH 16
#define SN_LENGTH 16
typedef struct
{
	UINT32 dwPicNum;    // 抓拍张数
	UINT32 dwPicWidth;  // 图像宽度
	UINT32 dwPicHeight; // 图像高度
	char ip[IP_LENGTH];    // 相机IP
	char sn[SN_LENGTH];    // 相机sn
	UINT32 dwPicType;    // 0-jpeg, 1-bmp, 2-raw
	UINT32 dwProtocol;   // 传输协议，0-Tcp,1-Udp

}PicInfo;



// 数据帧结构定义
#define FRAME_PIC_DATA_LENGTH 1024
typedef struct
{
	UINT32 dwType;   // 帧类型
	UINT32 FrameNum; // 帧编号
	UINT32 packetNum; // 包编号
	UINT32 picLength; // 图像长度
	UINT32 bStop;     // 停止位
	UINT32 timestamp; // 时间戳
	UINT32 dwDataLength;   // 当前包有效数据长度
	UINT32 dwCheck;   // 校验位
	BYTE   bpicData[FRAME_PIC_DATA_LENGTH]; // 帧数据

}tagDataFrame;


// 软触发返回的命令信息
typedef struct soft_trigger_packet
{
	unsigned int id;					// id = 0x20120216
	unsigned char avsend_ipaddr[16];	// 本地ip地址
	unsigned int avsend_port;			// 本地端口号
	char*        error_code;			// 错误代码
	DWORD		dwTrigSrc;
	DWORD		dwLamp;
	
}SoftCmdPacket;


// 命令帧结构
typedef struct
{
	UINT32 dwType;    // 帧类型；
	BYTE   bData[1024]; // 帧数据
}tagCMDFrame;

#define PICDATA    0x00000000  // 数据帧类型
#define REQUEST    0x00001000  // 请求命令帧
#define ACK		   0x00002000  // 应答命令帧,保留
#define START      0x00003000  // 传输命令帧

typedef LPVOID HANDLE;
typedef void (*StateInfo)(LPVOID lpObj, char* Message);

// 软触发命令函数
/*
	函数名称: SendSoftTrigge

	参数	: cameraIP	  - 相机IP地址
			  svrIP		  - 本地主机地址
			  port        - 本地端口号
			  pCmdInfo    - 返回抓拍的信息
	
	函数描述: 该函数完成软触发工作，SoftCmdPacket结构体返回抓拍的错误代码
	          如果相机在2s中内，没有收到反馈则相机中断，SoftCmdPacket::id = 0xFFFFFFFF
			  如果正常完成抓拍，SoftCmdPacket::error_code = "0"
			  如果抓拍失败，    SoftCmdPacket::error_code返回错误代码
			  "0" - 软触发成功
			  "1" - 软触发失败
			  "2" - ID错误，此情况认为是无效报文直接丢弃而不回复
			  "3" - 相机中的发送抓拍图片的目的ip地址错误
			  "4" - 相机中的发送抓拍图片的目的端口错误
			  "5" - 相机没有设置I/O输入输出状态 
			  "6" - 相机I/O没有关联 
			  "7" - 相机没有设置软触发关联
    举例:	  相机中ip地址错误，并且端口错误，但没有其他错误，就会在回复报文中将error_code填充为“34”，
	          如果相机存在ip地址错误，端口错误，没有设置软触发关联三个错误，就会在回复报文中将error_code字段填充为“347”。
			  以此类推.		
			  
    返回值：   -1: 无法得到客户端socket
				0: 相机连接失败
				1: 操作成功，但不一定完成抓拍，抓拍信息在SoftCmdPacket结构体
*/

bool __declspec(dllexport) SendSoftTrigge(char* cameraIP, char* svrIP, int port, SoftCmdPacket* pCmdInfo);

/*
	函数名称: InitSrv

	参数	: pSnapHandle - 抓拍句柄,在函数内部赋值
			  port		  - 本地端口号
	
	函数描述: 在抓拍时该函数第一个被调用，该函数用来初始化抓拍库
*/
bool __declspec(dllexport) InitSrv(HANDLE* pSnapHandle, int port = 64000);
/*
	函数名称: StartSrvSnap

	参数	: pSnapHandle - 抓拍句柄,在函数内部赋值

    返回值  : true:成功，false: 失败 
	
	函数描述: 启动抓拍线程
*/
bool __declspec(dllexport) StartSrvSnap(HANDLE pSnapHandle);
/*
	函数名称: SetCallBackInfo

	参数	: pSnapHandle - 抓拍句柄,在函数内部赋值			  
			  lpObj		  - 调用对象指针
			  snapInfo    - 回调函数，抓拍状态信息, snapInfo = NULL不设置回调函数

    返回值  : true:成功，false:失败
	
	函数描述: 该函数用来注册回调函数，回调函数返回抓拍信息
*/

bool __declspec(dllexport) SetCallBackInfo(HANDLE pSnapHandle, LPVOID lpObj, StateInfo snapInfo);

/*
	函数名称: GetSnapPicInfo

	参数	: pSnapHandle - 抓拍句柄,在函数内部赋值			  
			  pPicInfo	  - 抓拍图像信息结构体

    返回值  : true:成功，false: 失败
			  
	
	函数描述: 该函数得到抓拍信息
*/


bool __declspec(dllexport) GetSnapPicInfo(HANDLE pSnapHandle, PicInfo* pPicInfo);
/*
   函数名称; GetSnapBuffer

   函数功能: 获取抓拍图像的指针
   
	 参数:	  pSnapHandle- 抓拍句柄，在初始化函数中赋值
			  pSave      - 由用户分配
			  lenght[out]- 抓拍的图像长度	
			  timestamp  - 抓拍图像时间戳
			  pCamBuf	 - 与相机ip对应的指针，用户在SetSnapBuffer函数中分配
			  
	函数描述: 获取抓拍的图像
		 
	返回值：-1:入口指针错误
			 0:没有图像
			 1:获取图像
*/
int __declspec(dllexport) GetSnapBuffer(HANDLE pSnapHandle, 
										 BYTE* pSave, 
										 int* length/*图像长度*/, 
										 UINT32* timestamp, /*时间戳*/
										 void* pCamBuf);  /*相机ip对应的缓冲区地址*/

/*
	函数名称: SetSnapBuffer

	参数	: pSnapHandle - 抓拍句柄，在初始化函数InitSrv中分配
			  IP          - 相机IP地址
			  pBuffer     - 与该IP对应的FIFO缓冲区地址，在函数内部分配
*/
bool __declspec(dllexport)  SetSnapBuffer(HANDLE pSnapHandle, char* IP, void** pBuffer);
/*
	函数名称: SetSnapBuffer

    函数功能: 分配抓拍图像接收缓冲区

	参数	: pSnapHandle - 抓拍句柄，在初始化函数InitSrv中分配
			  pTransBuffer[out]- FIFO缓冲区地址，在函数内部分配
	返回值  : 
	          True:操作成功，False:操作失败
	修改时间: 2012/06/14
*/
bool __declspec(dllexport)  SetSnapBuffer(HANDLE pSnapHandle, void** pTransBuffer);
/*
	函数名称: ReleaseAllBind

    函数功能: 解除所有相机IP和内存地址的绑定

	参数	: pSnapHandle - 抓拍句柄，在初始化函数InitSrv中分配
			  
	返回值  : 
	          True:操作成功，False:操作失败

	修改时间:  新增 2012/06/14
*/

bool __declspec(dllexport)  ReleaseAllBind(HANDLE pSnapHandle);

/*
	函数名称: SetSnapPort

	参数	: pSnapHandle - 抓拍句柄,在函数内部赋值			  

			  port        - 抓拍端口号 

    返回值  : true:成功，false:失败
	
	函数描述: 设置相机抓拍端口号

    修改时间: 2012/06/19
*/
bool __declspec(dllexport) SetSnapPort(HANDLE pSnapHandle, int port);

/*
	函数名称: BindIPToBuffer

    函数功能: 绑定相机IP地址和内存地址，用户可以获取指定IP相机抓拍的图像

	参数	: pSnapHandle - 抓拍句柄，在初始化函数InitSrv中分配
			  IP          - 相机IP地址
			  pBuffer     - 与该IP对应的FIFO缓冲区地址，由SetSnapBuffer函数分配
	返回值  :
		      True:绑定成功, False:绑定失败
	修改时间: 新增 2012/06/14
*/
bool __declspec(dllexport) BindIPToBuffer(HANDLE pSnapHandle, char* IP, void* pBuffer);

/*
	函数名称: ReleaseFIFOBuffer

	参数	: pSnapHandle - 抓拍句柄，在初始化函数InitSrv中分配
			  
			  pBuf        - 与该IP对应的FIFO缓冲区地址，释放该内存

    返回值  : true:成功，false: 失败

    修改时间: 新增 2012/06/15
*/
bool __declspec(dllexport) ReleaseFIFOBuffer(HANDLE pSnapHandle, void** pBuf);

/*
	函数名称: ReleaseFIFOBuffer

    函数功能: 释放抓拍句柄pSnapHandle

	参数	: pSnapHandle - 抓拍句柄，在初始化函数InitSrv中分配
			  
    返回值  : 无

	修改时间: 新增 2012/06/15
*/
void __declspec(dllexport) ReleaseSnapHandle(HANDLE pSnapHandle);

/*
	函数名称: StopSrvSnap

	参数	: pSnapHandle - 抓拍句柄

    返回值  : true:成功，false: 失败 
	
	函数描述: 停止抓拍线程，断开socket连接
	
	修改时间: 新增 2012/06/18
*/
bool __declspec(dllexport) StopSrvSnap(HANDLE pSnapHandle);

//////////////////////////////////////////////////软触发命令/////////////////////////////////

/*
	函数名称: InitSoftTrig

    函数功能: 初始化

	参数	: pCmdHandle - 创建触发命令句柄			 

    返回值  : true:成功，false: 失败
*/
bool __declspec(dllexport) InitSoftTrig(HANDLE* pCmdHandle);

/*
	函数名称: SendSoftTrigge

    函数功能: 发送软触发命令

	参数	: pCmdHandle - 触发命令句柄	
			  cameraIP   - 相机IP地址
			  svrIP      - 本地服务器地址
			  port       - 本地抓拍端口
			  pCmdInfo   - 触发命令结构体

    返回值  : true:成功，false: 失败

    修改时间: 更新 2012/06/15
*/
bool __declspec(dllexport) SendSoftTrigge(HANDLE pCmdHandle, 
										  char* cameraIP, 
										  char* svrIP, 
										  int port, 
										  SoftCmdPacket* pCmdInfo);
/*
	函数名称: ReleaseCmdHandle

    函数功能: 释放触发命令句柄

	参数	: pCmdHandle - 触发命令句柄	

    返回值  : true:成功，false: 失败

    修改时间: 新增 2012/06/15
*/
bool __declspec(dllexport) ReleaseCmdHandle(HANDLE pCmdHandle);



#endif




















