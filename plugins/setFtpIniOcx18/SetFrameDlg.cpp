// SetFrameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "SetFrameDlg.h"

#include "public.h"
#include "UpDownFile.h"
/*
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cvaux.lib")
#pragma comment(lib,"highgui.lib")
#pragma comment(lib,"cvcam.lib")
*/
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetFrameDlg dialog


CSetFrameDlg::CSetFrameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetFrameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetFrameDlg)
		img=0;
	//}}AFX_DATA_INIT
}


void CSetFrameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetFrameDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetFrameDlg, CDialog)
	//{{AFX_MSG_MAP(CSetFrameDlg)
	ON_BN_CLICKED(IDC_VEHICLE, OnVehicle)
	ON_BN_CLICKED(IDC_LIGHT, OnLight)
	ON_BN_CLICKED(IDC_LANE, OnLane)
	ON_BN_CLICKED(IDC_DOCONFIG, OnDoconfig)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnUploadIni)
	ON_BN_CLICKED(IDC_BUTTON2, OnDownLoadIni)
	ON_WM_DROPFILES()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BT_SETFTP, OnBtSetftp)
	ON_BN_CLICKED(IDC_TIME_CONFIG, OnTimeConfig)
	ON_WM_TIMER()

	ON_MESSAGE(TF_FTP_MESSAGE, OnTFFtpMessage) //此行添加代码定义唯一消息
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetFrameDlg message handlers



BOOL CSetFrameDlg::OnInitDialog() 
{
	
	CDialog::OnInitDialog();

	// init Socket
	{WSADATA data;	WSAStartup(MAKEWORD(2,2), &data);}
	

	m_progress= new CProgress;
	m_progress->Create(IDD_PROGRESS, this);

	m_brush.CreateSolidBrush (RGB(m_r, m_g, m_b));

	memset(&m_OperationConfig.mysOperate,0,sizeof(Tel_Operate));

	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	memset(&ftpData,0,sizeof(FTP_THREAD_DATA));

	if (!readConfig()) return false;

	RemoveDir(ftpData.localPath);//清空临时目录
	CString scmd; 
//	scmd.Format("rd/s/q  %s ", ftpData.localPath); system(scmd);//清空临时目录
	scmd.Format("%s\\%s", ftpData.localPath, ftpData.cCameraName);
	KCreateFolder(scmd);//创建临时目录

//	OnDownLoadIni();//自动下载文件
	
	this->ShowWindow(SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetFrameDlg::ShowPic(Image* img)
{	
	if(img==0) return;
//	cvNamedWindow("Picture",1);	cvShowImage("Picture",img);
	CRect rect;
	GetDlgItem(IDC_IMAGE)->GetClientRect(&rect);
//	DrawImg2Hdc( img, IDC_IMAGE, this, rect);

}

void CSetFrameDlg::OnVehicle() 
{
	m_VehicleCalibration.img = img;
	m_VehicleCalibration.DoModal();
}

void CSetFrameDlg::OnLight() 
{
	m_LightConfig.img = img;
	m_LightConfig.DoModal();
}

void CSetFrameDlg::OnLane() 
{
	m_LaneConfig.img = img;
	if(m_LaneConfig.DoModal()!=IDOK)
		return;
	int len= sizeof(Tel_LaneConfig);

	char path[MAX_PATH]={0};
	sprintf( path, "%s\\%s\\LaneConfig.dat", ftpData.localPath, ftpData.cCameraName);
	FILE* pLane = fopen(path,"w");
	int len2 = fwrite(&m_LaneConfig.tempLaneConfig, sizeof(Tel_LaneConfig),1,pLane);
	fclose(pLane);
	AfxMessageBox("存储完成");
}
void CSetFrameDlg::OnTimeConfig() 
{
	m_timeConfigDlg.cameraName = ftpData.cCameraName;
	m_timeConfigDlg.DoModal();
}

void CSetFrameDlg::OnDoconfig() 
{
	m_OperationConfig.cameraName = ftpData.cCameraName;
	if(m_OperationConfig.DoModal()!=IDOK)
		return;
	char path[MAX_PATH]={0};
	sprintf( path, "%s\\%s\\OperateConfig.dat", ftpData.localPath, ftpData.cCameraName);
	FILE* pOperate = fopen(path,"w");
	fwrite(&m_OperationConfig.mysOperate, sizeof(Tel_Operate),1,pOperate);
	fclose(pOperate);
	AfxMessageBox("存储完成");
}


bool CSetFrameDlg::ReadFileInfo()
{
	char path[MAX_PATH]={0};
	sprintf( path, "%s\\%s\\OperateConfig.dat", ftpData.localPath, ftpData.cCameraName);
	FILE* pOperate = fopen(path,"r");
	if(pOperate!=NULL) {
		fread(&m_OperationConfig.mysOperate, sizeof(Tel_Operate),1,pOperate);
		fclose(pOperate);
	}
	else{
		
	}
	memset(path, 0, MAX_PATH);
	sprintf( path, "%s\\%s\\LaneConfig.dat", ftpData.localPath, ftpData.cCameraName);
	FILE* pLane = fopen(path,"r");
	if(pLane!=NULL){
		fread(&m_LaneConfig.tempLaneConfig, sizeof(Tel_LaneConfig),1,pLane);
		fclose(pLane);
	}
	return true;
}

void CSetFrameDlg::OnDropFiles(HDROP hDropInfo) 
{	
	
	UINT count;
	char filePath[200];
	count = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
	if(count)
	{        
		for(UINT i=0; i<count; i++)
		{
			int pathLen = DragQueryFile(hDropInfo, i, filePath, sizeof(filePath));
		//	img = cvLoadImage( filePath,1);
			img = KLoadImage(filePath);
			ShowPic(img);
			Sleep(100);
		//	AfxMessageBox(filePath);
		}
	}
	DragFinish(hDropInfo);
	CDialog::OnDropFiles(hDropInfo);
}

void CSetFrameDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	ShowPic(img);
}

void CSetFrameDlg::OnDestroy() 
{
	if(img!=NULL)
		delete img;

	RemoveDir(ftpData.localPath);
	WSACleanup();
	GdiplusShutdown(m_pGdiToken);	

	CDialog::OnDestroy();

}

void CALLBACK ShowProgress(DWORD TotalSize, DWORD currentSize,char* filename, int flag, DWORD dlgName)
{
	if(0 != dlgName)
	{
		CProgress *dlg = (CProgress *)dlgName;
		if(currentSize>=TotalSize)
			dlg->Close();
		else dlg->ShowProcess(TotalSize, currentSize, filename, flag);
	}
}

bool CSetFrameDlg::readConfig()
{
	memset(&ftpData,0,sizeof(FTP_THREAD_DATA));

	HKEY hKEY;
	LPCTSTR data_Set = "Software\\Teleframe\\ocxConfig\\";
	if (!OpenReg(hKEY)){
		if (CreateReg(hKEY,data_Set)!=0)
		{
			MessageBox("无权限读取注册表 !","系统提示");
			return false;
		}
	}
	char* data=0;
	data = QueryReg("configValue",sizeof(FTP_THREAD_DATA), hKEY);
	RegCloseKey(hKEY);
	if(data==0)
		return false;
	memcpy(&ftpData, data , sizeof(FTP_THREAD_DATA));
	delete data; 

	return true;
}

void CSetFrameDlg::OnUploadIni() 
{
	//上传配置文件
	size = 0;

	if(!readConfig()) return;
	
	ftpData.hMainWnd = this->m_hWnd;
	ftpData.nflag = 1;

	m_progress->SetProcessPos(0);
	m_progress->CenterWindow(AfxGetMainWnd());
	_beginthread(UploadThread,0,&ftpData); 

}

void CSetFrameDlg::OnDownLoadIni() 
{
	// 下载配置文件
	size = 0;
	if(!readConfig()) return;

	CString cameraPath;
	cameraPath.Format("%s\\%s",ftpData.localPath , ftpData.cCameraName);
	KCreateFolder(ftpData.localPath);
	KCreateFolder(cameraPath );

	ftpData.hMainWnd = this->m_hWnd;
	ftpData.nflag = 0;

	m_progress->SetProcessPos(0);
	m_progress->CenterWindow(AfxGetMainWnd());

	if(_beginthread(DownThread,0,&ftpData) < 0)
	{
		MessageBox("create thread failure","Msg");
	}
	else
	{
	//	MessageBox("Create thread success","Msg");
	}
	
}


LRESULT CSetFrameDlg::OnTFFtpMessage(WPARAM wParam, LPARAM lParam)
{
	int nFtpResult = wParam;
	int nFileNum = lParam;
	CString str;
//	str.Format("%d",nFtpResult );MessageBox(str);
	switch(nFtpResult)
	{
	case  FTP_UPLOAD_SUCCESS :	
		m_progress->ShowWindow(SW_SHOW);
		if(nFileNum < ftpData.MaxFileNum)
		{
			m_progress->ShowProcess( ftpData.MaxFileNum, lParam, ftpData.nFileList[nFileNum],ftpData.nflag);
		}
		else
		{ 
			//上传或者下载成功 
			m_progress->Close();

			char path[MAX_PATH]={0};
			CString filename;
			filename.Format("%s\\%s\\cPicCfg.bmp", ftpData.localPath, ftpData.cCameraName);

			img = KLoadImage( filename );
			ReadFileInfo();
			Invalidate(1);
		}
		break;
	case FTP_END:
		m_progress->Close();
		this->ShowWindow(SW_SHOW);
		if(ftpData.nflag==1) MessageBox("上传完成", "系统提示");
		else MessageBox("下载完成！");
		GetDlgItem(IDC_BUTTON1)->EnableWindow(true);
		break;
	case FTP_CONN_FAILURE:
		m_progress->Close();
	//	m_progress->ShowProcess( ftpData.MaxFileNum, lParam, ftpData.nFileList[nFileNum],-1);
		if(ftpData.nflag==1) MessageBox("上传失败，请检查网络再试", "系统提示");
		else {
			if(ftpData.nflag==0) MessageBox("下载失败，请检查网络, 窗口即将关闭", "系统提示");
			CDialog::OnOK();
		}
		//PostQuitMessage(1);
		break;
	case FTP_NAME_INVALID:
		m_progress->ShowProcess( ftpData.MaxFileNum, lParam, ftpData.nFileList[nFileNum],-2);
		break;
	}

	return 0;
}

void CSetFrameDlg::OnBtSetftp() 
{
	//m_setDlg.DestroyWindow();
	//m_setDlg.Create( IDD_SET_DLG, this);	
	//SetWindowLong( m_setDlg.GetSafeHwnd(),GWL_STYLE,  DS_SETFONT | WS_POPUP | WS_VISIBLE);
	//
	if( m_setDlg.DoModal()==IDOK) 
		memcpy(&ftpData, &m_setDlg.info, sizeof(FTP_THREAD_DATA));
	else return;
	CString spath;
	spath.Format("%s\\%s", ftpData.localPath, ftpData.cCameraName);
	KCreateFolder(spath);
}


void CSetFrameDlg::OnTimer(UINT nIDEvent) 
{
	size += 3; 
	long total = 1500;
	if(size>=total)
		m_progress->Close();
	else{
		if(nIDEvent==0) m_progress->ShowProcess( total, size, 	"file.txt", 0);
		else m_progress->ShowProcess( total, size, 	"file.txt", 1);
	}

	CDialog::OnTimer(nIDEvent);
}

HBRUSH CSetFrameDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	switch(nCtlColor)
	{
	case CTLCOLOR_DLG:
		return (HBRUSH) m_brush.GetSafeHandle();
		break;

	case CTLCOLOR_STATIC:
		pDC->SetBkMode(TRANSPARENT);
		pDC->SelectObject(&m_brush);
		return (HBRUSH) m_brush.GetSafeHandle(); // m_brush
		break;
	default:
		return hbr;
	}
	return hbr;
}

bool CSetFrameDlg::SetFtpInfo(char *Ip, long port, char *userName, char *passWord, char *serverPath, char *localPath, char *cameraName, int fileSum, CString fileLists)
{
	
	memset( &ftpData, 0, sizeof(ftpData));
	memcpy(ftpData.cFtpServerIp, Ip, 32 );
	memcpy(ftpData.cFtpUser, userName, 64 );
	memcpy(ftpData.cFtpPass, passWord, 64 );
//	memcpy(ftpData.serverPath, serverPath, 256 );
	CString m_localPath(localPath);
	if(m_localPath.Find('__')<0 ) 
	{
		m_localPath += "__" ;
	}
	else
	{
		m_localPath = m_localPath.Left(m_localPath.Find('__')+2);
	}
	m_localPath += cameraName;
//	MessageBox(m_localPath);
	m_localPath.Replace("/","\\");
	memcpy( ftpData.localPath, m_localPath, m_localPath.GetLength() );
//	memcpy(ftpData.localPath, localPath, 256);
	memcpy(ftpData.cCameraName, cameraName, 64 );
	ftpData.nFtpPort = (int)port;
	ftpData.MaxFileNum = (int)fileSum;
	CStringList fileList;
	CString file;
	Split(fileLists, "<R>", &fileList);
	for(int i=0; i<fileSum; i++)
	{
		file = fileList.GetHead();
		if(file.IsEmpty())	
		{ }
		else
		{
			memcpy(ftpData.nFileList[i],file.GetBuffer(file.GetLength()) , 32 );
		}
		fileList.RemoveHead();
	}
	
	return m_setDlg.SetFtpInfo(&ftpData);
}

CString CSetFrameDlg::GetFtpInfo(void)
{
	return m_setDlg.GetFtpInfo();
}
