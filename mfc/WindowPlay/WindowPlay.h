// WindowPlay.h : main header file for the WINDOWPLAY application
//

#if !defined(AFX_WINDOWPLAY_H__30234095_FD28_4BDB_AB32_3A2401E8092E__INCLUDED_)
#define AFX_WINDOWPLAY_H__30234095_FD28_4BDB_AB32_3A2401E8092E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWindowPlayApp:
// See WindowPlay.cpp for the implementation of this class
//

class CWindowPlayApp : public CWinApp
{
public:
	CWindowPlayApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWindowPlayApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWindowPlayApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINDOWPLAY_H__30234095_FD28_4BDB_AB32_3A2401E8092E__INCLUDED_)
