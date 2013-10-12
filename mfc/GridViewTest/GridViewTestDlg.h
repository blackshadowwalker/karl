// GridViewTestDlg.h : header file
//

#if !defined(AFX_GRIDVIEWTESTDLG_H__D4FE37A2_120A_426C_ABEF_65DF4CBA6B9C__INCLUDED_)
#define AFX_GRIDVIEWTESTDLG_H__D4FE37A2_120A_426C_ABEF_65DF4CBA6B9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GridCtrl_src/GridCtrl.h"
/////////////////////////////////////////////////////////////////////////////
// CGridViewTestDlg dialog

class CGridViewTestDlg : public CDialog
{
// Construction
public:
	CGridViewTestDlg(CWnd* pParent = NULL);	// standard constructor


	CGridCtrl m_Grid;
	CImageList m_ImageList;

	CSpinButtonCtrl	m_RowSpin;
	CSpinButtonCtrl	m_FixRowSpin;
	CSpinButtonCtrl	m_FixColSpin;
	CSpinButtonCtrl	m_ColSpin;	

	int		m_nFixCols;
	int		m_nFixRows;
	int		m_nCols;
	int		m_nRows;

	void FilleDatasToGridView();
	bool InitGridView();

// Dialog Data
	//{{AFX_DATA(CGridViewTestDlg)
	enum { IDD = IDD_GRIDVIEWTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridViewTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CGridViewTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEWTESTDLG_H__D4FE37A2_120A_426C_ABEF_65DF4CBA6B9C__INCLUDED_)
