#ifndef _DEVICE_PROTOCAL_HEADER
#define _DEVICE_PROTOCAL_HEADER

#define u16 unsigned short  
#define u8  unsigned char  
#define u32 unsigned int

/************************************************************************/
////����֡���ʹ���
#define NET_CMD_CODE_CONTROL_RESTORE					0x20010002		//�ָ���������
#define NET_CMD_CODE_CONTROL_USER_NAME_AND_PASS			0x20010003		//�����û�������
#define NET_CMD_CODE_RESTART							0x20010004		//����ϵͳ
//��ѯ����
#define NET_CMD_CODE_QUERY_SYS_TYPE						0x00000003		//�豸����
#define NET_CMD_CODE_QUERY_POSITION						0x00000004		//λ����Ϣ
#define NET_CMD_CODE_QUERY_USER_NAME					0x00000005		//�û���
#define NET_CMD_CODE_QUERY_PASSWD						0x00000006		//����
#define NET_CMD_CODE_QUERY_HTTP_PORT					0x00000007		//HTTP�˿�
#define NET_CMD_CODE_QUERY_SERVER_IP					0x00000008		//������IP��ַ
#define NET_CMD_CODE_QUERY_SERVER_PORT					0x00000009		//�������˿�
#define NET_CMD_CODE_QUERY_ASIC_VERSION					0x0000000A		//�豸�汾
#define NET_CMD_CODE_QUERY_FPGA_VERSION					0x0000000B		//����汾
#define NET_CMD_CODE_QUERY_MCU_VERSION					0x0000000C		//���ư汾	
#define NET_CMD_CODE_QUERY_SYS_SN						0x0000000D		//�豸���к�
#define NET_CMD_CODE_QUERY_COMPANY						0x0000000E		//��������
#define NET_CMD_CODE_QUERY_NETWORK_TYPE					0x00001000		//��������
#define NET_CMD_CODE_QUERY_MAC							0x00001001		//MAC��ַ

#define NET_CMD_CODE_QUERY_H264_FRAME					0x00010001		//H264֡��
#define NET_CMD_CODE_QUERY_H264_RESOLUTION				0x00010002		//H264�ֱ���
#define NET_CMD_CODE_QUERY_H264_BITRATE					0x00010003		//H264����
#define NET_CMD_CODE_QUERY_H264_SHOW_TIME_STAMP			0x00010004		//H264ʱ���
#define NET_CMD_CODE_QUERY_MJPEG_FRAME					0x00011001		//MJPEG֡��
#define NET_CMD_CODE_QUERY_MJPEG_RESOLUTION				0x00011002		//MJPEG�ֱ���
#define NET_CMD_CODE_QUERY_MJPEG_BITRATE				0x00011003		//MJPEG����
#define NET_CMD_CODE_QUERY_MJPEG_SHOW_TIME_STAMP		0x00011004		//MJPEGʱ���

#define NET_CMD_CODE_QUERY_AUTOISP_ENABLE				0x00020001		//������Ӧ�Ƿ�ʹ��
#define NET_CMD_CODE_QUERY_REFERENCE					0x00020002		//��׼ֵ
#define NET_CMD_CODE_QUERY_OFFSET						0x00020003		//ƫ��ֵ
#define NET_CMD_CODE_QUERY_AUTOEXPOSURE_TIME_RANGE		0x00020004		//�Զ��ع�ʱ�䷶Χ
#define NET_CMD_CODE_QUERY_GAMMA_TABLE					0x00020005		//gamma��
#define NET_CMD_CODE_QUERY_LUMINANCE					0x00020006		//����
#define NET_CMD_CODE_QUERY_SATURATION					0x00020007		//���Ͷ�
#define NET_CMD_CODE_QUERY_CONTRAST						0x00020008		//�Աȶ�
#define NET_CMD_CODE_QUERY_BIAS							0x00020009		//ƫ��
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_ENABLE		0x0002000A		//�����Ƿ�ʹ��
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_Y			0x0002000B		//����Yǿ��
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_CB			0x0002000C		//����CBǿ��
#define NET_CMD_CODE_QUERY_NOISE_REDUCTION_CR			0x0002000D		//����CRǿ��
#define NET_CMD_CODE_QUERY_PULSE_NOISE_REDUCTION_ENABLE 0x0002000E		//��Ե��ǿ�Ƿ�ʹ��
#define NET_CMD_CODE_QUERY_EDGE_ENHANCEMENT_ENABLE		0x0002000F		//��Ե��ǿ�Ƿ�ʹ��
#define NET_CMD_CODE_QUERY_SENSITIVITY					0x00020010		//������
#define NET_CMD_CODE_QUERY_INTENSITY					0x00020011		//ǿ��
#define NET_CMD_CODE_QUERY_MANUAL_EXPOSURE_TIME			0x00020012		//�ֶ��ع�ʱ��
#define NET_CMD_CODE_QUERY_MANUAL_GAIN					0x00020013		//�ֶ�����

#define NET_CMD_CODE_QUERY_IOINPUT_INFO					0x00030001		//IO��Ϣ

#define NET_CMD_CODE_QUERY_VIDEOSHUTTERANDGAIN_INFO		0x00003001		//��ѯ��Ƶ��������
#define NET_CMD_CODE_QUERY_TRGGRABSHUTTERANDGAIN_INFO	0x00003002		//��ѯץ�Ŀ��ź�����
#define NET_CMD_CODE_QUERY_METERINGAREA_INFO			0x00003003		//��ѯ�������
#define NET_CMD_CODE_QUERY_VIDEOPARAM_INFO				0x00003004      //��ѯ��ƵԤ�����������
#define NET_CMD_CODE_QUERY_WHITEBALANCE_INFO			0x00003005		//��ѯ��ƽ�����
#define NET_CMD_CODE_QUERY_REDLIGHTENHANCED_INFO		0x00003006		//��ѯ�����ǿ����

#define NET_CMD_CODE_QUERY_SMARTCAM_OSD					0x00040001		//���ܻ�OSD��Ϣ
#define NET_CMD_CODE_QUERY_SMARTCAM_RECOG				0x00040002		//���ܻ�ʶ�������Ϣ

//��������
#define NET_CMD_CODE_SET_SYS_TYPE						0x10000003		//�豸����
#define NET_CMD_CODE_SET_POSITION						0x10000004		//λ����Ϣ
#define NET_CMD_CODE_SET_USER_NAME						0x10000005		//�û���
#define NET_CMD_CODE_SET_PASSWD							0x10000006		//����
#define NET_CMD_CODE_SET_HTTP_PORT						0x10000007		//HTTP�˿�
#define NET_CMD_CODE_SET_SERVER_IP						0x10000008		//������IP��ַ
#define NET_CMD_CODE_SET_SERVER_PORT					0x10000009		//�������˿�
#define NET_CMD_CODE_SET_CAMERA_TIME					0x1000000A		// ���ʱ��
#define NET_CMD_CODE_SET_NETWORK_TYPE					0x10001000		//��������
#define NET_CMD_CODE_SET_MAC							0x10001001		//MAC��ַ

#define NET_CMD_CODE_SET_H264_FRAME						0x10010001		//H264֡��
#define NET_CMD_CODE_SET_H264_RESOLUTION				0x10010002		//H264�ֱ���
#define NET_CMD_CODE_SET_H264_BITRATE					0x10010003		//H264����
#define NET_CMD_CODE_SET_H264_SHOW_TIME_STAMP			0x10010004		//H264ʱ���
#define NET_CMD_CODE_SET_MJPEG_FRAME					0x10011001		//MJPEG֡��
#define NET_CMD_CODE_SET_MJPEG_RESOLUTION				0x10011002		//MJPEG�ֱ���
#define NET_CMD_CODE_SET_MJPEG_BITRATE					0x10011003		//MJPEG����
#define NET_CMD_CODE_SET_MJPEG_SHOW_TIME_STAMP			0x10011004		//MJPEGʱ���

#define NET_CMD_CODE_SET_AUTOISP_ENABLE					0x10020001		//������Ӧ�Ƿ�ʹ��
#define NET_CMD_CODE_SET_REFERENCE						0x10020002		//��׼ֵ
#define NET_CMD_CODE_SET_OFFSET							0x10020003		//ƫ��ֵ
#define NET_CMD_CODE_SET_AUTOEXPOSURE_TIME_RANGE		0x10020004		//�Զ��ع�ʱ�䷶Χ
#define NET_CMD_CODE_SET_GAMMA_TABLE					0x10020005		//gamma��
#define NET_CMD_CODE_SET_LUMINANCE						0x10020006		//����
#define NET_CMD_CODE_SET_SATURATION						0x10020007		//���Ͷ�
#define NET_CMD_CODE_SET_CONTRAST						0x10020008		//�Աȶ�
#define NET_CMD_CODE_SET_BIAS							0x10020009		//ƫ��
#define NET_CMD_CODE_SET_NOISE_REDUCTION_ENABLE			0x1002000A		//�����Ƿ�ʹ��
#define NET_CMD_CODE_SET_NOISE_REDUCTION_Y				0x1002000B		//����Yǿ��
#define NET_CMD_CODE_SET_NOISE_REDUCTION_CB				0x1002000C		//����CBǿ��
#define NET_CMD_CODE_SET_NOISE_REDUCTION_CR				0x1002000D		//����CRǿ��
#define NET_CMD_CODE_SET_PULSE_NOISE_REDUCTION_ENABLE	0x1002000E		//��Ե��ǿ�Ƿ�ʹ��
#define NET_CMD_CODE_SET_EDGE_ENHANCEMENT_ENABLE		0x1002000F		//��Ե��ǿ�Ƿ�ʹ��
#define NET_CMD_CODE_SET_SENSITIVITY					0x10020010		//������
#define NET_CMD_CODE_SET_INTENSITY						0x10020011		//ǿ��
#define NET_CMD_CODE_SET_MANUAL_EXPOSURE_TIME			0x10020012		//�ֶ��ع�ʱ��
#define NET_CMD_CODE_SET_MANUAL_GAIN					0x10020013		//�ֶ�����

#define NET_CMD_CODE_SET_IOINPUT_INFO					0x10030001		//��������IO��Ϣ

#define NET_CMD_CODE_SET_VIDEOSHUTTERANDGAIN_INFO		0x10003001		//������Ƶ��������
#define NET_CMD_CODE_SET_TRGGRABSHUTTERANDGAIN_INFO		0x10003002		//����ץ�Ŀ��ź�����
#define NET_CMD_CODE_SET_METERINGAREA_INFO				0x10003003		//���ò������
#define NET_CMD_CODE_SET_VIDEOPARAM_INFO				0x10003004      //������ƵԤ�����������
#define NET_CMD_CODE_SET_WHITEBALANCE_INFO			    0x10003005		//���ð�ƽ�����
#define NET_CMD_CODE_SET_REDLIGHTENHANCED_INFO			0x10003006		//���ú����ǿ����


//������Ƶ��������
#define NET_CMD_CODE_SET_VIDEOGENERALPARAM_INFO        0x10003007
//��ѯ��Ƶ��������
#define NET_CMD_CODE_GET_VIDEOGENERALPARAM_INFO        0x00003007

/***********************************************************************************/
// ��������
typedef struct
{
	u16 uSnapGain;			//ץ������
	u16 uSnapShutter;		//ץ�Ŀ���
	u16 uSnapInterval[4];	//ץ�ļ��
	u8 ucValidLevel;		//������ƽ��0-�͵�ƽ��1-�ߵ�ƽ
	u8 ucSnapNum;			//ץ������
	u8 ucRelevantLane;		//��������
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
	/*��Ƶ��������ʹ�� 0-�ֶ��������� 1-�Զ����ڿ������� */
	unsigned int  iVideoAutoShutterMode;
	/*��Ƶ�����Զ���������*/
	unsigned int iVideoAutoShutterMax;
	/*��Ƶ�����Զ���������*/
	unsigned int iVideoAutoShutterMin;
	/*��Ƶ�����Զ���������*/
	unsigned int iVideoAutoGainMax;
	/*��Ƶ�����Զ���������*/
	unsigned int iVideoAutoGainMin;
	/*�ֶ���Ƶ����ֵ*/
	unsigned int iVideoMulShutter;
	/*�ֶ���Ƶ����ֵ*/
	unsigned int iVideoMulGain;
	/*��ǰ��Ƶ����ֵ*/
	unsigned int iVideoAutoCurrentShutter;
	/*��ǰ��Ƶ����ֵ*/
	unsigned int iVideoAutoCurrentGain;
	/*�ع��׼ֵ*/
	unsigned int iVideoAutoRefValue;
	/*�ع�ƫ��*/
	unsigned int iVideoAutoOffset;
	/*�ع���*/
	unsigned int iVideoAutoInterVal;
	/*Ԥ��ֵ*/
	unsigned int iReserve[2];
	
}LusterVideoShutterAndGainInfStruct;

typedef struct TrgGrabShutterAndGainStruct{
	
	/*ץ�Ŀ�������ʹ�� 0-�ֶ��������� 1-�Զ����ڿ������� */	
	u32  iTrgGrabAutoShutterMode;	
	/*ץ�Ŀ����Զ���������*/	
	u32  iTrgGrabAutoShutterMax;	
	/*ץ�Ŀ����Զ���������*/	
	u32  iTrgGrabAutoShutterMin;	
	/*ץ�������Զ���������*/	
	u32  iTrgGrabAutoGainMax;	
	/*ץ�������Զ���������*/	
	u32  iTrgGrabAutoGainMin;	
	/*�ֶ�ץ�Ŀ���ֵ*/	
	u32  iTrgGrabMulShutter;	
	/*�ֶ�ץ������ֵ*/	
	u32  iTrgGrabMulGain;	
	/*Ԥ��ֵ*/	
	u32  iReserve[4];
	
}LusterTrgGrabShutterAndGainInfStruct;

typedef struct MeteringAreaStruct{
	
	/*�������ʹ�� 0-������������� 1-�����������*/	
	u32  iStartMeteringAreaMode;	
	/*��Ƶ�����Զ���������*/	
	u8  ucStartMeteringAreaValue[32];
	
} LusterMeteringAreaInfStruct;

typedef struct VideoParamStruct{
	/*��Ƶ���Ȳ��� ���ڷ�Χ-128-127*/
	int  iVideoParamBrightness;
	/*��Ƶ���ͶȲ��� ���ڷ�Χ0-255*/
	unsigned int iVideoParamSaturation;
	/*��Ƶ�ԱȶȲ��� ���ڷ�Χ-128-127*/
	int  iVideoParamContrast;
	/*��ƵMJPEGѹ�����Ӳ��� ���ڷ�Χ0-100*/
	unsigned int  iVideoParamJpegFactor;
	/*��Ƶ٤����� ���ڷ�Χ0-255*/
	unsigned int  iVideoParamGamma;
	/*��Ƶƫ�ò��� ���ڷ�Χ0-255*/
	unsigned int  iVideoParamOffset;
	/*��Ƶ����Ԥ��ֵ*/
	unsigned int  iVideoParamReserve[2];	
} LusterVideoParamInfStruct;

typedef struct WhiteBalanceStruct{
	
	/*��Ƶ���Ȳ��� ���ڷ�Χ0-255*/	
	u32  iWhiteBalanceMode;	
	/*��Ƶ�ԱȶȲ��� ���ڷ�Χ0-255*/	
	u32  iWhiteBalanceRedValue;	
	/*��ƵMJPEGѹ�����Ӳ��� ���ڷ�Χ0-255*/	
	u32  iWhiteBalanceGreenValue;	
	/*��Ƶ٤����� ���ڷ�Χ0-255*/	
	u32  iWhiteBalanceBuleValue;
	
} LusterWhiteBalanceInfStruct;

typedef struct RedLightEnhancedStruct{
	
	/*�����ǿ��ʼX����*/	
	u32  iStartX;	
	/*�����ǿ��ʼY����*/	
	u32  iStartY;	
	/*�����ǿ������*/	
	u32  iRectWidth;	
	/*�����ǿ����߶�*/	
	u32  iRectHeight;
	
} LusterRedLightEnhancedInfStruct;

typedef struct RedLightEnhancedParamStruct{
	
	/*�����ǿʹ��*/	
	u32  iRedLightEnhancedMode;	
	/*�����ǿ����*/	
	u32  iRedLightEnhancedNum;	
	/*�����ǿ����*/	
	u32  iRedLightEnhancedFactor;	
	/*�����ǿ����*/	
	LusterRedLightEnhancedInfStruct  redLightEnhancedRect[4];
	
} LusterRedLightEnhancedParamInfStruct;

typedef struct VideoGeneralParamStruct{
	/*��Ƶ���Žṹ��*/
	LusterVideoShutterAndGainInfStruct  videoShutterAndGainStruct;
	/*ͼ���������*/
	LusterVideoParamInfStruct  videoParamInfStruct;
}LusterVideoGeneralParamStruct;


/*************************************************************************************************/
BOOL __declspec(dllexport) IDVR_InitProtocalHandle(HANDLE *hChanHandle,char* TargetAddr, int Port,DWORD *dwReserve1 );
BOOL __declspec(dllexport) IDVR_ReleaseProtocalHandle(HANDLE* hChanHandle);
BOOL __declspec(dllexport) IDVR_SendCommand(HANDLE hChanHandle, DWORD CommandType, void* pvalue);
/*************************************************************************************************/

#endif