// TimeConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "TimeConfigDlg.h"

#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTimeConfigDlg dialog


CTimeConfigDlg::CTimeConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTimeConfigDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTimeConfigDlg)
	m_week = 0;
	m_listIndex = 0;
	//}}AFX_DATA_INIT
}


void CTimeConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTimeConfigDlg)
	DDX_Control(pDX, IDC_SAVE_AUTO, m_saveAuto);
	DDX_Control(pDX, IDC_COM_EVENT, m_event);
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_COMBO1, m_weeks);
	DDX_Text(pDX, IDC_EVENT_INDEX, m_listIndex);
	DDV_MinMaxInt(pDX, m_listIndex, 0, 999);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_CHECK6, editAble);
}


BEGIN_MESSAGE_MAP(CTimeConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CTimeConfigDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_CBN_SETFOCUS(IDC_COMBO1, OnSetfocusCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON0, OnButton0)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_CBN_SELCHANGE(IDC_COM_EVENT, OnSelchangeComEvent)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CTimeConfigDlg::OnBnClickedOk)
	ON_NOTIFY(NM_THEMECHANGED, IDC_CHECK6, &CTimeConfigDlg::OnNMThemeChangedCheck6)
//	ON_BN_CLICKED(IDC_CHECK6, &CTimeConfigDlg::OnBnClickedCheck6)
ON_BN_CLICKED(IDC_CHECK6, &CTimeConfigDlg::OnBnClickedCheck6)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTimeConfigDlg message handlers

BOOL CTimeConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int len = LEN_EVENT;
	for(int i=0; i<len; i++)
		m_event.AddString(eventVal[i]);
	m_event.SetCurSel(0);

	memset(&m_times, 0, sizeof(int)*7*20);

	memset(&info,0,sizeof(FTP_THREAD_DATA));

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
	char* data=0;
	data = QueryReg("configValue",sizeof(FTP_THREAD_DATA), hKEY);
	RegCloseKey(hKEY);
	if(data==0)
		return false;
	memcpy(&info, data , sizeof(FTP_THREAD_DATA));
	delete data; 

	/*char *path = GetWindowPath();
	strcat(path, "\\camera_setdlg.dat");
	FILE *fp = fopen(path, "r");
	if(fp==NULL) return false;
	fread( &info, sizeof(FTP_THREAD_DATA), 1, fp);
	fclose(fp);*/

	ReadTimeConfig();
	m_weeks.SetCurSel(0);
	UpdateTimes();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTimeConfigDlg::OnOK() 
{
	
	SaveTemp();
	if(SaveTimeConfig())
		AfxMessageBox("保存成功!");
	else {
		AfxMessageBox("保存失败!");
		return ;
	} 
	CDialog::OnOK();
}

bool CTimeConfigDlg::SaveTimeConfig()
{
	char path[MAX_PATH]={0};
	char text[100]={0};
	int index = m_listIndex; // m_event.GetCurSel();
	strcat(text, "Event_");
	strcat(text, eventID[index]);
	sprintf(path, "%s\\%s\\", info.localPath , cameraName);
	strcat(path, text);
	FILE *out = fopen( path,"w");
	if(out==NULL) {
		return false;
	}
	int i=0, j;
	for(i=0; i<7; i++){
		fprintf(out, "%d ",i);
		for(j=0; j<20; j++)
			fprintf(out, "%d ",m_times[i][j]);
		fprintf(out, "\n");
	}
	fclose(out);
	
	return true;
}

bool CTimeConfigDlg::ReadTimeConfig()
{
	char path[MAX_PATH]={0};
	char text[100]={0};
	int index = m_listIndex; //m_event.GetCurSel();
	strcat(text, "Event_");
	strcat(text, eventID[index]);
	sprintf(path, "%s\\%s\\", info.localPath , cameraName);
	strcat(path, text);
	FILE *in = fopen(path,"r");
	if(in==NULL) {
		return false;
	}
	int i=0, j;
	int t;
	for(i=0; i<7; i++){
		fscanf(in, "%d",&t);
		for(j=0; j<20; j++)
			fscanf(in, "%d", &m_times[i][j]);
		fscanf(in, "\n");
	}
	fclose(in);
	return true;
}
void CTimeConfigDlg::UpdateTimes()// 根据 m_times 动态显示设置 
{
//	UpdateData(true);
	int idd11 = IDC_DATETIMEPICKER1;
	int idc1  = IDC_CHECK1;
	int k,i;
	for(k=0; k<5;k++)
	{
		
		if(m_times[m_week][k*4+2]>0 || m_times[m_week][k*4+3]>0)
		{
			((CButton*)GetDlgItem(idc1))->SetCheck(1);
			for(i=0; i<4; i+=2 ){
				CDateTimeCtrl *t = (CDateTimeCtrl*)GetDlgItem(idd11);
				int hour = m_times[m_week][k*4+i];
				int minute = m_times[m_week][k*4+i+1] ;
				CTime time(2012,1,1, hour, minute,0);
				t->SetTime(&time);
				idd11++;
			}
		}
		else
		{
			((CButton*)GetDlgItem(idc1))->SetCheck(0);
			for(i=0; i<4; i+=2 ){
				CDateTimeCtrl *t = (CDateTimeCtrl*)GetDlgItem(idd11);
				m_times[m_week][k*4+i] = 0; // 星期: m_week  时间段：k  时间位置：k*4 ---- (k+1)*4-1
				m_times[m_week][k*4+i+1] = 0;
				CTime time(2012,1,1, 0,0,0);
				t->SetTime(&time);
				UpdateData(false);
				idd11++;
			}
		}
		idc1++;
	}
	
}


void CTimeConfigDlg::OnSelchangeCombo1()
{
//	AfxMessageBox("changed");
	SaveTemp();
	m_week = m_weeks.GetCurSel();
	UpdateTimes();
}

void CTimeConfigDlg::OnSetfocusCombo1() 
{
	m_week = m_weeks.GetCurSel();
}

void CTimeConfigDlg::SaveTemp()//临时存储 每天的时间段
{
	int idd11 = IDC_DATETIMEPICKER1;
	int idc1  = IDC_CHECK1;

	int i,k;
	UpdateData(true);
	for(k=0; k<5;k++)
	{
		int checked = (((CButton*)GetDlgItem(idc1))->GetCheck());
		if(checked>0)
		{
			for(i=0; i<4; i+=2 ){
				CDateTimeCtrl *t = (CDateTimeCtrl*)GetDlgItem(idd11);
				CTime time;
				t->GetTime(time);
				int hour = time.GetHour();
				int minute = time.GetMinute();
				m_times[m_week][k*4+i] = hour; // 星期: m_week  时间段：k  时间位置：k*4 ---- (k+1)*4-1
				m_times[m_week][k*4+i+1] = minute;
				idd11++;
			}
			
		}
		else
		{
			for(i=0; i<4; i+=2 ){
				m_times[m_week][k*4+i] = 0; // 星期: m_week  时间段：k  时间位置：k*4 ---- (k+1)*4-1
				m_times[m_week][k*4+i+1] = 0;
				idd11++;
			}
		}
		idc1++;
	}
	UpdateData(false);
}

void CTimeConfigDlg::OnCancel() 
{
//	char path[MAX_PATH]={0};
//	::GetCurrentDirectory(MAX_PATH, path);
//	GetWindowsDirectory(path, MAX_PATH);
	char *path = GetWindowPath();
	CString str;str.Format("%s",path);
//	MessageBox(str);

	CDialog::OnCancel();
}


void CTimeConfigDlg::OnButton0() 
{
	m_weeks.SetCurSel(0);
	OnSelchangeCombo1();
}

void CTimeConfigDlg::OnButton1() 
{
	m_weeks.SetCurSel(1);
	OnSelchangeCombo1();
}

void CTimeConfigDlg::OnButton2() 
{
	m_weeks.SetCurSel(2);
	OnSelchangeCombo1();
}

void CTimeConfigDlg::OnButton3() 
{
	m_weeks.SetCurSel(3);
	OnSelchangeCombo1();
}

void CTimeConfigDlg::OnButton4() 
{
	m_weeks.SetCurSel(4);
	OnSelchangeCombo1();
}

void CTimeConfigDlg::OnButton5() 
{
	m_weeks.SetCurSel(5);	
	OnSelchangeCombo1();
}

void CTimeConfigDlg::OnButton6() 
{
	m_weeks.SetCurSel(6);
	OnSelchangeCombo1();
}

void CTimeConfigDlg::OnSelchangeComEvent() 
{
	SaveTemp();
	if(editAble.GetCheck())
	{
		if(!m_saveAuto.GetCheck())
		{
			int ret = MessageBox("是否保存该事件的时间段设置","保存提示", MB_YESNOCANCEL | MB_ICONQUESTION);
			if(ret==IDYES)
			{	
				if(SaveTimeConfig())
					AfxMessageBox("保存成功!");
				else 
					AfxMessageBox("保存失败!");
			}
			else if(ret==IDCANCEL) m_event.SetCurSel(m_listIndex);
			else {	}
		}
		else { SaveTimeConfig(); }
	}

  	UpdateData(true);
	m_listIndex = m_event.GetCurSel();
	UpdateData(false);

	memset(&m_times, 0, sizeof(int)*7*20);
	UpdateData();
	ReadTimeConfig();	
	UpdateTimes();	
}

void CTimeConfigDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}

void CTimeConfigDlg::OnNMThemeChangedCheck6(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;
}



void CTimeConfigDlg::OnBnClickedCheck6()
{
	UpdateData(true);
	bool edit = editAble.GetCheck();
	if(edit){
		editAble.SetWindowTextA("查看");
		GetDlgItem(IDC_CHECK1)->EnableWindow(true);
		GetDlgItem(IDC_CHECK2)->EnableWindow(true);
		GetDlgItem(IDC_CHECK3)->EnableWindow(true);
		GetDlgItem(IDC_CHECK4)->EnableWindow(true);
		GetDlgItem(IDC_CHECK5)->EnableWindow(true);
	}
	else{
		if( MessageBox("是否保存修改","", MB_YESNO)== IDOK)
		{
			SaveTemp();
			SaveTimeConfig();
		}
		editAble.SetWindowTextA("编辑");
		GetDlgItem(IDC_CHECK1)->EnableWindow(false);
		GetDlgItem(IDC_CHECK2)->EnableWindow(false);
		GetDlgItem(IDC_CHECK3)->EnableWindow(false);
		GetDlgItem(IDC_CHECK4)->EnableWindow(false);
		GetDlgItem(IDC_CHECK5)->EnableWindow(false);
	}
	UpdateData(false);
}
