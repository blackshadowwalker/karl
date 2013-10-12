#ifndef __UP_DOWN_FILE_H
#define __UP_DOWN_FILE_H
#define  MAX_FILE_NUM 32
#define  FILENAME_LEN   128
#include <WinSock2.h>
#include <process.h>
#include "ftpgetput.h"
#define TF_FTP_MESSAGE  (WM_USER+100)

typedef struct  
{
	HWND  hMainWnd;
	char  cCameraName[64];
	char  cFtpPath[128];
	char  cFtpServerIp[32];
	int   nFtpPort;
	char  cFtpUser[64];
	char  cFtpPass[64];
	char  localPath[256];
	char  serverPath[256];
	int   nflag;//记录 上传/下载
	int   MaxFileNum;
	char  nFileList[MAX_FILE_NUM][FILENAME_LEN];
}FTP_THREAD_DATA;

void UploadThread(void* pParam);
void DownThread(void *pParam);

#endif