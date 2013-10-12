// GridViewTest.h : main header file for the GRIDVIEWTEST application
//

#if !defined(AFX_GRIDVIEWTEST_H__7071AA7D_EC2E_4DAC_A0F0_0C46B46A7B96__INCLUDED_)
#define AFX_GRIDVIEWTEST_H__7071AA7D_EC2E_4DAC_A0F0_0C46B46A7B96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CGridViewTestApp:
// See GridViewTest.cpp for the implementation of this class
//

class CGridViewTestApp : public CWinApp
{
public:
	CGridViewTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridViewTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGridViewTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEWTEST_H__7071AA7D_EC2E_4DAC_A0F0_0C46B46A7B96__INCLUDED_)
