// GetFramesFromAVIDlg.h : header file
//

#if !defined(AFX_GETFRAMESFROMAVIDLG_H__1717C609_2EF4_4931_BDCC_F5ACA430D764__INCLUDED_)
#define AFX_GETFRAMESFROMAVIDLG_H__1717C609_2EF4_4931_BDCC_F5ACA430D764__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CGetFramesFromAVIDlg dialog
typedef struct 
{
	int		frameInterval;//取帧间隔
	bool	bShow;//是否显示视频
	char	dstPath[256];
	char	aviPath[256];
	void*	pParam;//
}ProcessInfo;

#include "time.h"

class CGetFramesFromAVIDlg : public CDialog
{
// Construction
public:
	ProcessInfo *pInfo;
	bool	m_bShow;
	time_t	startTime;
	time_t	endTime;
	bool	SetAviProperty();
	int		sleepTime;//控制播放速度快慢,暂时没用
	bool	bGetFrame;//是否取数据帧
	bool	pause;
	CRect	screenRect;
	bool	isRun;

	void	Proc(ProcessInfo *stu );
	CGetFramesFromAVIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CGetFramesFromAVIDlg)
	enum { IDD = IDD_GETFRAMESFROMAVI_DIALOG };
	CButton	m_checkShow;
	CStatic	m_screen;
	CString	m_path;
	CString	m_aviPath;
	long	m_frameInterval;
	long	m_frameFrom;
	long	m_frameTo;
	CString	m_nFrame;
	int		m_sleepTime;//控制播放速度快慢
	long	m_rectHeight;
	long	m_rectWidth;
	long	m_rectX;
	int		m_rectY;
	CString	m_runTimes;
	int		m_imageDepth;
	int		m_imageChannel;
	int		m_imageHeight;
	int		m_imageWidth;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetFramesFromAVIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGetFramesFromAVIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton2();
	afx_msg void OnBtBrowswe();
	afx_msg void OnBtBrowserAvi();
	afx_msg void OnButton1();
	virtual void OnCancel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtPause();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnBtStartGetframe();
	afx_msg void OnSlower();
	afx_msg void OnFaster();
	afx_msg void OnNormal();
	afx_msg void OnCheckShow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETFRAMESFROMAVIDLG_H__1717C609_2EF4_4931_BDCC_F5ACA430D764__INCLUDED_)
