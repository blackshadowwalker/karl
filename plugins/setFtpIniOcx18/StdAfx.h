#if !defined(AFX_STDAFX_H__5FA101CF_A48D_4945_9D89_465BDF811D6B__INCLUDED_)
#define AFX_STDAFX_H__5FA101CF_A48D_4945_9D89_465BDF811D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// stdafx.h : include file for standard system include files,
//      or project specific include files that are used frequently,
//      but are changed infrequently

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxctl.h>         // MFC support for ActiveX Controls
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Comon Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// Delete the two includes below if you do not wish to use the MFC
//  database classes
#include <afxdb.h>			// MFC database classes
#include <afxdao.h>			// MFC DAO database classes

#include <comdef.h>//初始化一下com口
#include <GdiPlusHeaders.h>

 typedef unsigned long ULONG_PTR, *PULONG_PTR;
 #include <Gdiplus.h>
 using namespace Gdiplus;
 #pragma comment (lib, "GdiPlus.lib")

static ULONG_PTR m_pGdiToken;
static struct GdiplusStartupInput m_gdiplusStartupInput;

char m_windowPath[MAX_PATH]={0};
//	::GetCurrentDirectory(MAX_PATH, path);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__5FA101CF_A48D_4945_9D89_465BDF811D6B__INCLUDED_)
