// public.cpp
#pragma once

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
 
#include "public.h"
#include "ITSconfigToolK.h"


void alert(char *text)
{
	MessageBox(0, text,"", MB_OK);
}

char *getThisPath(CWinApp *app, char *path)
{
	char g_szThisPath[512] = {0};
	char g_szThisName[256] = {0}; 
	sprintf(g_szThisPath,"%s", app->m_pszHelpFilePath);
	sprintf(g_szThisName, "%s.HLP", app->m_pszExeName);
	printf("g_szOcxName = %s \n", g_szThisName);

	int pathLen = strlen(g_szThisPath);
	int nameLen = strlen(g_szThisName);
	g_szThisPath[pathLen-nameLen-1] = '\0';

	if(path==0)
	{	
		path = new char[512];
		memset(path, 0, 512);
	}
	sprintf(path, "%s",g_szThisPath); 
	return 	path;
}
void DrawImg2Hdc(Image *image, UINT id, CWnd* cWnd, CRect rect)
{
	if(image==0) return;
	CDC* pDC = cWnd->GetDlgItem(id)->GetDC();
	Graphics graphics( pDC->m_hDC);
	graphics.DrawImage(image,0,0, rect.Width(), rect.Height());
}
Image* KLoadImage(CString filename)
{
	LPWSTR strjpg = new WCHAR[255];
	LPTSTR lpStr2 = filename.GetBuffer( filename.GetLength() );
	int nLen2 = MultiByteToWideChar(CP_ACP, 0,lpStr2, -1, NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, lpStr2, -1, strjpg, nLen2);

	Image *image=0;
	image=Image::FromFile(strjpg,true);
	return image;
}

TCHAR* g_GetIniPath(void)
{
	static TCHAR* pszIniPath = NULL;
	if( NULL == pszIniPath)
	{
		TCHAR szDirBuf[512] = {0};
		pszIniPath = new TCHAR[512];
		memset(pszIniPath, 0, 512);
	//	GetSystemDirectory(szDirBuf,512);
	//	GetCurrentDirectory(512, szDirBuf);
		sprintf(pszIniPath, "%s\\langchn.ini", CITSconfigToolKApp::getAppPath());
		EventLog(pszIniPath);
	}
	return pszIniPath;
}
char *val = 0;
char* ConvertInfo(char* strText)
{

	if(val!=NULL)
		delete val;
	val = new char[256];
	memset(val,0,256);
	GetPrivateProfileString("String",strText,"",
		val,256,g_GetIniPath());
	if(strlen(val)==0)
	{
		//If there is no corresponding string in ini file ,then set it to be default value.
		memcpy(val,strText, strlen(strText));
	}
	return val;
}

CString ConvertString(CString strText)
{
	char *val = new char[200];
	CString strIniPath,strRet;
	
	memset(val,0,200);
	GetPrivateProfileString("String",strText,"",
		val,200,g_GetIniPath());
	strRet = val;
	if(strRet.GetLength()==0)
	{
		//If there is no corresponding string in ini file ,then set it to be default value.
		strRet=strText;
	}
	delete val;
	return strRet;
}
//Set static text in dialogue box (English->current language)
void g_SetWndStaticText(CWnd * pWnd)
{
	CString strCaption,strText;
	
	//Set main window title
	pWnd->GetWindowText(strCaption);
	if(strCaption.GetLength()>0)
	{
		strText=ConvertString(strCaption);
		pWnd->SetWindowText(strText);
	}
	
	//Set small window title 
	CWnd * pChild=pWnd->GetWindow(GW_CHILD);
	CString strClassName;
	while(pChild)
	{
		//////////////////////////////////////////////////////////////////////////		
		//Added by Jackbin 2005-03-11
		strClassName = ((CRuntimeClass*)pChild->GetRuntimeClass())->m_lpszClassName;
		if(strClassName == "CEdit")
		{
			//Next small window 
			pChild=pChild->GetWindow(GW_HWNDNEXT);
			continue;
		}
		
		//////////////////////////////////////////////////////////////////////////	
		
		//Set small window current language text 
		pChild->GetWindowText(strCaption);
		strText=ConvertString(strCaption);
		pChild->SetWindowText(strText);
		
		//Next small window 
		pChild=pChild->GetWindow(GW_HWNDNEXT);
	}
}
//�ж��ļ�/�ļ����Ƿ����
//�ж��ļ���	FindFirstFileExists(lpPath, FALSE);  
//�ж��ļ��У�	FindFirstFileExists(lpPath, FILE_ATTRIBUTE_DIRECTORY);  
BOOL FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter)  
{  
	WIN32_FIND_DATA fd;  
	HANDLE hFind = FindFirstFile(lpPath, &fd);  
	BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;  
	BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;  
	FindClose(hFind);  
	return RetValue;  
}  


TCHAR* g_GetSetPath(void)
{
	static TCHAR* pszIniPath = NULL;
	if( NULL == pszIniPath)
	{
		TCHAR szDirBuf[512] = {0};
		pszIniPath = new TCHAR[512];
		memset(pszIniPath, 0, 512);
		GetCurrentDirectory(512, szDirBuf);
		sprintf(pszIniPath, "%s\\set.ini", szDirBuf);
	}
	return pszIniPath;
}
//ѡ���ļ��� �Ի���
#ifndef BIF_NEWDIALOGSTYLE
#define BIF_NEWDIALOGSTYLE 0x0040
#endif
CString SelectFolder(CWnd *hWnd)
{
	HWND hwnd= hWnd->GetSafeHwnd();   //�õ����ھ��
	CString filePath= "";		//�õ��ļ�·��			
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)		//ȡ��IMalloc�������ӿ�
	{   
		BROWSEINFO		bi;
		TCHAR			pszBuffer[MAX_PATH];
		LPITEMIDLIST	pidl;   
		
		bi.hwndOwner		= hwnd;
		bi.pidlRoot			= NULL;
		bi.pszDisplayName   = pszBuffer;
		bi.lpszTitle		= _T("ѡ�񱣴���Ƶ֡ͼƬ���ļ���"); //ѡ��Ŀ¼�Ի�����ϲ��ֵı���
		//����½��ļ��а�ť BIF_NEWDIALOGSTYLE
		bi.ulFlags			=  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn				= NULL;
		bi.lParam			= 0;
		bi.iImage			= 0;
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //ȡ��IMalloc�������ӿ�
		{   
			if (::SHGetPathFromIDList(pidl, pszBuffer)) //���һ���ļ�ϵͳ·��
			{
				filePath = pszBuffer;
			}
			else filePath="";
			pMalloc->Free(pidl);	//�ͷ��ڴ�
			
		//	MessageBox(m_strPath);
		}
		pMalloc->Release();			//�ͷŽӿ�
	}

	return filePath;
}
void charRplace(char *src, char *oldRp, char* newRp){
	char  *p = src, *pre=src , *p2;
	char  str[512] = {0};
	p2 = str;
	while( (p = strstr(pre, oldRp)) ){
		memcpy(p2, pre, p-pre);
		p2 += (p-pre);
		memcpy(p2, newRp, strlen(newRp));
		p2 += strlen(newRp);
		pre = (p+strlen(oldRp));
	}
	if(strlen(pre)>0)
		memcpy(p2, pre, strlen(pre));
	memcpy(src, str, strlen(str));
}
/*
return	split len
*/
//int	splitchar(char *src=0,  char**dest=0, int destlen=0, char *splitstr=0, int maxlen=0)
int	splitchar(char *src,  char**dest, int destlen, char *splitstr, int maxlen)
{
	if(src==0 || dest==0 || destlen==0)
		return 0;
	if(splitstr==0)
	{
		splitstr = new char[2];
		splitstr[0] = ' ';
		splitstr[1] = '\0';
	}
	int lensrc = strlen(src);
	char *prestr = new char[lensrc+1];
	char *p2 = prestr;
	memset(prestr,0, lensrc+1);
	memcpy(prestr, src, lensrc);
	char *p = 0;
	int i=0;
	while( i<destlen && (i<maxlen || maxlen==0) && (p = strstr(prestr, splitstr)) ){
		dest[i] = new char[p-prestr+1];
		memset(dest[i], 0, p-prestr+1);
		memcpy(dest[i], prestr, p-prestr);
		i++;
		if(strlen(p)>=2)
			prestr = p+1;
	}
	if(strlen(prestr)){
		dest[i] = new char[strlen(prestr)+1];
		memset(dest[i], 0, strlen(prestr)+1);
		memcpy(dest[i], prestr, strlen(prestr));
		i++;
	}

	delete p2;
	return i;
}
bool KCreateFolder(CString folder)
{
	folder += "/";
	folder.Replace("/","\\");
	int index=2;
	BOOL isOk = true;
	while(1)
	{
	//	folder.Delete(0, index+1);
		index = folder.Find("\\",index+1);
		index = index<0? folder.Find("/") : index;
		if(index<0) break;
		CString str = folder.Left(index);
		isOk = (BOOL)CreateDirectory( str, 0 );
		//if(!isOk�� 
		//	return false;
	}
	return true;
}

bool RemoveDir(const char* szFileDir)
{
	if(szFileDir==NULL  || !FindFirstFileExists(szFileDir, FILE_ATTRIBUTE_DIRECTORY) )
		return false;
	CString strDir(szFileDir);
	if (strDir.GetAt(strDir.GetLength()-1) != '\\');
	strDir += '\\';
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((strDir + "*.*"),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp(wfd.cFileName,".") != 0 &&
				stricmp(wfd.cFileName,"..") != 0)
				RemoveDir( (strDir + wfd.cFileName));
		}
		else
		{
			DeleteFile( (strDir + wfd.cFileName));
		}
	}
	while (FindNextFile(hFind,&wfd));
		FindClose(hFind);
	RemoveDirectory(szFileDir);
	return true;
	
} 

bool OpenReg(HKEY &hKEY, char *data_Set)
{
	long	ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_READ,&hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return false;
	}
	return true;
}
BYTE* QueryReg(char *key,DWORD dataLen, HKEY hKEY)
{
	LPBYTE	data=new BYTE[dataLen];
	memset(data, 0, dataLen);
	DWORD	type_1=REG_BINARY;

	long ret1=::RegQueryValueEx(hKEY,key,NULL,&type_1,data,&dataLen);
	if(ret1!=ERROR_SUCCESS)
	{
		return NULL;
	}
	BYTE* str = new BYTE[dataLen];
	memcpy(str, data, dataLen);
//	delete data;
	return str;
}

long CreateReg(HKEY hKEY,const char *subkey)
{
    DWORD dwDisposition;
	return RegCreateKeyEx(HKEY_CURRENT_USER, subkey,         
           0,             
           NULL,             
           REG_OPTION_NON_VOLATILE,
           KEY_ALL_ACCESS,
           NULL,           
           &hKEY,          
           &dwDisposition );
}

bool WriteReg(HKEY &hKEY, char *data_Set)
{
	long	ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_WRITE,&hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return false;
	}
	return true;
}
bool SetReg(char *key, BYTE* value, DWORD dataLen, HKEY hKEY)
{
	DWORD	type_1 = REG_BINARY;
	long ret1=::RegSetValueEx(hKEY,key,NULL,type_1,(CONST BYTE*)value,dataLen);
	if(ret1!=ERROR_SUCCESS)
	{
		setLastError(ConvertInfo("�����޷������йص�ע�����Ϣ!"));
//		AfxMessageBox("�����޷������йص�ע�����Ϣ");
		return false;
	}
	return true;
}


char* GetWindowPath()
{
	char *path = new char[MAX_PATH];
	memset(path, 0, MAX_PATH);
	GetSystemDirectory(path, MAX_PATH);
//	GetModuleFileName(0, path, MAX_PATH);
	path[2]='\0';//
	/*for(int i=strlen(path); i>0; i--)
		if(path[i]=='/' || path[i]=='\\')
		{
			path[i+1]='\0';
			break;
		}*/
	strcat(path,"\\");
	return path;
}
bool GetModuleFilePath(char *path)
{
	if(path==NULL) 
	{
		path = new char[MAX_PATH];
		memset(path, 0, MAX_PATH);
	}
	GetModuleFileName(0, path, MAX_PATH);
	int len = strlen(path);
	char *p = path+len-1;
	while(*p--!= '\\' );
	*(p+1)='\0';
	return path;
}

#include "time.h"
char *formatTime(time_t* t)
{
	struct tm *time;
	time = localtime(t);
	char *str = new char[256];
	memset(str, 0, 256);
	sprintf(str,"%d-%d-%d  %d:%d:%d", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec );
	return str;
}
char *formatTMTime(struct tm *time)
{
	char *str = new char[256];
	memset(str, 0, 256);
	sprintf(str,"%d-%d-%d  %d:%d:%d", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec );
	return str;
}

void EventLog(char* info)
{
	time_t timer;//time_t����long int ����
	struct tm *tblock;
	timer = time(NULL);//��һ��Ҳ���Ըĳ�time(&timer);
	tblock = localtime(&timer);
//	fprintf(out, "\n%s\t%s",ctime(&timer), info);
	printf("\n��%s��\t%s",formatTime(&timer), info);
}

//
void Encryption(BYTE *data, long lenData,  BYTE *key, long lenKey)
{
	int j=0;
	for(int i=0; i<lenData; i++,j++)
	{
		if(j==lenKey)
			j=0;
		data[i] = data[i] ^ key[j];
	}
}
void Decryption(BYTE *data, long lenData,  BYTE *key, long lenKey)
{
	int j=0;
	for(int i=0; i<lenData; i++,j++)
	{
		if(j==lenKey)
			j=0;
		data[i] -= key[j];
	}
}


/*************  error infos ******************/
char*		getLastError(){
	return lastError;
}
int			setLastError(char *info){
	if(info==NULL)
		memset(lastError, 0, 256);
	else if (strlen(info)==0)
		memset(lastError, 0, 256);
	else 
		memcpy(lastError, info, strlen(info));
	return 0;
}
int			getLastErrorCode(){
	return lastErrorCode ;
}
int			setLastErrorCode(int code){
	lastErrorCode = code;
	return 0;
}

/**********  math *************/

// �㵽ֱ�ߵľ���
double DisPoint2Line(  CPoint pt, CLine line )
{
    //Line: ax+by+c=0
    //len = |Line|/sqrt(a*a+b*b)
    //a=y2-y1
    //b=x1-x2
    //c=x2*y1-x1*y2
	double a= line.endPoint.y-line.startPoint.y;
    double b = line.startPoint.x-line.endPoint.x;
    double c = line.endPoint.x*line.startPoint.y-line.startPoint.x*line.endPoint.y;

    double result = abs((long)((a*pt.x+b*pt.y+c)/sqrt((double)(a*a+b*b))));

    return result;
}