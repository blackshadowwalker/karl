#ifndef _COMMON_HEADER
#define _COMMON_HEADER

#include "protocal.h"
#include "snap.h"


#define VIDEO_DISCONNECT 0x0001
#define VIDEO_START 0x0002
#define VIDEO_CONNECT 0x0003
#define VIDEO_FAIL 0x0004
#define DECODE_FAIL 0x0005
#define DISCOVER 			0x01
#define SET_IPADDR			0x02
#define RESPONSE_ACK0_OK	0x10
#define RESPONSE_ACK1_OK	0x11
#define RESPONSE_ACK0_FAIL	0xf0
#define RESPONSE_ACK1_FAIL	0xf1
#define RESPONSE_CMD_FAIL	0xff
#define AD_ID				0xff0616 



struct Device 
{
	unsigned long id;
	unsigned long cmd;			// 0x01-discovery, 0x02-set ipaddr, 0x10-response_ok, 0xff-response-fail
	unsigned char chaddr[6];
	unsigned char shaddr[6];
	unsigned long ciaddr;
	unsigned long siaddr;
	unsigned long smask;
	unsigned long sgateway;
	char smode[8];
	char sn[32];
	char location[64];
};


enum StreamType
{
	H264,  
	MPGE4, 
	MJPG, 
	MP4A,
	UnKnown
};

enum RtspStatus
{
	RTSP_STOP,   //结束线程
	RTSP_START,  //开始线程
	RTSP_CONNECT, //连接成功
	RTSP_UNCONNECT, //连接失败
	RTSP_RECONNECT, //重连事件
	RTSP_BUFFERIN //数据进入
};

enum RecordStatus
{
    INVALID_VALUE, //参数地址无效
	DEVICE_ONLINE, //数据连接失败
	DEVICE_OFFLINE,
	RECORD_IDLE, //空闲当中
	RECORD_ON,   //录像当中
	RECORD_OFF   //录像任务结束
};

struct RECORD_TIME_INFO
{
	DWORD nYear;
	DWORD nMonth;
	DWORD nDay;
	DWORD nHour;
	DWORD nMinute;
	DWORD nSecond;
	RECORD_TIME_INFO()
	{
		nYear = 0;
		nMonth = 0;
		nDay = 0;
		nHour = 0;
        nMinute = 0;
		nMinute = 0;
		nSecond = 0;
	}
};


typedef void (*RtspCallBack)(LPVOID lpobj,enum RtspStatus status);
typedef void (*RecordCallBack)(LPVOID lpobj,enum RecordStatus status);
typedef void (*DecoderHandle)(LPVOID lpobj,unsigned char* rgb24,int outSize,int width,int height);
typedef void (*VideoMessageBack)(LPVOID lpobj,WORD errorCode,char* Message);
typedef void (*VideoInfoBack)(LPVOID lpobj,StreamType Type,int Width, int Height);
typedef void (*DeviceDiscovery)(LPVOID mObj,Device* mDevice);

// 视频预览函数
__declspec(dllexport) BOOL IDVR_StartDevicePreview(HWND hWnd,HANDLE *hChanHandle,char* TargetAddr, DWORD *dwReserve1);
__declspec(dllexport) BOOL IDVR_StopDevicePreview(HANDLE hChanHandle);
__declspec(dllexport) BOOL IDVR_DeviceRefresh(HANDLE hChanHandle);
 __declspec(dllexport) BOOL IDVR_CaptureDeviceBuffer(HANDLE hChanHandle,BYTE** csBuffer, DWORD *dwReserve1);
__declspec(dllexport) BOOL IDVR_CaptureDevicePicture(HANDLE hChanHandle,char* csFileName, DWORD *dwReserve1);
__declspec(dllexport) BOOL IDVR_VideoInfo(LPVOID lpobj, VideoInfoBack Info,VideoMessageBack Message,HANDLE hChanHandle);
__declspec(dllexport) BOOL IDVR_StartDeviceRecord(HANDLE hChanHandle,char* csFileName, DWORD *dwReserve1);
__declspec(dllexport) BOOL IDVR_GetDeviceState(HANDLE hChanHandle,int* iState);
__declspec(dllexport) BOOL IDVR_StopDeviceRecord(HANDLE hChanHandle);

// 设备连接函数
__declspec(dllexport) BOOL IDVR_ConnectServer(char* TargetAddr, void **VbufHandle, void **AbufHandle, HANDLE *hRtspHandle,BOOL Record, DWORD *dwReserve1);
__declspec(dllexport) BOOL IDVR_DisConnectServer(HANDLE handle);
__declspec(dllexport) BOOL IDVR_ReConnect(HANDLE handle);
__declspec(dllexport) BOOL IDVR_StartServer(HANDLE handle);
__declspec(dllexport) BOOL IDVR_ServerStatus(LPVOID lpobj,RtspCallBack callback,HANDLE handle);
__declspec(dllexport) BOOL IDVR_StartServerRecord(HANDLE RtspHandle,char* csFileName);
__declspec(dllexport) void IDVR_StopServerRecord(HANDLE RtspHandle);
__declspec(dllexport) bool IDVR_GetServerRecordState(HANDLE RtspHandle);


__declspec(dllexport) BOOL IDVR_StartDeviceRecord(HANDLE *hChanHandle,char* TargetAddr, DWORD *dwReserve1);
__declspec(dllexport) void IDVR_SetCallBack(HANDLE hChanHandle,RecordCallBack hCallBack ,LPVOID hObj);
__declspec(dllexport) void IDVR_StartRecord(HANDLE hChanHandle);
__declspec(dllexport) void IDVR_StopRecord(HANDLE hChanHandle);
__declspec(dllexport) void IDVR_SetRecord(HANDLE hChanHandle,RECORD_TIME_INFO* struStartTime,RECORD_TIME_INFO* struEndTime,char* RecordPath,long TimeSpan,long FileSize);
__declspec(dllexport) void IDVR_CloseRecord(HANDLE hChanHandle);


// 设备搜索函数
BOOL __declspec(dllexport) IDVR_StartDeviceDiscovery(HANDLE *hChanHandle,DeviceDiscovery Discovery,LPVOID Obj, int Port);
BOOL __declspec(dllexport) IDVR_SetDeviceDiscovery(HANDLE hChanHandle,Device* mDevice);
void __declspec(dllexport) IDVR_StopDeviceDiscovery(HANDLE hChanHandle);

// 图像采集
BOOL __declspec(dllexport) IDECODER_SetDecoder(HANDLE *hChanHandle,char* TargetAddr, DWORD *dwReserve1);
BOOL __declspec(dllexport) IDECODER_SetCallBack(HANDLE hChanHandle,LPVOID hObj,DecoderHandle hDecoder,VideoMessageBack hMessage);
BOOL __declspec(dllexport) IDECODER_Start(HANDLE hChanHandle);
BOOL __declspec(dllexport) IDECODER_Buffer(HANDLE hChanHandle,unsigned char* buf, int* length, int* width, int* height);
BOOL __declspec(dllexport) IDECODER_GetJpg(HANDLE hChanHandle,unsigned char* RecvBuf, int* RecvLen, struct timeval* presentationTime=NULL);
BOOL __declspec(dllexport) IDECODER_Stop(HANDLE hChanHandle);

///////////////////////////////////////////////////////////////////////////
#endif