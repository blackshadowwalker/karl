#if !defined(AFX_OPERATIONCONFIG_H__C452CA31_36FF_4C7D_AEE7_7E0906461650__INCLUDED_)
#define AFX_OPERATIONCONFIG_H__C452CA31_36FF_4C7D_AEE7_7E0906461650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OperationConfig.h : header file
//
#include "ConfigType.h"
#include "UpDownFile.h"
/////////////////////////////////////////////////////////////////////////////
// OperationConfig dialog

class OperationConfig : public CDialog
{
// Construction
	DECLARE_DYNAMIC(OperationConfig)
public:
	int regionList[4];
	FTP_THREAD_DATA  info;
	CString cameraName;
	OperationConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(OperationConfig)
	enum { IDD = IDD_OPERATION };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(OperationConfig)
	public:
	virtual int DoModal();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

public:
	int configList[10];
	bool InitDlg();
	bool LoadInfo();
	Tel_Operate mysOperate;//存储结构，返回值

protected:
	static bool inited;
	CComboBox m_operatetype;
	Tel_LaneConfig mysLaneConfig;
	CComboBox m_regionname;
	CComboBox m_regionid;
	CComboBox m_operate;
	CComboBox m_mode;
	CListCtrl m_listoperate;
	int JudgeSame();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnCbnSelchangeRegionName();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedDel();
	virtual BOOL OnInitDialog();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(OperationConfig)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPERATIONCONFIG_H__C452CA31_36FF_4C7D_AEE7_7E0906461650__INCLUDED_)
