#if !defined(AFX_PROGRESS_H__D3C452AF_1A24_4015_92F4_6A4F24DEAD54__INCLUDED_)
#define AFX_PROGRESS_H__D3C452AF_1A24_4015_92F4_6A4F24DEAD54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Progress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog

class CProgress : public CDialog
{
// Construction
public:
	void Close();
	void SetProcessPos(int pos);
	void ShowProcess(long totalSize, long curSize, char* filename, int flag);
	CProgress(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CProgress)
	enum { IDD = IDD_PROGRESS };
	CProgressCtrl	m_progress;
	CString	m_title;
	CString	m_totalSize;
	CString	m_curSize;
	CString	m_Percentage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgress)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgress)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESS_H__D3C452AF_1A24_4015_92F4_6A4F24DEAD54__INCLUDED_)
