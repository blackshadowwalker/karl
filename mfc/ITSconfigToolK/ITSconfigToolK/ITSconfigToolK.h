
// ITSconfigToolK.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CITSconfigToolKApp:
// �йش����ʵ�֣������ ITSconfigToolK.cpp
//

class CITSconfigToolKApp : public CWinApp
{
public:
	CITSconfigToolKApp();
	static CString m_appPath;
	static const char *getAppPath(){return m_appPath.GetBuffer(m_appPath.GetLength());}
// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CITSconfigToolKApp theApp;