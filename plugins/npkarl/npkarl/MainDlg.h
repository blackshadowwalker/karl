#ifndef HEADER_MAIN_DLG
#define HEADER_MAIN_DLG

#ifndef _AFX_ENABLE_INLINES
#define _AFX_ENABLE_INLINES
#endif

#pragma once



#include "resource.h"
#include <afxwin.h>
// CMainDlg �Ի���

class CMainDlg : public CDialog
{
	DECLARE_DYNAMIC(CMainDlg)

public:
	CMainDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMainDlg();

// �Ի�������
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
#endif