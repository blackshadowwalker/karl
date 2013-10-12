#if !defined(AFX_SETINIOCXCTL_H__335C2CC8_346D_4035_A0AE_5A1434CF7EBD__INCLUDED_)
#define AFX_SETINIOCXCTL_H__335C2CC8_346D_4035_A0AE_5A1434CF7EBD__INCLUDED_

#include "SetFrameDlg.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SetIniOcxCtl.h : Declaration of the CSetIniOcxCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl : See SetIniOcxCtl.cpp for implementation.

class CSetIniOcxCtrl : public COleControl
{
	DECLARE_DYNCREATE(CSetIniOcxCtrl)

// Constructor
public:
	CSetIniOcxCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSetIniOcxCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CSetIniOcxCtrl();

	BEGIN_OLEFACTORY(CSetIniOcxCtrl)        // Class factory and guid
		virtual BOOL VerifyUserLicense();
		virtual BOOL GetLicenseKey(DWORD, BSTR FAR*);
	END_OLEFACTORY(CSetIniOcxCtrl)

	DECLARE_OLETYPELIB(CSetIniOcxCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CSetIniOcxCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CSetIniOcxCtrl)		// Type name and misc status

	// Subclassed control support
	BOOL IsSubclassedControl();
	LRESULT OnOcmCommand(WPARAM wParam, LPARAM lParam);

// Message maps
	//{{AFX_MSG(CSetIniOcxCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CSetIniOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CSetIniOcxCtrl)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	CSetFrameDlg m_dlg;
	enum {
		dispidGetFtpInfo = 8L,
		dispidSetFtpInfo = 7L,
		dispidSetTimeConfigdlg = 6L,
		dispidSetDoConfigDlg = 5L,
		dispidSetLaneDlg = 4L,
		dispidUpLoadInfo = 3L,
		dispidDownLoadInfo = 2L,
		dispidSetFtpInfoDlg = 1L
		//{{AFX_DISP_ID(CSetIniOcxCtrl)
		// NOTE: ClassWizard will add and remove enumeration elements here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISP_ID
	};
protected:
	void SetFtpInfoDlg(void);
	VARIANT_BOOL DownLoadInfo(void);
	VARIANT_BOOL UpLoadInfo(void);
	VARIANT_BOOL SetLaneDlg(void);
	void SetDoConfigDlg(void);
	void SetTimeConfigdlg(void);
	VARIANT_BOOL SetFtpInfo(LPCTSTR Ip, LONG Port, LPCTSTR userName, LPCTSTR passWord, LPCTSTR serverPath, LPCTSTR localPath,BSTR cameraName, LONG fileSum, LPCTSTR fileList);
	BSTR GetFtpInfo(void);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETINIOCXCTL_H__335C2CC8_346D_4035_A0AE_5A1434CF7EBD__INCLUDED)
