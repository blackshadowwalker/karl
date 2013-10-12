// SetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "SetDlg.h"
#include "Winsock2.h"

#pragma comment(lib,"Ws2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDlg dialog


CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDlg::IDD, pParent)
	, m_cameraName(_T("PZC1LW04300068"))
{
	//{{AFX_DATA_INIT(CSetDlg)
	m_localPath = _T("d:\\temp\\config");
	m_port = 21;
	m_username = _T("admin");
	m_password = _T("admin");
	m_ftpPath = _T("");
	//}}AFX_DATA_INIT
}


void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDlg)
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_LOCAL_PATH, m_localPath);
	DDX_Text(pDX, IDC_PORT, m_port);
	DDX_Text(pDX, IDC_USERNAME, m_username);
	DDX_Text(pDX, IDC_PASSWORD, m_password);
	DDX_Text(pDX, IDC_FTP_PATH, m_ftpPath);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_CAMREA_NAME, m_cameraName);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
	//{{AFX_MSG_MAP(CSetDlg)
	//}}AFX_MSG_MAP
//	ON_BN_CLICKED(IDOK, &CSetDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSetDlg::OnBnClickedButton1)
	ON_LBN_DBLCLK(IDC_LIST1, &CSetDlg::OnLbnDblclkList1)
	ON_LBN_KILLFOCUS(IDC_LIST1, &CSetDlg::OnLbnKillfocusList1)
	ON_LBN_SELCHANGE(IDC_LIST1, &CSetDlg::OnLbnSelchangeList1)
//	ON_BN_CLICKED(IDOK, &CSetDlg::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDlg message handlers

void CSetDlg::OnOK() 
{
	UpdateData(true);

	if(m_ip.IsBlank()) {
		MessageBox("请输入 FTP IP");
		return ;
	}
	if(m_port<1)
	{
		MessageBox("请输入正确的端口");
		return ;
	}
	if(m_localPath.IsEmpty())
	{
		MessageBox("请输入本地缓存路径");
		return ;
	}
	if(m_username.IsEmpty())
	{
		MessageBox("请输入FTP用户名");
		return ;
	}
	if(m_password.IsEmpty())
	{
		MessageBox("请输入FTP密码");
		return ;
	}
	//if(m_ftpPath.IsEmpty())
	//{
	//	MessageBox("请输入FTP下载路径");
	//	return ;
	//}
	if(m_cameraName.IsEmpty())
	{
		MessageBox("请输入摄像头名称");
		return ;
	}
	if(!SaveSetIni()){
		MessageBox("保存失败!", "提示",  MB_OK | MB_ICONERROR );
	}
	CDialog::OnOK();
}



bool CSetDlg::ReadSetIni()
{
	//读取配置文件
	DWORD ipD = ntohl(inet_addr(info.cFtpServerIp));// 将字符串ip转化为32位整数
	m_ip.SetAddress(ipD);

	m_port = info.nFtpPort;
	m_username.Format("%s", info.cFtpUser);
	m_password.Format("%s", info.cFtpPass);
	m_ftpPath.Format("%s", info.serverPath);
	if(strlen(info.localPath)>0) 
		m_localPath.Format("%s", info.localPath);
	m_cameraName.Format("%s", info.cCameraName);

	m_list.ResetContent();
	if(info.MaxFileNum<1)
	{
		m_list.AddString("cPicCfg.bmp");
		m_list.AddString("Event_CHD");
		m_list.AddString("Event_CLL");
		m_list.AddString("Event_KK");
		m_list.AddString("Event_NX");
		m_list.AddString("Event_PDCD");
		m_list.AddString("Event_SFZ");
		m_list.AddString("Event_SFZ");
		m_list.AddString("Event_TLSJC");
		m_list.AddString("Event_WCP");
		m_list.AddString("Event_WGBD");
		m_list.AddString("Event_WZTC");
		m_list.AddString("Event_YHX");
		m_list.AddString("LaneConfig.dat");
		m_list.AddString("OperateConfig.dat");
	}
	else
	{
		for(int i=0; i<info.MaxFileNum; i++){
			m_list.AddString(info.nFileList[i]);
		}
	}

	UpdateData(false);

	return true;
}

bool CSetDlg::SaveSetIni()
{
	UpdateData(true);

	CString str;
	BYTE bt[4];
	m_ip.GetAddress(bt[0],bt[1],bt[2],bt[3]);
	str.Format("%d.%d.%d.%d", bt[0],bt[1],bt[2],bt[3] );

	memset(&info, 0, sizeof(info));
	memcpy( info.cFtpServerIp ,str, str.GetLength());
	info.nFtpPort = m_port;
	memcpy( info.cFtpUser , m_username, m_username.GetLength() );
	memcpy( info.cFtpPass , m_password, m_password.GetLength() );
//	memcpy( info.serverPath, m_ftpPath, m_ftpPath.GetLength() );
	if(m_localPath.Find('__')<0 ) 
	{
		m_localPath += "__" ;
	}
	else
	{
		m_localPath = m_localPath.Left(m_localPath.Find('__')+2);
	}
	m_localPath += m_cameraName;
//	MessageBox(m_localPath);
	m_localPath.Replace("/","\\");
	memcpy( info.localPath, m_localPath, m_localPath.GetLength() );

	strncpy(info.cCameraName,m_cameraName, 64);

	CString fileName;
	int count = m_list.GetCount();
	for(int i=0; i<count; i++){
		m_list.GetText(i, fileName);
		fileName.Replace("/","\\");
		strncpy(info.nFileList[i], fileName, FILENAME_LEN);
	}
	info.MaxFileNum = count;

	HKEY hKEY;
	LPCTSTR data_Set = "Software\\Teleframe\\ocxConfig\\";
//	SetRegPath("Software\\Teleframe\\ocxConfig\\");
	if (!OpenReg(hKEY)){
		if (CreateReg(hKEY,data_Set)!=0)
		{
			MessageBox("无权限读取注册表 !","系统提示");
			return false;
		}

	}
	if (!WriteReg(hKEY)){
		return false;
	}

	char* data = new char[sizeof(FTP_THREAD_DATA)];
	memset(data, 0, sizeof(FTP_THREAD_DATA));
	memcpy(data, &info, sizeof(FTP_THREAD_DATA));
	if(!SetReg("configValue",data, sizeof(FTP_THREAD_DATA), hKEY))
	{
		MessageBox("保存失败","系统提示");
		return false; 
	}
	RegCloseKey(hKEY);

	return true;
}

BOOL CSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list.AddString("cPicCfg.bmp");
	m_list.AddString("Event_CHD");
	m_list.AddString("Event_CLL");
	m_list.AddString("Event_KK");
	m_list.AddString("Event_NX");
	m_list.AddString("Event_PDCD");
	m_list.AddString("Event_SFZ");
	m_list.AddString("Event_SFZ");
	m_list.AddString("Event_TLSJC");
	m_list.AddString("Event_WCP");
	m_list.AddString("Event_WGBD");
	m_list.AddString("Event_WZTC");
	m_list.AddString("Event_YHX");
	m_list.AddString("LaneConfig.dat");
	m_list.AddString("OperateConfig.dat");

	if(ReadConfigFromReg()) 
	{
		ReadSetIni();
	}
	else 
	{
		char *path = GetWindowPath();
		m_localPath.Format("%s\\config", path);
	}

	return TRUE; 
}

BOOL CSetDlg::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CDialog::PreCreateWindow(cs);
}

//void CSetDlg::OnBnClickedOk()
//{
//	SaveSetIni();
//	// TODO: 在此添加控件通知处理程序代码
//	OnOK();
//}
void ListAllFiles(char *Path, CListBox *list)
{
    char file[MAX_PATH];
    lstrcpy(file,Path);
    lstrcat(file,"\\*.*"); 
    WIN32_FIND_DATA wfd; 
    HANDLE Find = FindFirstFile(file,&wfd); 
    if (Find == INVALID_HANDLE_VALUE)  
        return;
     
    while (FindNextFile(Find, &wfd))
    {
		char szFindPath[MAX_PATH]={0};
        if (wfd.cFileName[0] == '.') 
        {
            continue;
        } 
		lstrcpy(szFindPath,Path); 
		lstrcat(szFindPath,"\\"); 
		lstrcat(szFindPath,wfd.cFileName); 
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
        {
            //ListAllFiles(szFindPath, list);  
		}
		else
			list->AddString( wfd.cFileName );
        //DeleteFile(FilePath);
    }
    FindClose(Find);
     
}
void CSetDlg::OnBnClickedButton1()
{
	CString str;
	GetDlgItem(IDC_EDIT_ADD)->GetWindowText(str);
	if(str.IsEmpty()) return ;
	if( m_list.FindString(0, str)>=0) ;
	else m_list.InsertString(0,str);
	m_list.SetCurSel(0);
	//	GetDlgItem(IDC_EDIT_ADD)->SetWindowText("");
	CEdit *p = ((CEdit*)GetDlgItem(IDC_EDIT_ADD));
	p->SetSel(str.GetLength());
	return ;
}

void CSetDlg::OnLbnDblclkList1()
{
	int index = m_list.GetCurSel();
	m_list.DeleteString(index);
}

BOOL CSetDlg::PreTranslateMessage(MSG* pMsg)
{
	if (GetDlgItem(IDC_EDIT_ADD) == GetFocus() && WM_KEYDOWN   ==   pMsg-> message && 13   ==   pMsg-> wParam)
	{
		CString str;
		GetDlgItem(IDC_EDIT_ADD)->GetWindowText(str);
		if(str.IsEmpty()) return false;
		if( m_list.FindString(0, str)>=0) ;
		else m_list.InsertString(0,str);
		m_list.SetCurSel(0);
	//	GetDlgItem(IDC_EDIT_ADD)->SetWindowText("");
		CEdit *p = ((CEdit*)GetDlgItem(IDC_EDIT_ADD));
		p->SetSel(str.GetLength());
		return FALSE;

	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSetDlg::OnLbnKillfocusList1()
{
//	OnLbnSelchangeList1();
}

void CSetDlg::OnLbnSelchangeList1()
{
	CString str;
	m_list.GetText(m_list.GetCurSel(), str);
	GetDlgItem(IDC_EDIT_ADD)->SetWindowText(str);
}


bool  CSetDlg::SetFtpInfo(SetInfoList *ftpInfo)
{
	memset(&info, 0, sizeof(SetInfoList));
	memcpy(&info, ftpInfo, sizeof(SetInfoList));

	HKEY hKEY;
	LPCTSTR data_Set = "Software\\Teleframe\\ocxConfig\\";
	if (!OpenReg(hKEY)){
		if (CreateReg(hKEY,data_Set)!=0)
		{
			MessageBox("无权限读取注册表 !","系统提示", MB_OK);
			return false;
		}
	}
	if (!WriteReg(hKEY)){
		return false;
	}
	char* data = new char[sizeof(SetInfoList)];
	memset(data, 0, sizeof(SetInfoList));
	memcpy(data, &info, sizeof(SetInfoList));
	if(!SetReg("configValue",data, sizeof(SetInfoList), hKEY))
	{
		MessageBox("保存失败","系统提示", MB_OK);
		return false; 
	}
	RegCloseKey(hKEY);

	return true;
}
CString CSetDlg::GetFtpInfo(void)
{
	CString str(""), temp;
	if(ReadConfigFromReg())
	{
		str += info.cFtpServerIp;
		str += "<F>";
		temp.Format("%d",info.nFtpPort);
		str += temp;
		str += "<F>";
		str += info.cFtpUser;
		str += "<F>";
		str += info.cFtpPass;
		str += "<F>";
		str += info.serverPath;
		str += "<F>";
		str += info.localPath;
		str += "<F>";
		str += info.cCameraName;
		str += "<F>";
		temp.Format("%d",info.MaxFileNum);
		str += temp;
		str += "<F>";
		for(int i=0; i<info.MaxFileNum; i++)
		{
			str += CString(info.nFileList[i]);
			str += "<R>";
		}
		if(info.MaxFileNum>0) 
			str += "<F>";
	}
	else
	{
		str = "";
	}
	return str;
}

bool CSetDlg::ReadConfigFromReg(void)
{
	memset(&info, 0, sizeof(SetInfoList));

	HKEY hKEY;
	LPCTSTR data_Set = "Software\\Teleframe\\ocxConfig\\";
//	SetRegPath("Software\\Teleframe\\ocxConfig\\");
	if (!OpenReg(hKEY)){
		if (CreateReg(hKEY,data_Set)!=0)
		{
			MessageBox("无权限读取注册表 !","系统提示");
			return false;
		}
		return false;//由于键值不存在，所以需要返回；由于数据为空，故返回false
	}
	
	char* data=0;
	data = QueryReg("configValue",sizeof(FTP_THREAD_DATA), hKEY);
	RegCloseKey(hKEY);
	if(data==NULL) 
		return false;
	else {
		memcpy(&info, data , sizeof(FTP_THREAD_DATA));
		delete data; 
	}
	return true;
}

