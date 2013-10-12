// GetFramesFromAVI.h : main header file for the GETFRAMESFROMAVI application
//

#if !defined(AFX_GETFRAMESFROMAVI_H__C8396B90_EA96_4A5C_8BAF_4C19887FD879__INCLUDED_)
#define AFX_GETFRAMESFROMAVI_H__C8396B90_EA96_4A5C_8BAF_4C19887FD879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGetFramesFromAVIApp:
// See GetFramesFromAVI.cpp for the implementation of this class
//

class CGetFramesFromAVIApp : public CWinApp
{
public:
	CGetFramesFromAVIApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetFramesFromAVIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGetFramesFromAVIApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETFRAMESFROMAVI_H__C8396B90_EA96_4A5C_8BAF_4C19887FD879__INCLUDED_)
