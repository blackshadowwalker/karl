// GetFramesFromAVIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GetFramesFromAVI.h"
#include "GetFramesFromAVIDlg.h"

#include <process.h> 

#include "cv.h"
#include "highgui.h"

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"highgui.lib")
#pragma comment(lib,"ml.lib")
#pragma comment(lib,"cvaux.lib")
#pragma comment(lib,"cvcam.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_UPDATE_ID		1
#define TIMER_UPDATE_INNERTIMER	10

static int nFrames = 0;

CString OpenFolder(CWnd *hWnd);


#define BIF_NEWDIALOGSTYLE 0x0040
CString OpenFolder(CWnd *hWnd)
{
	HWND hwnd= hWnd->GetSafeHwnd();   //得到窗口句柄
	CString filePath= "";		//得到文件路径			
	LPMALLOC pMalloc;
	if (::SHGetMalloc(&pMalloc) == NOERROR)		//取得IMalloc分配器接口
	{   
		BROWSEINFO		bi;
		TCHAR			pszBuffer[MAX_PATH];
		LPITEMIDLIST	pidl;   
		
		bi.hwndOwner		= hwnd;
		bi.pidlRoot			= NULL;
		bi.pszDisplayName   = pszBuffer;
		bi.lpszTitle		= _T("选择保存视频帧图片的文件夹"); //选择目录对话框的上部分的标题
		//添加新建文件夹按钮 BIF_NEWDIALOGSTYLE
		bi.ulFlags			=  BIF_NEWDIALOGSTYLE | BIF_RETURNONLYFSDIRS | BIF_RETURNFSANCESTORS;
		bi.lpfn				= NULL;
		bi.lParam			= 0;
		bi.iImage			= 0;
		if ((pidl = ::SHBrowseForFolder(&bi)) != NULL)  //取得IMalloc分配器接口
		{   
			if (::SHGetPathFromIDList(pidl, pszBuffer)) //获得一个文件系统路径
			{
				filePath = pszBuffer;
			}
			else filePath="";
			pMalloc->Free(pidl);	//释放内存
			
		//	MessageBox(m_strPath);
		}
		pMalloc->Release();			//释放接口
	}

	return filePath;
}

char *formatTime(time_t* t)
{
	struct tm *time;
	time = localtime(t);
	char *str = new char[256];
	memset(str, 0, 256);
	sprintf(str,"%d-%d-%d  %d.%d.%d", time->tm_year+1900, time->tm_mon+1, time->tm_mday, time->tm_hour, time->tm_min, time->tm_sec );
	return str;
}
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
// CGetFramesFromAVIDlg dialog

CGetFramesFromAVIDlg::CGetFramesFromAVIDlg(CWnd* pParent /*=NULL*/)
: CDialog(CGetFramesFromAVIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGetFramesFromAVIDlg)
	m_path = _T("d:\\savePic");
	m_aviPath = _T("");
	m_frameInterval = 2;
	m_frameFrom = 0;
	m_frameTo = 0;
	m_nFrame = _T("0");
	m_sleepTime = 0;
	m_rectHeight = 0;
	m_rectWidth = 0;
	m_rectX = 0;
	m_rectY = 0;
	m_runTimes = _T("");
	m_imageDepth = 0;
	m_imageChannel = 1;
	pause = false;
	bGetFrame = false;
	sleepTime = 1;
	startTime = 0;
	endTime = 0;
	m_imageHeight = 0;
	m_imageWidth = 0;
	pInfo = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetFramesFromAVIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGetFramesFromAVIDlg)
	DDX_Control(pDX, IDC_CHECK_SHOW, m_checkShow);
	DDX_Control(pDX, IDC_IMAGE, m_screen);
	DDX_Text(pDX, IDC_PATH, m_path);
	DDX_Text(pDX, IDC_AVI_PATH, m_aviPath);
	DDX_Text(pDX, IDC_FRAME_JG, m_frameInterval);
	DDV_MinMaxInt(pDX, m_frameInterval, 0, 999999);
	DDX_Text(pDX, IDC_FRAME_FROM, m_frameFrom);
	DDX_Text(pDX, IDC_FRAME_TO, m_frameTo);
	DDX_Text(pDX, IDC_NFRAME, m_nFrame);
	DDX_Text(pDX, IDC_SLEEP_TIME, m_sleepTime);
	DDV_MinMaxInt(pDX, m_sleepTime, 0, 999999);
	DDX_Text(pDX, IDC_RECT_HEIGHT, m_rectHeight);
	DDX_Text(pDX, IDC_RECT_WIDTH, m_rectWidth);
	DDX_Text(pDX, IDC_RECT_X, m_rectX);
	DDX_Text(pDX, IDC_RECT_Y, m_rectY);
	DDX_Text(pDX, IDC_RUN_RIMES, m_runTimes);
	DDX_Text(pDX, IDC_IMAGE_DEPTH, m_imageDepth);
	DDX_Text(pDX, IDC_IMAGE_CHANNEL, m_imageChannel);
	DDV_MinMaxInt(pDX, m_imageChannel, 1, 4);
	DDX_Text(pDX, IDC_IMAGE_HEIGHT, m_imageHeight);
	DDX_Text(pDX, IDC_IMAGE_WIDTH, m_imageWidth);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGetFramesFromAVIDlg, CDialog)
//{{AFX_MSG_MAP(CGetFramesFromAVIDlg)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
ON_BN_CLICKED(IDC_BT_BROWSWE, OnBtBrowswe)
ON_BN_CLICKED(IDC_BT_BROWSER_AVI, OnBtBrowserAvi)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BT_PAUSE, OnBtPause)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BT_START_GETFRAME, OnBtStartGetframe)
	ON_BN_CLICKED(IDC_SLOWER, OnSlower)
	ON_BN_CLICKED(IDC_FASTER, OnFaster)
	ON_BN_CLICKED(IDC_NORMAL, OnNormal)
	ON_BN_CLICKED(IDC_CHECK_SHOW, OnCheckShow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGetFramesFromAVIDlg message handlers

BOOL CGetFramesFromAVIDlg::OnInitDialog()
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
	m_screen.GetWindowRect(&screenRect);
	m_checkShow.SetCheck(true);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGetFramesFromAVIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetFramesFromAVIDlg::OnPaint() 
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
HCURSOR CGetFramesFromAVIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGetFramesFromAVIDlg::OnBtBrowswe() 
{
	CString str = OpenFolder(this);
	if(str.IsEmpty())
		return;
	m_path = str;
	UpdateData(false);
}

bool KCreateFolder(CString folder)
{
	folder += "/";
	folder.Replace("/","\\");
	int index=2;
	bool isOk = true;
	while(1)
	{
	//	folder.Delete(0, index+1);
		index = folder.Find("\\",index+1);
		index = index<0? folder.Find("/") : index;
		if(index<0) break;
		CString str = folder.Left(index);
		isOk = (BOOL)CreateDirectory( str, 0 );
		//if(!isOk） 
		//	return false;
	}
	return true;
}

void Karl_OnDraw(IplImage* img, CWnd *cWnd)
{	
/*	IplImage*  dst= cvCreateImage(cvGetSize(img), img->depth, img->nChannels);
cvCopy(img, dst, NULL);
cvNamedWindow( "显示图像", 1 );//创建窗口
cvShowImage( "显示图像", dst );//显示图像
	*/
	if(cWnd==NULL) return;
	CDC *pDC = cWnd->GetDC();
	HDC hDC= pDC->GetSafeHdc();
	CRect rect;
	cWnd->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img);
	cimg.DrawToHDC(hDC,&rect);
	cWnd->ReleaseDC(pDC);
	
}

void savePictures(void* pParam)
{
	ProcessInfo *stu ;
	stu = (ProcessInfo*)pParam;
	CGetFramesFromAVIDlg *dlg =  (CGetFramesFromAVIDlg*)stu->pParam;
	dlg->Proc(stu);
}

bool CGetFramesFromAVIDlg::SetAviProperty()
{
	CoInitialize(NULL);//初始化com,否则多线程中的cvCaptureFromFile 不能再次使用
	CvCapture* capture=0;
	capture = cvCaptureFromFile( m_aviPath);
	bool isRright = false;
	if( capture )
    {
		m_frameTo = cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_COUNT);
        while(1)
        {
			IplImage* image = cvQueryFrame( capture );
			if( image)
			{
				m_rectWidth = m_imageWidth = image->width;
				m_rectHeight= m_imageHeight = image->height;
				m_imageChannel = image->nChannels;
				m_imageDepth = image->depth;
				isRright = true;
				break;
			}
			if( !cvGrabFrame( capture ))
                break;
		}
		cvReleaseCapture( &capture );
    }	
	CoUninitialize();

	return isRright;
}



void CGetFramesFromAVIDlg::Proc(ProcessInfo *pstu )
{
	if(pstu==NULL)
		return;
	ProcessInfo *stu = new ProcessInfo;
	stu->pParam = pstu->pParam;
	stu->frameInterval = pstu->frameInterval;
	sprintf(stu->aviPath, "%s", pstu->aviPath);
	sprintf(stu->dstPath, "%s", pstu->dstPath);

	CGetFramesFromAVIDlg *dlg = (CGetFramesFromAVIDlg*)stu->pParam;
	
	if(strlen(stu->aviPath)<2 || strlen(stu->aviPath)<2 )
		return; 
	
	CString dstPath(stu->dstPath);
	CString aviPath(stu->aviPath);
	char savePath[256]={0};

	bool showin = false;
	
	char aviFilePath[256]={0};
	sprintf(aviFilePath, "%s", aviPath);
//	LPWSTR out;
//	Utf82Unicode(out,outsize, aviFilePath, strlen(aviFilePath);
	
	CoInitialize(NULL);//初始化com,否则多线程中的cvCaptureFromFile 不能再次使用
	CvCapture* capture=0;
	capture = cvCaptureFromFile( aviFilePath);

	CWnd *window = GetDlgItem(IDC_IMAGE);
	if( capture )
    {
		nFrames = 0;
		bool bInit = false;
		CvRect imageRect;	
		IplImage* img =0;
        while(1)
        {
			if(!isRun)
				break;
			while(pause)
			{
				if(!isRun)
					break;
				Sleep(100);
			}
			nFrames++;
			dlg->m_nFrame.Format("%d", nFrames);

			IplImage* image = cvQueryFrame( capture );
			
			if( !cvGrabFrame( capture ))
                break;
			
            if( image )
            {
				if(!bInit)
				{
					if(image->origin==0)
						imageRect = cvRect(dlg->m_rectX, dlg->m_rectY,  dlg->m_rectWidth, dlg->m_rectHeight);
					else
						imageRect = cvRect(dlg->m_rectX, (dlg->m_imageHeight - dlg->m_rectY) - dlg->m_rectHeight ,  dlg->m_rectWidth, dlg->m_rectHeight);

					img = cvCreateImage(cvSize(dlg->m_rectWidth, dlg->m_rectHeight), dlg->m_imageDepth, dlg->m_imageChannel);
					bInit = true;
				}
				if ( dlg->m_frameInterval > 0 && nFrames%dlg->m_frameInterval  !=0 )
				{
					continue;
				}
			
				if(dlg->m_bShow)
					Karl_OnDraw(image, window);				
            	
				if(bGetFrame)
				{
					if ( nFrames < dlg->m_frameFrom )
						continue;
					if ( nFrames > dlg->m_frameTo )
					{
						dlg->OnBtStartGetframe();
						break;
					}
					//
					img->origin = 1;
					cvSetImageROI(image, imageRect);
					cvCopy(image, img);
					cvResetImageROI(image);
					

					sprintf(savePath, "%s\\%d.jpg", dstPath, nFrames);
					cvSaveImage(savePath, img);
				}
            }
			int sleepTime = abs(dlg->m_sleepTime) + 3 ;
			Sleep(sleepTime);
        }
		cvReleaseCapture( &capture );
		dlg->endTime = time(NULL);
		dlg->m_runTimes.Format("%d ", dlg->endTime - dlg->startTime);
    }	
	CoUninitialize();
	delete stu;
}


void CGetFramesFromAVIDlg::OnButton2() 
{
	UpdateData(true);
	
	startTime = time(NULL);

	if(pInfo!=0)
		delete pInfo;
	pInfo = new ProcessInfo;
	memset(pInfo , 0, sizeof(ProcessInfo));
	pInfo->frameInterval = m_frameInterval;
	sprintf(pInfo->aviPath,"%s",m_aviPath);
	sprintf(pInfo->dstPath, "%s", m_path);
	pInfo->pParam = this;
	pInfo->bShow = this->m_checkShow.GetCheck();
	m_bShow = this->m_checkShow.GetCheck();

	KCreateFolder(m_aviPath);
	KCreateFolder(m_path);

	SetTimer( TIMER_UPDATE_ID, TIMER_UPDATE_INNERTIMER, 0);

	isRun = true;
	pause = false;
	_beginthread(savePictures, 0 ,pInfo); 

}


void CGetFramesFromAVIDlg::OnBtBrowserAvi() 
{
	UpdateData(true);
	CFileDialog fileOpenDlg(TRUE, _T("*.avi"), "",OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|OFN_HIDEREADONLY,
		"avi files (*.avi) |*.avi;|All Files (*.*)|*.*||",NULL);
	if (fileOpenDlg.DoModal()!=IDOK) return ;
	
	m_aviPath = fileOpenDlg.GetPathName();

	SetAviProperty();

	UpdateData(false);
}


void CGetFramesFromAVIDlg::OnButton1() 
{
	UpdateData(true);
	isRun = false;
	Sleep(100);
	KillTimer(TIMER_UPDATE_ID);
	UpdateData(false);
}

void CGetFramesFromAVIDlg::OnCancel() 
{
	isRun = false;	
	OnButton1();
	Sleep(500);
	
	CRect r;
	this->GetWindowRect(&r);
	int dt = r.Height()/30;
	while(r.Height()>10)
	{
		r.bottom -= dt;
		r.top	+= dt;
		this->MoveWindow(r);
		Sleep(10);
	}
	exit(0);
}

void CGetFramesFromAVIDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	CRect r2 ;
	CRect r;
	this->GetWindowRect(&r);
	ScreenToClient(&r);
	CRect rnew = screenRect;
	rnew.right = r.right - 5;
	rnew.bottom = r.bottom - 5;
	rnew.left = 0;
	
	if(m_screen.m_hWnd != NULL)	
	{
		GetDlgItem(IDC_NFRAME)->GetWindowRect(&r2);
		ScreenToClient(&r2);
		rnew.top = r2.bottom +5 ;
		m_screen.MoveWindow(rnew);		
	}
}

void CGetFramesFromAVIDlg::OnBtPause() 
{
	pause = !pause;
	UpdateData(true);
	if(pause)
	{
		KillTimer(TIMER_UPDATE_ID);
		GetDlgItem(IDC_BT_PAUSE)->SetWindowText("Resume");
	}
	else
	{
		SetTimer(TIMER_UPDATE_ID, TIMER_UPDATE_INNERTIMER, 0);
		GetDlgItem(IDC_BT_PAUSE)->SetWindowText("Pause");
	}
	
}

void CGetFramesFromAVIDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==TIMER_UPDATE_ID)
	{
		UpdateData(false);
	}
		
	CDialog::OnTimer(nIDEvent);
}

void CGetFramesFromAVIDlg::OnButton4() 
{
	UpdateData(true);
	m_frameFrom = atol(m_nFrame.GetBuffer(m_nFrame.GetLength()));
	UpdateData(false);
}

void CGetFramesFromAVIDlg::OnButton5() 
{
	UpdateData(true);
	m_frameTo = atol(m_nFrame.GetBuffer(m_nFrame.GetLength()));
	UpdateData(false);
}

void CGetFramesFromAVIDlg::OnBtStartGetframe() 
{
	bGetFrame = !bGetFrame;
	if(bGetFrame)
	{
		if(m_frameFrom > m_frameTo)
		{
			MessageBox("结束帧不能小于开始帧!","", MB_OK);
			bGetFrame = false;
		}
		GetDlgItem(IDC_BT_START_GETFRAME)->SetWindowText("停止取帧");
	}
	else
	{
		GetDlgItem(IDC_BT_START_GETFRAME)->SetWindowText("开始取帧");
	}
}

void CGetFramesFromAVIDlg::OnSlower() 
{
	//慢进
	m_sleepTime += 10;
	UpdateData(false);
}

void CGetFramesFromAVIDlg::OnFaster() 
{
	//快进
	if(m_sleepTime<=0)
	{
		m_frameInterval++;
	}
	else
		m_sleepTime -= 10;
	UpdateData(false);
	
}

void CGetFramesFromAVIDlg::OnNormal() 
{	
	//正常播放	
	m_sleepTime = 0;
	m_frameInterval = 0;
	UpdateData(false);

}


void CGetFramesFromAVIDlg::OnCheckShow() 
{
	m_bShow = !m_checkShow.GetCheck();
	m_checkShow.SetCheck(m_bShow);
	UpdateData(false);
}
