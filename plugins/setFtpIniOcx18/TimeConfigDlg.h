#if !defined(AFX_TIMECONFIGDLG_H__A431F09D_2765_4F60_9869_FAE7FBB0A1B3__INCLUDED_)
#define AFX_TIMECONFIGDLG_H__A431F09D_2765_4F60_9869_FAE7FBB0A1B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeConfigDlg.h : header file
//
#include "UpDownFile.h"
#include "afxwin.h"
/////////////////////////////////////////////////////////////////////////////
// CTimeConfigDlg dialog

class CTimeConfigDlg : public CDialog
{
// Construction
public:
	FTP_THREAD_DATA  info;

	void UpdateTimes();
	void SaveTemp();
	CString cameraName;
	int m_week;
	int m_times[7][20];
	bool ReadTimeConfig();
	bool SaveTimeConfig();

	CTimeConfigDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTimeConfigDlg)
	enum { IDD = IDD_TIME_CONFIG };
	CButton	m_saveAuto;
	CComboBox	m_event;
	CButton	m_check1;
	CComboBox	m_weeks;
	int		m_listIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeConfigDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeConfigDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnSetfocusCombo1();
	virtual void OnCancel();
	afx_msg void OnButton3();
	afx_msg void OnButton0();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnSelchangeComEvent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnNMThemeChangedCheck6(NMHDR *pNMHDR, LRESULT *pResult);
	CButton editAble;
//	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck6();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMECONFIGDLG_H__A431F09D_2765_4F60_9869_FAE7FBB0A1B3__INCLUDED_)
