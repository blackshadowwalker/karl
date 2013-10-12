#include "stdafx.h"
#include "stdio.h"
#include "UpDownFile.h"


void UploadThread(void* pParam)
{
	FTP_THREAD_DATA  ftpData= {0};
	memcpy(&ftpData,pParam,sizeof(FTP_THREAD_DATA));
	int nFilePos = 0; //�ڼ����ļ���

	while(1)
	{
		int  nFtpResult = 0;
		char cServerFileName[256]  = {0};
		char cLocalFile[256] = {0};

		if(nFilePos < ftpData.MaxFileNum)
		{
			
			sprintf(cLocalFile,"%s/%s/%s",ftpData.localPath,ftpData.cCameraName, ftpData.nFileList[nFilePos]);
			bool exist = fopen(cLocalFile, "r")==NULL ? false : true;
			if(exist)
				nFtpResult = ftpputfile(ftpData.cFtpServerIp,ftpData.nFtpPort,ftpData.cFtpUser,
					ftpData.cFtpPass,cLocalFile, cServerFileName);
			else 
				nFtpResult = FTP_NAME_INVALID;

			if(nFtpResult == FTP_UPLOAD_SUCCESS)
			{
				// ftp �ϴ��ɹ�
			}
			else if(FTP_CONN_FAILURE== nFtpResult)
			{
				// ftp ��������ʧ��
				PostMessage(ftpData.hMainWnd,TF_FTP_MESSAGE,nFtpResult,nFilePos);
				break;
			}
			nFilePos++; //�´�ѭ��������һ���ļ�
		}
		else
		{
			nFtpResult = FTP_END;
		}
		Sleep(20);
		PostMessage(ftpData.hMainWnd,TF_FTP_MESSAGE,nFtpResult,nFilePos);

		if(FTP_END == nFtpResult)
		{
			ftpconfirm(ftpData.cFtpServerIp,ftpData.nFtpPort,ftpData.cFtpUser,
				ftpData.cFtpPass,ftpData.cCameraName);
			Sleep(500);
			break;
		}
	}

}

void  DownThread(void *pParam)
{
	FTP_THREAD_DATA  ftpData= {0};
	memcpy(&ftpData,pParam,sizeof(FTP_THREAD_DATA));
	int nFilePos = 0; //�ڼ����ļ���
	char cDebugBuff[64] = {0};
	int  nLock = ftplock(ftpData.cFtpServerIp,ftpData.nFtpPort,ftpData.cFtpUser,
		ftpData.cFtpPass,ftpData.cCameraName,true);

	/****�ȴ�������ͷȡ��ͼƬ***/
	Sleep(1000);
	while(1)
	{
		int  nFtpResult = 0;
		char cServerFileName[256]  = {0};
		char cLocalFile[256] = {0};
        
		if(nFilePos < ftpData.MaxFileNum)
		{
			sprintf(cServerFileName,"\\%s\\%s",ftpData.cCameraName,ftpData.nFileList[nFilePos]);
			sprintf(cLocalFile,"%s\\%s\\%s",ftpData.localPath,ftpData.cCameraName, ftpData.nFileList[nFilePos]);
			nFtpResult = ftpgetfile(ftpData.cFtpServerIp,ftpData.nFtpPort,ftpData.cFtpUser,
				ftpData.cFtpPass,cServerFileName,cLocalFile);
		//	MessageBox(0,"FTP_CONN_FAILURE","", MB_OK);
			if(nFtpResult == FTP_UPLOAD_SUCCESS)
			{

			}
			else if(FTP_CONN_FAILURE== nFtpResult)
			{
				// ftp ��������ʧ��
				PostMessage(ftpData.hMainWnd,TF_FTP_MESSAGE,nFtpResult,nFilePos);
				
				break;
			}
			nFilePos++; //�´�ѭ��������һ���ļ�
		}
		else
		{
			nFtpResult = FTP_END;
		}
		Sleep(20);
		PostMessage(ftpData.hMainWnd,TF_FTP_MESSAGE,nFtpResult,nFilePos);

		if(FTP_END == nFtpResult)
		{
			Sleep(500);
			break;
		}
	}

	nLock = ftplock(ftpData.cFtpServerIp,ftpData.nFtpPort,ftpData.cFtpUser,
		ftpData.cFtpPass,ftpData.cCameraName,false);

}

