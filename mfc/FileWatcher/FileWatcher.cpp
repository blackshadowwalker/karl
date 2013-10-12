// FileWatcher.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FileWatcher.h"
#include "FileWatcherDlg.h"

#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CFileWatcherApp

BEGIN_MESSAGE_MAP(CFileWatcherApp, CWinApp)
	//{{AFX_MSG_MAP(CFileWatcherApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileWatcherApp construction

CFileWatcherApp::CFileWatcherApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFileWatcherApp object

CFileWatcherApp theApp;

CString CFileWatcherApp::m_appPath="";
FILE *CFileWatcherApp::g_logFile=0;
CString CFileWatcherApp::g_logFilePath="";

#pragma comment(lib, "lib/SkinPPWTL.lib")
/////////////////////////////////////////////////////////////////////////////
// CFileWatcherApp initialization

BOOL CFileWatcherApp::InitInstance()
{
	skinppLoadSkin(_T("skin/AquaOS.ssk"));

	CString g_szOcxPath = this->m_pszHelpFilePath;
	CString g_szOcxName = this->m_pszExeName;

	g_szOcxName += ".HLP";
	int nTmp = g_szOcxName.GetLength();
	nTmp = g_szOcxPath.GetLength() - nTmp;
	g_szOcxPath = g_szOcxPath.Left(nTmp);

	memset(EventLogFile, 0 , 256);
//	CString g_szPath  = g_GetIniPath();
	m_appPath = g_szOcxPath;
	KCreateFolder(g_szOcxPath+"\\log");
	sprintf(EventLogFile, "%s\\log\\ITSEventLog.log", g_szOcxPath );



	if(!FindFirstFileExists((PTSTR)EventLog, FALSE))
	{
		g_logFile = freopen(EventLogFile, "a+",stdout);
		printf("");
	}
	else
		g_logFile = freopen(EventLogFile, "a+",stdout);

	g_logFilePath = EventLogFile;

	printf("[g_szPath]=%s\n", g_szOcxPath);//thisµÄÂ·¾¶

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	CFileWatcherDlg dlg;
	m_pMainWnd = &dlg;
	dlg.logFile.Format("%s", EventLogFile);
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

