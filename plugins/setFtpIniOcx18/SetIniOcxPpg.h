#if !defined(AFX_SETINIOCXPPG_H__5ECE2846_D5A2_4DFC_A8D9_D58BCE6BD8F7__INCLUDED_)
#define AFX_SETINIOCXPPG_H__5ECE2846_D5A2_4DFC_A8D9_D58BCE6BD8F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SetIniOcxPpg.h : Declaration of the CSetIniOcxPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CSetIniOcxPropPage : See SetIniOcxPpg.cpp.cpp for implementation.

class CSetIniOcxPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CSetIniOcxPropPage)
	DECLARE_OLECREATE_EX(CSetIniOcxPropPage)

// Constructor
public:
	CSetIniOcxPropPage();

// Dialog Data
	//{{AFX_DATA(CSetIniOcxPropPage)
	enum { IDD = IDD_PROPPAGE_SETINIOCX };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CSetIniOcxPropPage)
		// NOTE - ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETINIOCXPPG_H__5ECE2846_D5A2_4DFC_A8D9_D58BCE6BD8F7__INCLUDED)
