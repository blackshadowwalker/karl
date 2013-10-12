#ifndef _DEVICE_PROTOCAL_HEADER
#define _DEVICE_PROTOCAL_HEADER

#define u16 unsigned short  
#define u8  unsigned char  
#define u32 unsigned int

/************************************************************************/
////命令帧类型代码
#define NET_CMD_CODE_CONTROL_RESTORE					0x20010002		//恢复出厂设置
#define NET_CMD_CODE_CONTROL_USER_NAME_AND_PASS			0x20010003		//设置用户和密码
#define NET_CMD_CODE_RESTART							0x20010004		//重启系统
//查询命令
#define NET_CMD_CODE_QUERY_SYS_TYPE						0x00000003		//设备类型
#define NET_CMD_CODE_QUERY_POSITION						0x00000004		//位置信息
#define NET_CMD_CODE_QUERY_USER_NAME					0x00000005		//用户名
#define NET_CMD_CODE_QUERY_PASSWD						0x00000006		//密码
#define NET_CMD_CODE_QUERY_HTTP_PORT					0x00000007		//HTTP端口
#define NET_CMD_CODE_QUERY_SERVER_IP					0x00000008		//服务器IP地址
#define NET_CMD_CODE_QUERY_SERVER_PORT					0x00000009		//服务器端口
#define NET_CMD_CODE_QUERY_ASIC_VERSION					0x0000000A		//设备版本
#define NET_CMD_CODE_QUERY_FPGA_VERSION					0x0000000B		//成像版本
#define NET_CMD_CODE_QUERY_MCU_VERSION					0x0000000C		//控制版本	
#define NET_CMD_CODE_QUERY_SYS_SN						0x0000000D		//设备序列号
#define NET_CMD_CODE_QUERY_COMPANY						0x0000000E		//生产厂家
#define NET_CMD_CODE_QUERY_NETWORK_TYPE					0x00001000		//网络类型
#define NET_CMD_CODE_QUERY_MAC							0x00001001		//MAC地址

#define NET_CMD_CODE_QUERY_H264_FRAME					0x00010001		//H264帧率
#define NET_CMD_CODE_QUERY_H264_RESOLUTION				0x00010002		//H264分辨率
#define NET_CMD_CODE_QUERY_H264_BITRATE					0x00010003		//H264码率
#define NET_CMD_CODE_QUERY_H264_SHOW_TIME_STAMP			0x00010004		//H264时间戳
#define NET_CMD_CODE_QUERY_MJPEG_FRAME					0x00011001		//MJPEG帧率
#define NET_CMD_CODE_QUERY_MJPEG_RESOLUTION				0x00011002		//MJPEG分辨率
#define NET_CMD_CODE_QUERY_MJPEG_BITRATE				0x00011003		//MJPEG码率
#define NET_CMD_CODE_QUERY_MJPEG_SHOW_TIME_STAMP		0x00011004		//MJPEG时间戳

#define NET_CMD_CODE_QUERY_AUTOISP_ENABLE				0x00020001		//光自适应是否使能
#define NET_CMD_CODE_QUERY_REFERENCE					0x00020002		//基准值
#define NET_CMD_CODE_QUERY_OFFSET						0x00020003		//偏移值
#define NET_CMD_CODE_QUERY_AUTOEXPOSURE_TIME_RANGE		0x00020004		//自动曝光时间范围
#define NET_CMD_CODE_QUERY_GAMMA_TABLE					0x00020005		//gamma表
#define NET_CMD_CODE_QUERY_LUMINANCE					0x00020006		//亮度
#define NET_CMD_CODE_QUERY_SATURATION					0x00020007		//饱和度
#define NET_CMD_CODE_QUERY_CONTRAST						0x00020008		//对比度
#define NET_CMD_CODE_QUERY_BIAS							0x00020009		//偏置
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_ENABLE		0x0002000A		//降噪是否使能
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_Y			0x0002000B		//降噪Y强度
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_CB			0x0002000C		//降噪CB强度
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_CR			0x0002000D		//降噪CR强度
#define NET_CMD_CODE_QUERY_PULSE_NOISE_REDUCTION_ENABLE 0x0002000E		//边缘增强是否使能
#define NET_CMD_CODE_QUERY_EDGE_ENHANCEMENT_ENABLE		0x0002000F		//边缘增强是否使能
#define NET_CMD_CODE_QUERY_SENSITIVITY					0x00020010		//灵敏度
#define NET_CMD_CODE_QUERY_INTENSITY					0x00020011		//强度
#define NET_CMD_CODE_QUERY_MANUAL_EXPOSURE_TIME			0x00020012		//手动曝光时间
#define NET_CMD_CODE_QUERY_MANUAL_GAIN					0x00020013		//手动增益

#define NET_CMD_CODE_QUERY_IOINPUT_INFO					0x00030001		//IO信息

#define NET_CMD_CODE_QUERY_VIDEOSHUTTERANDGAIN_INFO		0x00003001		//查询视频快门增益
#define NET_CMD_CODE_QUERY_TRGGRABSHUTTERANDGAIN_INFO	0x00003002		//查询抓拍快门和增益
#define NET_CMD_CODE_QUERY_METERINGAREA_INFO			0x00003003		//查询测光区域
#define NET_CMD_CODE_QUERY_VIDEOPARAM_INFO				0x00003004      //查询视频预处理基本参数
#define NET_CMD_CODE_QUERY_WHITEBALANCE_INFO			0x00003005		//查询白平衡参数
#define NET_CMD_CODE_QUERY_REDLIGHTENHANCED_INFO		0x00003006		//查询红灯增强参数

#define NET_CMD_CODE_QUERY_SMARTCAM_OSD					0x00040001		//智能机OSD信息
#define NET_CMD_CODE_QUERY_SMARTCAM_RECOG				0x00040002		//智能机识别参数信息

//设置命令
#define NET_CMD_CODE_SET_SYS_TYPE						0x10000003		//设备类型
#define NET_CMD_CODE_SET_POSITION						0x10000004		//位置信息
#define NET_CMD_CODE_SET_USER_NAME						0x10000005		//用户名
#define NET_CMD_CODE_SET_PASSWD							0x10000006		//密码
#define NET_CMD_CODE_SET_HTTP_PORT						0x10000007		//HTTP端口
#define NET_CMD_CODE_SET_SERVER_IP						0x10000008		//服务器IP地址
#define NET_CMD_CODE_SET_SERVER_PORT					0x10000009		//服务器端口
#define NET_CMD_CODE_SET_CAMERA_TIME					0x1000000A		// 相机时间
#define NET_CMD_CODE_SET_NETWORK_TYPE					0x10001000		//网络类型
#define NET_CMD_CODE_SET_MAC							0x10001001		//MAC地址

#define NET_CMD_CODE_SET_H264_FRAME						0x10010001		//H264帧率
#define NET_CMD_CODE_SET_H264_RESOLUTION				0x10010002		//H264分辨率
#define NET_CMD_CODE_SET_H264_BITRATE					0x10010003		//H264码率
#define NET_CMD_CODE_SET_H264_SHOW_TIME_STAMP			0x10010004		//H264时间戳
#define NET_CMD_CODE_SET_MJPEG_FRAME					0x10011001		//MJPEG帧率
#define NET_CMD_CODE_SET_MJPEG_RESOLUTION				0x10011002		//MJPEG分辨率
#define NET_CMD_CODE_SET_MJPEG_BITRATE					0x10011003		//MJPEG码率
#define NET_CMD_CODE_SET_MJPEG_SHOW_TIME_STAMP			0x10011004		//MJPEG时间戳

#define NET_CMD_CODE_SET_AUTOISP_ENABLE					0x10020001		//光自适应是否使能
#define NET_CMD_CODE_SET_REFERENCE						0x10020002		//基准值
#define NET_CMD_CODE_SET_OFFSET							0x10020003		//偏移值
#define NET_CMD_CODE_SET_AUTOEXPOSURE_TIME_RANGE		0x10020004		//自动曝光时间范围
#define NET_CMD_CODE_SET_GAMMA_TABLE					0x10020005		//gamma表
#define NET_CMD_CODE_SET_LUMINANCE						0x10020006		//亮度
#define NET_CMD_CODE_SET_SATURATION						0x10020007		//饱和度
#define NET_CMD_CODE_SET_CONTRAST						0x10020008		//对比度
#define NET_CMD_CODE_SET_BIAS							0x10020009		//偏置
#define NET_CMD_CODE_SET_NOISE_REDUCTION_ENABLE			0x1002000A		//降噪是否使能
#define NET_CMD_CODE_SET_NOISE_REDUCTION_Y				0x1002000B		//降噪Y强度
#define NET_CMD_CODE_SET_NOISE_REDUCTION_CB				0x1002000C		//降噪CB强度
#define NET_CMD_CODE_SET_NOISE_REDUCTION_CR				0x1002000D		//降噪CR强度
#define NET_CMD_CODE_SET_PULSE_NOISE_REDUCTION_ENABLE	0x1002000E		//边缘增强是否使能
#define NET_CMD_CODE_SET_EDGE_ENHANCEMENT_ENABLE		0x1002000F		//边缘增强是否使能
#define NET_CMD_CODE_SET_SENSITIVITY					0x10020010		//灵敏度
#define NET_CMD_CODE_SET_INTENSITY						0x10020011		//强度
#define NET_CMD_CODE_SET_MANUAL_EXPOSURE_TIME			0x10020012		//手动曝光时间
#define NET_CMD_CODE_SET_MANUAL_GAIN					0x10020013		//手动增益

#define NET_CMD_CODE_SET_IOINPUT_INFO					0x10030001		//设置输入IO信息

#define NET_CMD_CODE_SET_VIDEOSHUTTERANDGAIN_INFO		0x10003001		//设置视频快门增益
#define NET_CMD_CODE_SET_TRGGRABSHUTTERANDGAIN_INFO		0x10003002		//设置抓拍快门和增益
#define NET_CMD_CODE_SET_METERINGAREA_INFO				0x10003003		//设置测光区域
#define NET_CMD_CODE_SET_VIDEOPARAM_INFO				0x10003004      //设置视频预处理基本参数
#define NET_CMD_CODE_SET_WHITEBALANCE_INFO			    0x10003005		//设置白平衡参数
#define NET_CMD_CODE_SET_REDLIGHTENHANCED_INFO			0x10003006		//设置红灯增强参数


//设置视频基本参数
#define NET_CMD_CODE_SET_VIDEOGENERALPARAM_INFO        0x10003007
//查询视频基本参数
#define NET_CMD_CODE_GET_VIDEOGENERALPARAM_INFO        0x00003007

/***********************************************************************************/
// 数据类型
typedef struct
{
	u16 uSnapGain;			//抓拍增益
	u16 uSnapShutter;		//抓拍快门
	u16 uSnapInterval[4];	//抓拍间隔
	u8 ucValidLevel;		//工作电平。0-低电平，1-高电平
	u8 ucSnapNum;			//抓拍张数
	u8 ucRelevantLane;		//关联车道
	u8 reserved[9];	
}SQ_IOInputParam;

typedef struct
{
	u8 net_mode[16];     // static, dynamic
	u8 net_ipaddr[16];
	u8 net_mask[16];
	u8 net_gateway[16];
	u8 net_dns[16];
	u8 reserved[32];
	
}SQ_NetParam;

typedef struct _SeverIP
{
	u8 IP[16];
}SQ_ServerIP;

typedef struct _SeverPort
{
	u8 Port[16];
}SQ_ServerPort;

typedef struct _tm
{  	
	int tm_sec;	
	int tm_min;	
	int tm_hour;	
	int tm_mday;	
	int tm_mon; 	
	int tm_year;	
	int tm_wday;	
	int tm_yday;	
	int tm_isdst;	
}SQ_CameraTime;

typedef struct VideoShutterAndGainStruct{
	/*视频快门增益使能 0-手动快门增益 1-自动调节快门增益 */
	unsigned int  iVideoAutoShutterMode;
	/*视频快门自动调节上限*/
	unsigned int iVideoAutoShutterMax;
	/*视频快门自动调节下限*/
	unsigned int iVideoAutoShutterMin;
	/*视频增益自动调节上限*/
	unsigned int iVideoAutoGainMax;
	/*视频增益自动调节下限*/
	unsigned int iVideoAutoGainMin;
	/*手动视频快门值*/
	unsigned int iVideoMulShutter;
	/*手动视频增益值*/
	unsigned int iVideoMulGain;
	/*当前视频快门值*/
	unsigned int iVideoAutoCurrentShutter;
	/*当前视频增益值*/
	unsigned int iVideoAutoCurrentGain;
	/*曝光基准值*/
	unsigned int iVideoAutoRefValue;
	/*曝光偏置*/
	unsigned int iVideoAutoOffset;
	/*曝光间隔*/
	unsigned int iVideoAutoInterVal;
	/*预留值*/
	unsigned int iReserve[2];
	
}LusterVideoShutterAndGainInfStruct;

typedef struct TrgGrabShutterAndGainStruct{
	
	/*抓拍快门增益使能 0-手动快门增益 1-自动调节快门增益 */	
	u32  iTrgGrabAutoShutterMode;	
	/*抓拍快门自动调节上限*/	
	u32  iTrgGrabAutoShutterMax;	
	/*抓拍快门自动调节下限*/	
	u32  iTrgGrabAutoShutterMin;	
	/*抓拍增益自动调节上限*/	
	u32  iTrgGrabAutoGainMax;	
	/*抓拍增益自动调节下限*/	
	u32  iTrgGrabAutoGainMin;	
	/*手动抓拍快门值*/	
	u32  iTrgGrabMulShutter;	
	/*手动抓拍增益值*/	
	u32  iTrgGrabMulGain;	
	/*预留值*/	
	u32  iReserve[4];
	
}LusterTrgGrabShutterAndGainInfStruct;

typedef struct MeteringAreaStruct{
	
	/*测光区域使能 0-不启动测光区域 1-启动测光区域*/	
	u32  iStartMeteringAreaMode;	
	/*视频快门自动调节上限*/	
	u8  ucStartMeteringAreaValue[32];
	
} LusterMeteringAreaInfStruct;

typedef struct VideoParamStruct{
	/*视频亮度参数 调节范围-128-127*/
	int  iVideoParamBrightness;
	/*视频饱和度参数 调节范围0-255*/
	unsigned int iVideoParamSaturation;
	/*视频对比度参数 调节范围-128-127*/
	int  iVideoParamContrast;
	/*视频MJPEG压缩因子参数 调节范围0-100*/
	unsigned int  iVideoParamJpegFactor;
	/*视频伽马参数 调节范围0-255*/
	unsigned int  iVideoParamGamma;
	/*视频偏置参数 调节范围0-255*/
	unsigned int  iVideoParamOffset;
	/*视频参数预留值*/
	unsigned int  iVideoParamReserve[2];	
} LusterVideoParamInfStruct;

typedef struct WhiteBalanceStruct{
	
	/*视频亮度参数 调节范围0-255*/	
	u32  iWhiteBalanceMode;	
	/*视频对比度参数 调节范围0-255*/	
	u32  iWhiteBalanceRedValue;	
	/*视频MJPEG压缩因子参数 调节范围0-255*/	
	u32  iWhiteBalanceGreenValue;	
	/*视频伽马参数 调节范围0-255*/	
	u32  iWhiteBalanceBuleValue;
	
} LusterWhiteBalanceInfStruct;

typedef struct RedLightEnhancedStruct{
	
	/*红灯增强起始X坐标*/	
	u32  iStartX;	
	/*红灯增强起始Y坐标*/	
	u32  iStartY;	
	/*红灯增强区域宽度*/	
	u32  iRectWidth;	
	/*红灯增强区域高度*/	
	u32  iRectHeight;
	
} LusterRedLightEnhancedInfStruct;

typedef struct RedLightEnhancedParamStruct{
	
	/*红灯增强使能*/	
	u32  iRedLightEnhancedMode;	
	/*红灯增强个数*/	
	u32  iRedLightEnhancedNum;	
	/*红灯增强因子*/	
	u32  iRedLightEnhancedFactor;	
	/*红灯增强区域*/	
	LusterRedLightEnhancedInfStruct  redLightEnhancedRect[4];
	
} LusterRedLightEnhancedParamInfStruct;

typedef struct VideoGeneralParamStruct{
	/*视频快门结构体*/
	LusterVideoShutterAndGainInfStruct  videoShutterAndGainStruct;
	/*图像参数调整*/
	LusterVideoParamInfStruct  videoParamInfStruct;
}LusterVideoGeneralParamStruct;


/*************************************************************************************************/
BOOL __declspec(dllexport) IDVR_InitProtocalHandle(HANDLE *hChanHandle,char* TargetAddr, int Port,DWORD *dwReserve1 );
BOOL __declspec(dllexport) IDVR_ReleaseProtocalHandle(HANDLE* hChanHandle);
BOOL __declspec(dllexport) IDVR_SendCommand(HANDLE hChanHandle, DWORD CommandType, void* pvalue);
/*************************************************************************************************/

#endif