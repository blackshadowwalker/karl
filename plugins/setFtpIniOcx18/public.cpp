//public.cpp

#include "stdafx.h"
#include "public.h"
/*
void DrawImg2Hdc(IplImage *img, UINT id, CDC *pDC, CRect rect)
{
	HDC hDC=pDC->GetSafeHdc();
	CvvImage cimage;
	cimage.CopyOf(img,img->nChannels);
	cimage.DrawToHDC(hDC,&rect);
}
*/

bool RemoveDir(const char* szFileDir)
{
/*	std::string strDir = szFileDir;
	if (strDir.at(strDir.length()-1) != '\\');
	strDir += '\\';
	WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
	if (hFind == INVALID_HANDLE_VALUE)
		return false;
	do
	{
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (stricmp(wfd.cFileName,".") != 0 &&
				stricmp(wfd.cFileName,"..") != 0)
				RemoveDir( (strDir + wfd.cFileName).c_str());
		}
		else
		{
			DeleteFile( (strDir + wfd.cFileName).c_str());
		}
	}
	while (FindNextFile(hFind,&wfd));
	FindClose(hFind);
	RemoveDirectory(szFileDir);
*/	return true;
	
} 

bool KCreateFolder(CString folder)
{
	folder += "/";
	folder.Replace("/","\\");
	int index=2;
	bool isOk = true;
	while(1)
	{
	//	folder.Delete(0, index+1);
		index = folder.Find("\\",index+1);
		index = index<0? folder.Find("/") : index;
		if(index<0) break;
		CString str = folder.Left(index);
		isOk = CreateDirectory( str, 0 );
		//if(!isOk） 
		//	return false;
	}
	return true;
}
//注册表相关
void SetRegPath(CString str)
{
	data_Set = (LPCTSTR)str;
}
LPCTSTR GetRegPath()
{
	return data_Set;
}
bool OpenReg(HKEY &hKEY)
{
	long	ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_READ,&hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return false;
	}
	return true;
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
bool WriteReg(HKEY &hKEY)
{
	long	ret0=(::RegOpenKeyEx(HKEY_CURRENT_USER,data_Set,0,KEY_WRITE,&hKEY));
	if(ret0!=ERROR_SUCCESS)
	{
		return false;
	}
	return true;
}
char* QueryReg(char *key,DWORD dataLen, HKEY hKEY)
{
	LPBYTE	data=new BYTE[dataLen];
	memset(data, 0, dataLen);
	DWORD	type_1=REG_BINARY;

	long ret1=::RegQueryValueEx(hKEY,key,NULL,&type_1,data,&dataLen);
	if(ret1!=ERROR_SUCCESS)
	{
		return NULL;
	}
	char* str = new char[dataLen];
	memcpy(str, data, dataLen);
//	delete data;
	return str;
}

bool SetReg(char *key, char* value, DWORD dataLen, HKEY hKEY)
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
	strcat(path,"\\setFrame\\");
	return path;
}

Tel_Point Point2Telpoint(CPoint pt)
{
	Tel_Point p;
	p.ix = pt.x;
	p.iy = pt.y;
	return p;
}
CPoint Telpoint2Point(Tel_Point pt)
{
	CPoint p;
	p.x = pt.ix;
	p.y = pt.iy;
	return p;
}

void DrawImg2Hdc(Image *image, UINT id, CWnd* cWnd, CRect rect)
{
	if(image==0) return;
	CDC* pDC = cWnd->GetDlgItem(id)->GetDC();
	Graphics graphics( pDC->m_hDC);
	graphics.DrawImage(image,0,0, rect.Width(), rect.Height());
}

void DrawImgFile2Hdc(CString filename, UINT id, CWnd* cWnd, CRect rect)
{
	Image *image = KLoadImage(filename);
	DrawImg2Hdc(image, id, cWnd, rect);
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

