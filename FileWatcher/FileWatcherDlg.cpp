// FileWatcherDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileWatcher.h"
#include "FileWatcherDlg.h"

#include <windows.h>  
#include <process.h>

#include "public.h"

#include "cv.h"
#include "cxcore.h"
#include "highgui.h"

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"highgui.lib")

#define IMAGE_WIDTH 200
#define IMAGE_HEIGHT 150


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HANDLE m_handle;
HANDLE hMutex;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileWatcherDlg dialog

CFileWatcherDlg::CFileWatcherDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileWatcherDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileWatcherDlg)
	m_dir = _T("D:\\watcher");
	bWatching = false;
	m_imageWidth = 200;
	m_imageHeight = 150;
	bStopProcess = true;
	bStopedProcess = true;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileWatcherDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileWatcherDlg)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Control(pDX, IDC_LIST_WATCHER, m_wlist);
	DDX_Text(pDX, IDC_DIR, m_dir);
	DDX_Text(pDX, IDC_IMAGE_WIDTH, m_imageWidth);
	DDV_MinMaxInt(pDX, m_imageWidth, 1, 9999);
	DDX_Text(pDX, IDC_IMAGE_HEIGHT, m_imageHeight);
	DDV_MinMaxInt(pDX, m_imageHeight, 1, 9999);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileWatcherDlg, CDialog)
	//{{AFX_MSG_MAP(CFileWatcherDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BT_WATCH, OnBtWatch)
	ON_BN_CLICKED(IDC_BT_BROWSER_DIR, OnBtBrowserDir)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BT_LOG, OnBtLog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BT_RESET_WH, OnBtResetWh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileWatcherDlg message handlers

BOOL CFileWatcherDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	ReadConfig();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileWatcherDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileWatcherDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileWatcherDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



//process images
UINT ThreadProcess(LPVOID pParam){

	CFileWatcherDlg * dlg = (CFileWatcherDlg*)pParam;

	IplImage* img=0;
	IplImage* img12=0;
	CString imagePath="";
	int index;
	while(true){

		if(dlg->bStopProcess)
			break;

		WaitForSingleObject(hMutex,-1);//waiting signal

		if(dlg->m_images.size()<1){
			ReleaseMutex(hMutex);
			Sleep(50);
			continue;
		}
		imagePath = dlg->m_images.front();
		dlg->m_images.pop_front();
		ReleaseMutex(hMutex);//release signal

		//	CFile mFile(_T(image),CFile::modeRead);
		index = imagePath.Find("_small.jpg");
		if(index>0){
			continue;
		}
		dlg->PrintMsg("cvLoadImage : "+imagePath);
		img=cvLoadImage(imagePath);
		if(img==0){
			continue;
		}
		img12=cvCreateImage(cvSize(dlg->m_imageWidth, dlg->m_imageHeight),8,3);
		cvResize(img,img12,CV_INTER_NN);
		cvSaveImage(imagePath+"_small.jpg", img12);
		cvReleaseImage(&img);
		cvReleaseImage(&img12);
		
	}
	dlg->bStopedProcess = true;

	return 0;
}

UINT ThreadWatcher(LPVOID pParam){

	CFileWatcherDlg * dlg = (CFileWatcherDlg*)pParam;
//	dlg->MessageBox(dlg->m_dir);

	HANDLE hDir; 
	char notify[1024]; 
	DWORD cbBytes; 
	char AnsiChar[3]; 
	wchar_t UnicodeChar[2]; 
	CString path = dlg->m_dir;

	FILE_NOTIFY_INFORMATION *pNotify=(FILE_NOTIFY_INFORMATION *)notify; 

//	GetCurrentDirectory(MAX_PATH,path.GetBuffer(MAX_PATH+1));

    hDir = CreateFile( path, FILE_LIST_DIRECTORY,
        FILE_SHARE_READ | 
        FILE_SHARE_WRITE | 
        FILE_SHARE_DELETE, NULL, 
        OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | 
        FILE_FLAG_OVERLAPPED, NULL); 
    if (hDir == INVALID_HANDLE_VALUE) 
    { 
		dlg->PrintMsg("hDir:INVALID_HANDLE_VALUE");
        //dlg->m_edit.ReplaceSel("hDir:INVALID_HANDLE_VALUE\r\n");
        return 0;
    } 
	CString str;
	
	WCHAR  wcFileName[1024]={0};
	DWORD dwFileNameLength ;
	char cFileName[1024] = {0};

	while (TRUE) 
    { 
		if(!dlg->bWatching)
			break;
        if(ReadDirectoryChangesW(hDir, &notify, sizeof(notify),
            true, FILE_NOTIFY_CHANGE_FILE_NAME| FILE_NOTIFY_CHANGE_LAST_WRITE  , 
            &cbBytes, NULL, NULL)) 
        { 
 
		//	dlg->MessageBox("re");
			dwFileNameLength = pNotify->FileNameLength;  
			memset(wcFileName, 0 , 1024);
			memcpy( wcFileName, pNotify->FileName, dwFileNameLength );
			WideCharToMultiByte( CP_ACP, 0, wcFileName, -1, cFileName, 1024, NULL, NULL );
			
            switch(pNotify->Action) 
            { 
            case FILE_ACTION_ADDED: 
				str.Format("Directory/File added - %s",cFileName);
                break; 
            case FILE_ACTION_REMOVED:
				str.Format("Directory/File removed - %s",cFileName);
                break; 
            case FILE_ACTION_MODIFIED: 
				WaitForSingleObject(hMutex,-1);//waiting
				dlg->m_images.push_back(path+"\\"+cFileName);
				str.Format("STL list size=%d ", dlg->m_images.size());
				dlg->PrintMsg(str);
				ReleaseMutex(hMutex);//release 
				str.Format("Directory/File modified - %s",cFileName);
                break; 
            case FILE_ACTION_RENAMED_OLD_NAME: 
				str.Format("Directory/File rename - %s",cFileName);
                break; 
            case FILE_ACTION_RENAMED_NEW_NAME: 
				str.Format("Directory/File new name - %s",cFileName);
                break; 
            default: 
                break; 
            } 
			dlg->PrintMsg(str);
			
        }
    }
	dlg->PrintMsg("End Watcher");
	return 0;
}

void CFileWatcherDlg::OnBtWatch() 
{
	UpdateData(true);
	if(!bWatching)
	{
		bWatching = true;
		bStopProcess = false;
		AfxBeginThread(ThreadWatcher, this);
		AfxBeginThread(ThreadProcess, this);
		PrintMsg("Start Watcher");
		CString str;
		str.Format("STL list MAX size=%d ", m_images.max_size());
		PrintMsg(str);
		GetDlgItem(IDC_BT_WATCH)->SetWindowText("Stop");
	}else{
		bWatching = false;
		bStopProcess = true;
		GetDlgItem(IDC_BT_WATCH)->SetWindowText("Watch");
	}
}

void CFileWatcherDlg::OnBtBrowserDir() 
{
	UpdateData(true);
	CString dir = SelectFolder(this);	
	if(dir!=""){
		m_dir = dir;
		UpdateData(false);
		SaveConfig();
	}
	
}

void CFileWatcherDlg::PrintMsg(CString str)
{
	printf("[%s] ListSize=%d , %s\n", getNowTime(), m_wlist.GetCount(), str);//this的路径
	m_wlist.AddString(str);
	if(m_wlist.GetCount()>50)
		m_wlist.ResetContent();	
	m_wlist.SetCurSel(m_wlist.GetCount());

//	EventLog(str.GetBuffer(str.GetLength()));
	GetDlgItem(IDC_EDIT1)->SetWindowText(str);

}

void CFileWatcherDlg::OnButton1() 
{
	m_wlist.ResetContent();	
	PrintMsg("list.ResetContent");
}

void CFileWatcherDlg::OnBtLog() 
{
	CString cmd ;
	cmd.Format("%s", logFile);
	ShellExecute(NULL,"open", logFile ,NULL,NULL,SW_SHOWNORMAL);
	printf("[%s] %s\n", getNowTime(), cmd);//this的路径
		
}

bool CFileWatcherDlg::ReadConfig()
{
	char lpFileName[512]={0};
	char retString[512]={0};
	sprintf(lpFileName,"%s\\FileWatcherConfig.ini",CFileWatcherApp::m_appPath);
	
	int retNum = GetPrivateProfileString("config","dir","", retString, 512, lpFileName);
	if(retString!="");
		m_dir.Format("%s",retString);
	UpdateData(false);

	return true;
}


bool CFileWatcherDlg::SaveConfig()
{
	UpdateData(true);
	char lpFileName[512]={0};
	char retString[512]={0};
	sprintf(lpFileName,"%s\\FileWatcherConfig.ini",CFileWatcherApp::m_appPath);

	WritePrivateProfileString("config","dir", m_dir, lpFileName);

	return true;
}

void CFileWatcherDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	CRect wr;
	this->GetWindowRect(&wr);
	ScreenToClient(&wr);
	if(m_wlist.m_hWnd != NULL)	
	{
		CRect m_oldRect;
		m_wlist.GetWindowRect(&m_oldRect);
		ScreenToClient(&m_oldRect);
		CRect rnew = m_oldRect;
		rnew.right = wr.right-15;
		rnew.bottom = wr.bottom-50;
		m_wlist.MoveWindow(rnew);	
	}
	if(m_edit.m_hWnd != NULL)	
	{
		CRect m_oldRect;
		m_edit.GetWindowRect(&m_oldRect);
		ScreenToClient(&m_oldRect);
		CRect rnew = m_oldRect;
		rnew.right = wr.right-15;
		rnew.bottom = wr.bottom-15;
		rnew.top = rnew.bottom -25;
		m_edit.MoveWindow(rnew);	
	}
		
}

void CFileWatcherDlg::OnButton2() 
{
	//clear log file
	
}

void CFileWatcherDlg::OnBtResetWh() 
{
	UpdateData(true);
	/*
	bStopProcess = true;
	while(!bStopedProcess)
		Sleep(100);
	*/
}
