#if !defined(_COMMON_HEADER_INCLUDED)
#define _COMMON_HEADER_INCLUDED

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// ������Ϣ�ṹ��,������������
#define IP_LENGTH 16
#define SN_LENGTH 16
typedef struct
{
	UINT32 dwPicNum;    // ץ������
	UINT32 dwPicWidth;  // ͼ����
	UINT32 dwPicHeight; // ͼ��߶�
	char ip[IP_LENGTH];    // ���IP
	char sn[SN_LENGTH];    // ���sn
	UINT32 dwPicType;    // 0-jpeg, 1-bmp, 2-raw
	UINT32 dwProtocol;   // ����Э�飬0-Tcp,1-Udp

}PicInfo;



// ����֡�ṹ����
#define FRAME_PIC_DATA_LENGTH 1024
typedef struct
{
	UINT32 dwType;   // ֡����
	UINT32 FrameNum; // ֡���
	UINT32 packetNum; // �����
	UINT32 picLength; // ͼ�񳤶�
	UINT32 bStop;     // ֹͣλ
	UINT32 timestamp; // ʱ���
	UINT32 dwDataLength;   // ��ǰ����Ч���ݳ���
	UINT32 dwCheck;   // У��λ
	BYTE   bpicData[FRAME_PIC_DATA_LENGTH]; // ֡����

}tagDataFrame;


// �������ص�������Ϣ
typedef struct soft_trigger_packet
{
	unsigned int id;					// id = 0x20120216
	unsigned char avsend_ipaddr[16];	// ����ip��ַ
	unsigned int avsend_port;			// ���ض˿ں�
	char*        error_code;			// �������
	DWORD		dwTrigSrc;
	DWORD		dwLamp;
	
}SoftCmdPacket;


// ����֡�ṹ
typedef struct
{
	UINT32 dwType;    // ֡���ͣ�
	BYTE   bData[1024]; // ֡����
}tagCMDFrame;

#define PICDATA    0x00000000  // ����֡����
#define REQUEST    0x00001000  // ��������֡
#define ACK		   0x00002000  // Ӧ������֡,����
#define START      0x00003000  // ��������֡

typedef LPVOID HANDLE;
typedef void (*StateInfo)(LPVOID lpObj, char* Message);

// ���������
/*
	��������: SendSoftTrigge

	����	: cameraIP	  - ���IP��ַ
			  svrIP		  - ����������ַ
			  port        - ���ض˿ں�
			  pCmdInfo    - ����ץ�ĵ���Ϣ
	
	��������: �ú����������������SoftCmdPacket�ṹ�巵��ץ�ĵĴ������
	          ��������2s���ڣ�û���յ�����������жϣ�SoftCmdPacket::id = 0xFFFFFFFF
			  ����������ץ�ģ�SoftCmdPacket::error_code = "0"
			  ���ץ��ʧ�ܣ�    SoftCmdPacket::error_code���ش������
			  "0" - �����ɹ�
			  "1" - ����ʧ��
			  "2" - ID���󣬴������Ϊ����Ч����ֱ�Ӷ��������ظ�
			  "3" - ����еķ���ץ��ͼƬ��Ŀ��ip��ַ����
			  "4" - ����еķ���ץ��ͼƬ��Ŀ�Ķ˿ڴ���
			  "5" - ���û������I/O�������״̬ 
			  "6" - ���I/Oû�й��� 
			  "7" - ���û��������������
    ����:	  �����ip��ַ���󣬲��Ҷ˿ڴ��󣬵�û���������󣬾ͻ��ڻظ������н�error_code���Ϊ��34����
	          ����������ip��ַ���󣬶˿ڴ���û���������������������󣬾ͻ��ڻظ������н�error_code�ֶ����Ϊ��347����
			  �Դ�����.		
			  
    ����ֵ��   -1: �޷��õ��ͻ���socket
				0: �������ʧ��
				1: �����ɹ�������һ�����ץ�ģ�ץ����Ϣ��SoftCmdPacket�ṹ��
*/

bool __declspec(dllexport) SendSoftTrigge(char* cameraIP, char* svrIP, int port, SoftCmdPacket* pCmdInfo);

/*
	��������: InitSrv

	����	: pSnapHandle - ץ�ľ��,�ں����ڲ���ֵ
			  port		  - ���ض˿ں�
	
	��������: ��ץ��ʱ�ú�����һ�������ã��ú���������ʼ��ץ�Ŀ�
*/
bool __declspec(dllexport) InitSrv(HANDLE* pSnapHandle, int port = 64000);
/*
	��������: StartSrvSnap

	����	: pSnapHandle - ץ�ľ��,�ں����ڲ���ֵ

    ����ֵ  : true:�ɹ���false: ʧ�� 
	
	��������: ����ץ���߳�
*/
bool __declspec(dllexport) StartSrvSnap(HANDLE pSnapHandle);
/*
	��������: SetCallBackInfo

	����	: pSnapHandle - ץ�ľ��,�ں����ڲ���ֵ			  
			  lpObj		  - ���ö���ָ��
			  snapInfo    - �ص�������ץ��״̬��Ϣ, snapInfo = NULL�����ûص�����

    ����ֵ  : true:�ɹ���false:ʧ��
	
	��������: �ú�������ע��ص��������ص���������ץ����Ϣ
*/

bool __declspec(dllexport) SetCallBackInfo(HANDLE pSnapHandle, LPVOID lpObj, StateInfo snapInfo);

/*
	��������: GetSnapPicInfo

	����	: pSnapHandle - ץ�ľ��,�ں����ڲ���ֵ			  
			  pPicInfo	  - ץ��ͼ����Ϣ�ṹ��

    ����ֵ  : true:�ɹ���false: ʧ��
			  
	
	��������: �ú����õ�ץ����Ϣ
*/


bool __declspec(dllexport) GetSnapPicInfo(HANDLE pSnapHandle, PicInfo* pPicInfo);
/*
   ��������; GetSnapBuffer

   ��������: ��ȡץ��ͼ���ָ��
   
	 ����:	  pSnapHandle- ץ�ľ�����ڳ�ʼ�������и�ֵ
			  pSave      - ���û�����
			  lenght[out]- ץ�ĵ�ͼ�񳤶�	
			  timestamp  - ץ��ͼ��ʱ���
			  pCamBuf	 - �����ip��Ӧ��ָ�룬�û���SetSnapBuffer�����з���
			  
	��������: ��ȡץ�ĵ�ͼ��
		 
	����ֵ��-1:���ָ�����
			 0:û��ͼ��
			 1:��ȡͼ��
*/
int __declspec(dllexport) GetSnapBuffer(HANDLE pSnapHandle, 
										 BYTE* pSave, 
										 int* length/*ͼ�񳤶�*/, 
										 UINT32* timestamp, /*ʱ���*/
										 void* pCamBuf);  /*���ip��Ӧ�Ļ�������ַ*/

/*
	��������: SetSnapBuffer

	����	: pSnapHandle - ץ�ľ�����ڳ�ʼ������InitSrv�з���
			  IP          - ���IP��ַ
			  pBuffer     - ���IP��Ӧ��FIFO��������ַ���ں����ڲ�����
*/
bool __declspec(dllexport)  SetSnapBuffer(HANDLE pSnapHandle, char* IP, void** pBuffer);
/*
	��������: SetSnapBuffer

    ��������: ����ץ��ͼ����ջ�����

	����	: pSnapHandle - ץ�ľ�����ڳ�ʼ������InitSrv�з���
			  pTransBuffer[out]- FIFO��������ַ���ں����ڲ�����
	����ֵ  : 
	          True:�����ɹ���False:����ʧ��
	�޸�ʱ��: 2012/06/14
*/
bool __declspec(dllexport)  SetSnapBuffer(HANDLE pSnapHandle, void** pTransBuffer);
/*
	��������: ReleaseAllBind

    ��������: ����������IP���ڴ��ַ�İ�

	����	: pSnapHandle - ץ�ľ�����ڳ�ʼ������InitSrv�з���
			  
	����ֵ  : 
	          True:�����ɹ���False:����ʧ��

	�޸�ʱ��:  ���� 2012/06/14
*/

bool __declspec(dllexport)  ReleaseAllBind(HANDLE pSnapHandle);

/*
	��������: SetSnapPort

	����	: pSnapHandle - ץ�ľ��,�ں����ڲ���ֵ			  

			  port        - ץ�Ķ˿ں� 

    ����ֵ  : true:�ɹ���false:ʧ��
	
	��������: �������ץ�Ķ˿ں�

    �޸�ʱ��: 2012/06/19
*/
bool __declspec(dllexport) SetSnapPort(HANDLE pSnapHandle, int port);

/*
	��������: BindIPToBuffer

    ��������: �����IP��ַ���ڴ��ַ���û����Ի�ȡָ��IP���ץ�ĵ�ͼ��

	����	: pSnapHandle - ץ�ľ�����ڳ�ʼ������InitSrv�з���
			  IP          - ���IP��ַ
			  pBuffer     - ���IP��Ӧ��FIFO��������ַ����SetSnapBuffer��������
	����ֵ  :
		      True:�󶨳ɹ�, False:��ʧ��
	�޸�ʱ��: ���� 2012/06/14
*/
bool __declspec(dllexport) BindIPToBuffer(HANDLE pSnapHandle, char* IP, void* pBuffer);

/*
	��������: ReleaseFIFOBuffer

	����	: pSnapHandle - ץ�ľ�����ڳ�ʼ������InitSrv�з���
			  
			  pBuf        - ���IP��Ӧ��FIFO��������ַ���ͷŸ��ڴ�

    ����ֵ  : true:�ɹ���false: ʧ��

    �޸�ʱ��: ���� 2012/06/15
*/
bool __declspec(dllexport) ReleaseFIFOBuffer(HANDLE pSnapHandle, void** pBuf);

/*
	��������: ReleaseFIFOBuffer

    ��������: �ͷ�ץ�ľ��pSnapHandle

	����	: pSnapHandle - ץ�ľ�����ڳ�ʼ������InitSrv�з���
			  
    ����ֵ  : ��

	�޸�ʱ��: ���� 2012/06/15
*/
void __declspec(dllexport) ReleaseSnapHandle(HANDLE pSnapHandle);

/*
	��������: StopSrvSnap

	����	: pSnapHandle - ץ�ľ��

    ����ֵ  : true:�ɹ���false: ʧ�� 
	
	��������: ֹͣץ���̣߳��Ͽ�socket����
	
	�޸�ʱ��: ���� 2012/06/18
*/
bool __declspec(dllexport) StopSrvSnap(HANDLE pSnapHandle);

//////////////////////////////////////////////////��������/////////////////////////////////

/*
	��������: InitSoftTrig

    ��������: ��ʼ��

	����	: pCmdHandle - ��������������			 

    ����ֵ  : true:�ɹ���false: ʧ��
*/
bool __declspec(dllexport) InitSoftTrig(HANDLE* pCmdHandle);

/*
	��������: SendSoftTrigge

    ��������: ������������

	����	: pCmdHandle - ����������	
			  cameraIP   - ���IP��ַ
			  svrIP      - ���ط�������ַ
			  port       - ����ץ�Ķ˿�
			  pCmdInfo   - ��������ṹ��

    ����ֵ  : true:�ɹ���false: ʧ��

    �޸�ʱ��: ���� 2012/06/15
*/
bool __declspec(dllexport) SendSoftTrigge(HANDLE pCmdHandle, 
										  char* cameraIP, 
										  char* svrIP, 
										  int port, 
										  SoftCmdPacket* pCmdInfo);
/*
	��������: ReleaseCmdHandle

    ��������: �ͷŴ���������

	����	: pCmdHandle - ����������	

    ����ֵ  : true:�ɹ���false: ʧ��

    �޸�ʱ��: ���� 2012/06/15
*/
bool __declspec(dllexport) ReleaseCmdHandle(HANDLE pCmdHandle);



#endif




















