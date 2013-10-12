// SetIniOcxPpg.cpp : Implementation of the CSetIniOcxPropPage property page class.

#include "stdafx.h"
#include "setIniOcx.h"
#include "SetIniOcxPpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSetIniOcxPropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSetIniOcxPropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(CSetIniOcxPropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSetIniOcxPropPage, "SETINIOCX.SetIniOcxPropPage.1",
	0xcfec386a, 0x7907, 0x4b8f, 0x95, 0x98, 0x28, 0x59, 0x6, 0x95, 0xe4, 0x26)


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxPropPage::CSetIniOcxPropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for CSetIniOcxPropPage

BOOL CSetIniOcxPropPage::CSetIniOcxPropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_SETINIOCX_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxPropPage::CSetIniOcxPropPage - Constructor

CSetIniOcxPropPage::CSetIniOcxPropPage() :
	COlePropertyPage(IDD, IDS_SETINIOCX_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(CSetIniOcxPropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxPropPage::DoDataExchange - Moves data between page and properties

void CSetIniOcxPropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(CSetIniOcxPropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxPropPage message handlers
