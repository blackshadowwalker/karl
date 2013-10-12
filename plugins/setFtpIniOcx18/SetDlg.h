#if !defined(AFX_SETDLG_H__E44E08DE_98D1_4164_BB56_20F745BC1BB8__INCLUDED_)
#define AFX_SETDLG_H__E44E08DE_98D1_4164_BB56_20F745BC1BB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog
#include "public.h"
#include "updownfile.h"
#include "afxwin.h"

typedef FTP_THREAD_DATA SetInfoList;

class CSetDlg : public CDialog
{
// Construction
public:
	SetInfoList info;
	bool SetFtpInfo(SetInfoList *ftpInfo);
	bool SaveSetIni();
	bool ReadSetIni();
	CSetDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSetDlg)
	enum { IDD = IDD_SET_DLG };
	CIPAddressCtrl	m_ip;
	CString	m_localPath;
	long	m_port;
	CString	m_username;
	CString	m_password;
	CString	m_ftpPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSetDlg)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnBnClickedOk();
	CString m_cameraName;
	CListBox m_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLbnDblclkList1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLbnKillfocusList1();
	afx_msg void OnLbnSelchangeList1();
	CString GetFtpInfo(void);
	bool ReadConfigFromReg(void);
//	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETDLG_H__E44E08DE_98D1_4164_BB56_20F745BC1BB8__INCLUDED_)
