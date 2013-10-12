// setIniOcx.cpp : Implementation of CSetIniOcxApp and DLL registration.

#include "stdafx.h"
#include "setIniOcx.h"
#include "comcat.h"
#include "strsafe.h"
#include "objsafe.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CSetIniOcxApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x16551f99, 0x27ed, 0x433d, { 0x9e, 0x36, 0x57, 0xcf, 0x1e, 0xd5, 0x87, 0xab } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;

const CATID CLSID_SafeItem =
		{ 0x16551f99, 0x27ed, 0x433d, { 0x9e, 0x36, 0x57, 0xcf, 0x1e, 0xd5, 0x87, 0xab } };

////////////////////////////////////////////////////////////////////////////
// CSetIniOcxApp::InitInstance - DLL initialization

BOOL CSetIniOcxApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	if (bInit)
	{
		// TODO: Add your own module initialization code here.
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CSetIniOcxApp::ExitInstance - DLL termination

int CSetIniOcxApp::ExitInstance()
{
	// TODO: Add your own module termination code here.

	return COleControlModule::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry
HRESULT CreateComponentCategory(CATID catid, WCHAR *catDescription)
{
    ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;
 
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (FAILED(hr))
        return hr;
 
    // Make sure the HKCR\Component Categories\{..catid...}
    // key is registered.
    CATEGORYINFO catinfo;
    catinfo.catid = catid;
    catinfo.lcid = 0x0409 ; // english

    // Make sure the provided description is not too long.
    // Only copy the first 127 characters if it is.
    // The second parameter of StringCchLength is the maximum
    // number of characters that may be read into catDescription.
    // There must be room for a NULL-terminator. The third parameter
    // contains the number of characters excluding the NULL-terminator.
	int len = wcslen(catDescription);    
    if (len>127) len = 127;    
    wcsncpy(catinfo.szDescription, catDescription, len);    
    // Make sure the description is null terminated.    
    catinfo.szDescription[len] = '\0';    
    hr = pcr->RegisterCategories(1, &catinfo);    
    pcr->Release();  
 
    return hr;
}
 
// HRESULT RegisterCLSIDInCategory -
//      Register your component categories information
 
HRESULT RegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
// Register your component categories information.
    ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
                NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (SUCCEEDED(hr))
    {
       // Register this category as being "implemented" by the class.
       CATID rgcatid[1] ;
       rgcatid[0] = catid;
       hr = pcr->RegisterClassImplCategories(clsid, 1, rgcatid);
    }
 
    if (pcr != NULL)
        pcr->Release();
            
    return hr;
}
 
// HRESULT UnRegisterCLSIDInCategory - Remove entries from the registry
 
HRESULT UnRegisterCLSIDInCategory(REFCLSID clsid, CATID catid)
{
    ICatRegister *pcr = NULL ;
    HRESULT hr = S_OK ;
 
    hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr, 
            NULL, CLSCTX_INPROC_SERVER, IID_ICatRegister, (void**)&pcr);
    if (SUCCEEDED(hr))
    {
       // Unregister this category as being "implemented" by the class.
       CATID rgcatid[1] ;
       rgcatid[0] = catid;
       hr = pcr->UnRegisterClassImplCategories(clsid, 1, rgcatid);
    }
 
    if (pcr != NULL)
        pcr->Release();
 
    return hr;
}

STDAPI DllRegisterServer(void)
{
    HRESULT hr;    // HResult used by Safety Functions
 
    AFX_MANAGE_STATE(_afxModuleAddrThis);
 
    if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
      return ResultFromScode(SELFREG_E_TYPELIB);
 
    if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
      return ResultFromScode(SELFREG_E_CLASS);
 
    // Mark the control as safe for initializing.
                                             
    hr = CreateComponentCategory(CATID_SafeForInitializing, 
         L"Controls safely initializable from persistent data!");
    if (FAILED(hr))
      return hr;
 
    hr = RegisterCLSIDInCategory(CLSID_SafeItem, 
         CATID_SafeForInitializing);
    if (FAILED(hr))
        return hr;
 
    // Mark the control as safe for scripting.
 
    hr = CreateComponentCategory(CATID_SafeForScripting, 
                                 L"Controls safely  scriptable!");
    if (FAILED(hr))
        return hr;
 
    hr = RegisterCLSIDInCategory(CLSID_SafeItem, 
                        CATID_SafeForScripting);
    if (FAILED(hr))
        return hr;
 
    return NOERROR;
}

STDAPI DllUnregisterServer(void)
{
    HRESULT hr;    // HResult used by Safety Functions
 
    AFX_MANAGE_STATE(_afxModuleAddrThis);
 
    if (!AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor))
      return ResultFromScode(SELFREG_E_TYPELIB);
 
    if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
      return ResultFromScode(SELFREG_E_CLASS);
 
    // Remove entries from the registry.
 
    hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, 
                     CATID_SafeForInitializing);
    if (FAILED(hr))
      return hr;
 
    hr=UnRegisterCLSIDInCategory(CLSID_SafeItem, 
                        CATID_SafeForScripting);
    if (FAILED(hr))
      return hr;
 
    return NOERROR;
}
