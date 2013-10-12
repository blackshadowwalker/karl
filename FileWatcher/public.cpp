// public.cpp
#pragma once

#include "stdafx.h"
#include "public.h"

char *replaceALl(char *tchar)
{
	return tchar;
}

void ListAllFiles(char *Path, CListBox *pList)
{
    char file[MAX_PATH];
    lstrcpy(file,Path);
    lstrcat(file,"\\*.*"); 
    WIN32_FIND_DATA wfd; 
    HANDLE Find = FindFirstFile(file,&wfd); 
    if (Find == INVALID_HANDLE_VALUE)  
        return;
     
    while (FindNextFile(Find, &wfd))
    {
		char szFindPath[MAX_PATH]={0};
        if (wfd.cFileName[0] == '.') 
        {
            continue;
        } 
		lstrcpy(szFindPath,Path); 
		lstrcat(szFindPath,"\\"); 
		lstrcat(szFindPath,wfd.cFileName); 
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
        {
            //ListAllFiles(szFindPath, list);  
		}
		else
			pList->AddString( wfd.cFileName );
        //DeleteFile(FilePath);
    }
    FindClose(Find);
     
}

TCHAR* g_GetIniPath(void)
{
	static TCHAR* pszIniPath = NULL;
	if( NULL == pszIniPath)
	{
		TCHAR szDirBuf[512] = {0};
		pszIniPath = new TCHAR[512];
		memset(pszIniPath, 0, 512);
		GetSystemDirectory(szDirBuf,512);
	//	GetCurrentDirectory(512, szDirBuf);
		sprintf(pszIniPath, "%s\\langchn.ini", szDirBuf);
	}
	return pszIniPath;
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

TCHAR* g_GetSetPath(void)
{
	static TCHAR* pszIniPath = NULL;
	if( NULL == pszIniPath)
	{
		TCHAR szDirBuf[512] = {0};
		pszIniPath = new TCHAR[512];
		memset(pszIniPath, 0, 512);
		GetCurrentDirectory(512, szDirBuf);
		sprintf(pszIniPath,"%s\\set.ini", szDirBuf);
	}
	return pszIniPath;
}

//选择文件夹 对话框
#ifndef BIF_NEWDIALOGSTYLE
#define BIF_NEWDIALOGSTYLE 0x0040
#endif
CString SelectFolder(CWnd *hWnd)
{
	HWND hwnd= hWnd->GetSafeHwnd();   //得到窗口句柄
	CString filePath= "";		//得到文件路径			
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)		//取得IMalloc分配器接口
	{   
		BROWSEINFO		bi;
		TCHAR			pszBuffer[MAX_PATH];
		LPITEMIDLIST	pidl;   
		
		bi.hwndOwner		= hwnd;
		bi.pidlRoot			= NULL;
		bi.pszDisplayName   = pszBuffer;
		bi.lpszTitle		= _T("Select Folder"); //选择目录对话框的上部分的标题
		//添加新建文件夹按钮 BIF_NEWDIALOGSTYLE
		bi.ulFlags			=  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn				= NULL;
		bi.lParam			= 0;
		bi.iImage			= 0;
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //取得IMalloc分配器接口
		{   
			if (::SHGetPathFromIDList(pidl, pszBuffer)) //获得一个文件系统路径
			{
				filePath = pszBuffer;
			}
			else filePath="";
			pMalloc->Free(pidl);	//释放内存
			
		//	MessageBox(m_strPath);
		}
		pMalloc->Release();			//释放接口
	}

	return filePath;
}
//判断文件/文件夹是否存在
//判断文件：	FindFirstFileExists(lpPath, FALSE);  
//判断文件夹：	FindFirstFileExists(lpPath, FILE_ATTRIBUTE_DIRECTORY);  
BOOL FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter)  
{  
	WIN32_FIND_DATA fd;  
	HANDLE hFind = FindFirstFile(lpPath, &fd);  
	BOOL bFilter = (FALSE == dwFilter) ? TRUE : fd.dwFileAttributes & dwFilter;  
	BOOL RetValue = ((hFind != INVALID_HANDLE_VALUE) && bFilter) ? TRUE : FALSE;  
	FindClose(hFind);  
	return RetValue;  
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
		//if(!isOk） 
		//	return false;
	}
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
//		AfxMessageBox("错误：无法设置有关的注册表信息");
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
	return true;
}

#include "time.h"
static char *timestr = new char[256];

char *getNowTime(){
	time_t timer;
	struct tm *tmt;
	timer = time(NULL);
	tmt = localtime(&timer);
	
	memset(timestr, 0, 256);
	sprintf(timestr,"%d-%d-%d  %d:%d:%d", tmt->tm_year+1900, tmt->tm_mon+1, tmt->tm_mday, tmt->tm_hour, tmt->tm_min, tmt->tm_sec );
	return timestr;
}

char *formatTime(time_t* t)
{
	struct tm *tmt =new struct tm;
	tmt = localtime(t);
	char *str = new char[256];
	memset(str, 0, 256);
	sprintf(str,"%d-%d-%d  %d:%d:%d", tmt->tm_year+1900, tmt->tm_mon+1, tmt->tm_mday, tmt->tm_hour, tmt->tm_min, tmt->tm_sec );
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
	char *path = new char[256];
	memset(path, 0, 256);
	GetModuleFilePath(path);
	char *path2 = GetWindowPath();
	time_t timer;//time_t就是long int 类型
	struct tm *tblock;
	timer = time(NULL);//这一句也可以改成time(&timer);
	tblock = localtime(&timer);
//	fprintf(out, "\n%s\t%s",ctime(&timer), info);
//	fprintf(out, "\n【%s】\t%s",formatTime(&timer), info);
	printf("【%s】\t%s \n",formatTime(&timer), info);
	
//	fclose(out);
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


/*
//字符串分割
//e.g:
	CStringList fileList;
	CString file;
	Split(fileLists, "<R>", &fileList);
	for(int i=0; i<fileSum; i++)
	{
		file = fileList.GetHead();
		if(file.IsEmpty())	
		{ }
		else
		{
			memcpy(ftpData.nFileList[i],file.GetBuffer(file.GetLength()) , 32 );
		}
		fileList.RemoveHead();
	}
*/
void Split(const CString& src, CString delimit, CStringList* pOutList, int num, CString nullSubst)  
{  
	ASSERT( !src.IsEmpty() && !delimit.IsEmpty() );  
	if(num==1)   
	{  
		pOutList->AddTail(src);  
		return;  
	}  

	int deliLen = delimit.GetLength();  
	long index = -1, lastSearchPosition = 0, cnt = 0;  

	while( (index=src.Find(delimit, lastSearchPosition))!=-1 )  
	{  
		if(index==lastSearchPosition)  
		{
			pOutList->AddTail(nullSubst);  
		}
		else 
		{
			pOutList->AddTail(src.Mid(lastSearchPosition, index-lastSearchPosition));  
		}
		lastSearchPosition = index + deliLen;  

		if(num)  
		{  
			++cnt;  
			if(cnt+1==num) break;  
		}  
	}  
	CString lastOne = src.Mid(lastSearchPosition);  
	pOutList->AddTail( lastOne.IsEmpty()? nullSubst:lastOne);  
}


void __cdecl kprintf(const char *format, ...)
{
    char buf[4096], *p = buf;
    va_list args;
    va_start(args, format);
    p += _vsnprintf(p, sizeof buf - 1, format, args);
    va_end(args);
    while ( p > buf && isspace(p[-1]) )
        *--p = '\0';
    *p++ = '\r';
    *p++ = '\n';
    *p = '\0';
    OutputDebugString(buf);
}
