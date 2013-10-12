// WindowPlayDlg.h : header file
//
//{{AFX_INCLUDES()
#include "wmpplayer4.h"
//}}AFX_INCLUDES

#if !defined(AFX_WINDOWPLAYDLG_H__85B1D366_7CBD_4A68_9CA3_8453A91D975A__INCLUDED_)
#define AFX_WINDOWPLAYDLG_H__85B1D366_7CBD_4A68_9CA3_8453A91D975A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWindowPlayDlg dialog

class CWindowPlayDlg : public CDialog
{
// Construction
public:
	CWindowPlayDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWindowPlayDlg)
	enum { IDD = IDD_WINDOWPLAY_DIALOG };
	CWMPPlayer4	m_player;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowPlayDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWindowPlayDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWPLAYDLG_H__85B1D366_7CBD_4A68_9CA3_8453A91D975A__INCLUDED_)
