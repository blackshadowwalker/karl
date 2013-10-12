// SetIniOcxCtl.cpp : Implementation of the CSetIniOcxCtrl ActiveX Control class.

#include "stdafx.h"
#include "setIniOcx.h"
#include "SetIniOcxCtl.h"
#include "SetIniOcxPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CSetIniOcxCtrl, COleControl)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CSetIniOcxCtrl, COleControl)
	//{{AFX_MSG_MAP(CSetIniOcxCtrl)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(OCM_COMMAND, OnOcmCommand)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CSetIniOcxCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CSetIniOcxCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "SetFtpInfoDlg", dispidSetFtpInfoDlg, SetFtpInfoDlg, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "DownLoadInfo", dispidDownLoadInfo, DownLoadInfo, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "UpLoadInfo", dispidUpLoadInfo, UpLoadInfo, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "SetLaneDlg", dispidSetLaneDlg, SetLaneDlg, VT_BOOL, VTS_NONE)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "SetDoConfigDlg", dispidSetDoConfigDlg, SetDoConfigDlg, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "SetTimeConfigdlg", dispidSetTimeConfigdlg, SetTimeConfigdlg, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "SetFtpInfo", dispidSetFtpInfo, SetFtpInfo, VT_BOOL, VTS_BSTR VTS_I4 VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_BSTR)
	DISP_FUNCTION_ID(CSetIniOcxCtrl, "GetFtpInfo", dispidGetFtpInfo, GetFtpInfo, VT_BSTR, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CSetIniOcxCtrl, COleControl)
	//{{AFX_EVENT_MAP(CSetIniOcxCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CSetIniOcxCtrl, 1)
	PROPPAGEID(CSetIniOcxPropPage::guid)
END_PROPPAGEIDS(CSetIniOcxCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CSetIniOcxCtrl, "SETINIOCX.SetIniOcxCtrl.1",
	0x7c723a0a, 0xeac5, 0x4163, 0x8b, 0x9, 0xad, 0x6e, 0x15, 0x94, 0xf7, 0xf5)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CSetIniOcxCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DSetIniOcx =
		{ 0x20731cb3, 0x91f9, 0x48b2, { 0x87, 0x85, 0xd9, 0xf2, 0x92, 0x44, 0xfe, 0xa9 } };
const IID BASED_CODE IID_DSetIniOcxEvents =
		{ 0x38ad2a45, 0xf642, 0x47aa, { 0xa6, 0x48, 0xdc, 0x5e, 0xbc, 0xc0, 0x91, 0x85 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwSetIniOcxOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CSetIniOcxCtrl, IDS_SETINIOCX, _dwSetIniOcxOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::CSetIniOcxCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CSetIniOcxCtrl

BOOL CSetIniOcxCtrl::CSetIniOcxCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	// TODO: Verify that your control follows apartment-model threading rules.
	// Refer to MFC TechNote 64 for more information.
	// If your control does not conform to the apartment-model rules, then
	// you must modify the code below, changing the 6th parameter from
	// afxRegApartmentThreading to 0.

	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_SETINIOCX,
			IDB_SETINIOCX,
			afxRegApartmentThreading,
			_dwSetIniOcxOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Licensing strings

static const TCHAR BASED_CODE _szLicFileName[] = _T("setIniOcx.lic");

static const WCHAR BASED_CODE _szLicString[] =
	L"Copyright (c) 2012 ";


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::CSetIniOcxCtrlFactory::VerifyUserLicense -
// Checks for existence of a user license

BOOL CSetIniOcxCtrl::CSetIniOcxCtrlFactory::VerifyUserLicense()
{
	return AfxVerifyLicFile(AfxGetInstanceHandle(), _szLicFileName,
		_szLicString);
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::CSetIniOcxCtrlFactory::GetLicenseKey -
// Returns a runtime licensing key

BOOL CSetIniOcxCtrl::CSetIniOcxCtrlFactory::GetLicenseKey(DWORD dwReserved,
	BSTR FAR* pbstrKey)
{
	if (pbstrKey == NULL)
		return FALSE;

	*pbstrKey = SysAllocString(_szLicString);
	return (*pbstrKey != NULL);
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::CSetIniOcxCtrl - Constructor

CSetIniOcxCtrl::CSetIniOcxCtrl()
{
	InitializeIIDs(&IID_DSetIniOcx, &IID_DSetIniOcxEvents);

	// TODO: Initialize your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::~CSetIniOcxCtrl - Destructor

CSetIniOcxCtrl::~CSetIniOcxCtrl()
{
	// TODO: Cleanup your control's instance data here.
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::OnDraw - Drawing function

void CSetIniOcxCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	if (!pdc)	return;

	DoSuperclassPaint(pdc, rcBounds);

	m_dlg.MoveWindow(rcBounds, TRUE);
//	CBrush brBackGnd(TranslateColor(AmbientBackColor()));
	CBrush brBackGnd(RGB(100,100,250));

	pdc->FillRect(rcBounds, &brBackGnd);
	
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::DoPropExchange - Persistence support

void CSetIniOcxCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::OnResetState - Reset control to default state

void CSetIniOcxCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::AboutBox - Display an "About" box to the user

void CSetIniOcxCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_SETINIOCX);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::PreCreateWindow - Modify parameters for CreateWindowEx

BOOL CSetIniOcxCtrl::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.lpszClass = _T("STATIC");
	return COleControl::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::IsSubclassedControl - This is a subclassed control

BOOL CSetIniOcxCtrl::IsSubclassedControl()
{
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl::OnOcmCommand - Handle command messages

LRESULT CSetIniOcxCtrl::OnOcmCommand(WPARAM wParam, LPARAM lParam)
{
#ifdef _WIN32
	WORD wNotifyCode = HIWORD(wParam);
#else
	WORD wNotifyCode = HIWORD(lParam);
#endif

	// TODO: Switch on wNotifyCode here.

	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CSetIniOcxCtrl message handlers

int CSetIniOcxCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (COleControl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_dlg.Create(IDD_SET_FRAM_DLG, this);	
	m_dlg.m_r = 100;
	m_dlg.m_g = 200;
	m_dlg.m_b = 250;

	return 0;
}

void CSetIniOcxCtrl::SetFtpInfoDlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	m_dlg.OnBtSetftp();
}

VARIANT_BOOL CSetIniOcxCtrl::DownLoadInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_dlg.OnDownLoadIni();

	return VARIANT_TRUE;
}

VARIANT_BOOL CSetIniOcxCtrl::UpLoadInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_dlg.OnUploadIni();

	return VARIANT_TRUE;
}

VARIANT_BOOL CSetIniOcxCtrl::SetLaneDlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_dlg.OnLane();

	return VARIANT_TRUE;
}

void CSetIniOcxCtrl::SetDoConfigDlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_dlg.OnDoconfig();
}

void CSetIniOcxCtrl::SetTimeConfigdlg(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_dlg.OnTimeConfig();
}

VARIANT_BOOL CSetIniOcxCtrl::SetFtpInfo(LPCTSTR Ip, LONG Port, LPCTSTR userName, LPCTSTR passWord, LPCTSTR serverPath, LPCTSTR localPath,BSTR cameraName, LONG fileSum, LPCTSTR fileList)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

//	char *ip= (LPSTR)(LPCTSTR)Ip; // This can be OK
	bool isOk = m_dlg.SetFtpInfo( (LPSTR)(LPCTSTR)Ip,
					Port,
					(LPSTR)(LPCTSTR)userName,
					(LPSTR)(LPCTSTR)passWord,
					(LPSTR)(LPCTSTR)serverPath,
					(LPSTR)(LPCTSTR)localPath,
					(LPSTR)(LPCTSTR)cameraName,
					fileSum,
					fileList);

//	MessageBox("SetFtpInfo","",MB_OK);
	if(isOk)
		return VARIANT_TRUE;
	else 
		return VARIANT_FALSE;
}

BSTR CSetIniOcxCtrl::GetFtpInfo(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString strResult = m_dlg.GetFtpInfo();

	return strResult.AllocSysString();
}
