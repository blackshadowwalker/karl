#if !defined(AFX_LIGHTCONFIG_H__473CA246_5A67_4B87_B641_8756B560B771__INCLUDED_)
#define AFX_LIGHTCONFIG_H__473CA246_5A67_4B87_B641_8756B560B771__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LightConfig.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// LightConfig dialog

class LightConfig : public CDialog
{
// Construction
public:
	Image *img;
	void ShowPic();
	LightConfig(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(LightConfig)
	enum { IDD = IDD_LIGHT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LightConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(LightConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LIGHTCONFIG_H__473CA246_5A67_4B87_B641_8756B560B771__INCLUDED_)
