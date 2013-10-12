// FileWatcherDlg.h : header file
//

#if !defined(AFX_FILEWATCHERDLG_H__41F1A27C_5C3F_4E76_A9E3_8661E40F5CED__INCLUDED_)
#define AFX_FILEWATCHERDLG_H__41F1A27C_5C3F_4E76_A9E3_8661E40F5CED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CFileWatcherDlg dialog

#include <list>
using namespace std;


class CFileWatcherDlg : public CDialog
{
// Construction
public:
	bool SaveConfig();
	void PrintMsg(CString);
	CFileWatcherDlg(CWnd* pParent = NULL);	// standard constructor

	BOOL bStopProcess;
	BOOL bStopedProcess;

// Dialog Data
	//{{AFX_DATA(CFileWatcherDlg)
	enum { IDD = IDD_FILEWATCHER_DIALOG };
	CEdit	m_edit;
	CListBox	m_wlist;
	CString	m_dir;
	int		m_imageWidth;
	int		m_imageHeight;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFileWatcherDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
public:
	bool ReadConfig();
	bool bWatching;
	CString logFile;
	list<CString> m_images;

	// Generated message map functions
	//{{AFX_MSG(CFileWatcherDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtWatch();
	afx_msg void OnBtBrowserDir();
	afx_msg void OnButton1();
	afx_msg void OnBtLog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButton2();
	afx_msg void OnBtResetWh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILEWATCHERDLG_H__41F1A27C_5C3F_4E76_A9E3_8661E40F5CED__INCLUDED_)
