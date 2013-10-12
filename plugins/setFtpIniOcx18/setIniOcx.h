#if !defined(AFX_SETINIOCX_H__79C02676_2E01_4A06_9670_DE22160DE185__INCLUDED_)
#define AFX_SETINIOCX_H__79C02676_2E01_4A06_9670_DE22160DE185__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// setIniOcx.h : main header file for SETINIOCX.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxApp : See setIniOcx.cpp for implementation.

class CSetIniOcxApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETINIOCX_H__79C02676_2E01_4A06_9670_DE22160DE185__INCLUDED)
