// OperationConfig.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "OperationConfig.h"

#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

bool OperationConfig::inited=false;
/////////////////////////////////////////////////////////////////////////////
// OperationConfig dialog
IMPLEMENT_DYNAMIC(OperationConfig, CDialog)

OperationConfig::OperationConfig(CWnd* pParent /*=NULL*/)
	: CDialog(OperationConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(OperationConfig)
	
	//}}AFX_DATA_INIT
}


void OperationConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OperationConfig)
	DDX_Control(pDX, IDC_REGION_NAME, m_regionname);
	DDX_Control(pDX, IDC_REGION_ID, m_regionid);
	DDX_Control(pDX, IDC_OPERATE, m_operate);
	DDX_Control(pDX, IDC_MODE, m_mode);
	DDX_Control(pDX, IDC_LIST_OPERATE, m_listoperate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(OperationConfig, CDialog)
	//{{AFX_MSG_MAP(OperationConfig)
	ON_BN_CLICKED(IDC_ADD, OnBnClickedAdd)
	ON_CBN_SELCHANGE(IDC_REGION_NAME, OnCbnSelchangeRegionName)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_DEL, OnBnClickedDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// OperationConfig message handlers




bool OperationConfig::LoadInfo()
{
	if(mysOperate.iNum<1) return false;//配置文件为空
	int i,j;
	CString str;
	for(i=0, j=1; i<mysOperate.iNum; i++, j++){
		str.Format("%s",config[mysOperate.operate[j].iRegionType] );
		m_listoperate.InsertItem(i, str, 0);
		str.Format("%d", mysOperate.operate[j].iID);
		m_listoperate.SetItemText(i, 1, str);
		str.Format("%s", coperate[mysOperate.operate[j].iOperateType]);
		m_listoperate.SetItemText(i, 2, str);
		str.Format("%s", cmode[mysOperate.operate[j].iDetMode]);
		m_listoperate.SetItemText(i, 3, str);
	}
	return true;
}
bool OperationConfig::InitDlg()
{	
	int i;
/*	char *path = GetWindowPath();
	strcat(path, "\\camera_setdlg.dat");
	FILE *fp = fopen(path, "r");
	if(fp==NULL) return false;
	fread( &info, sizeof(FTP_THREAD_DATA), 1, fp);
	fclose(fp);
*/
	HKEY hKEY;
	LPCTSTR data_Set = "Software\\Teleframe\\ocxConfig\\";
//	SetRegPath("Software\\Teleframe\\ocxConfig\\");
	if (!OpenReg(hKEY)){
		if (CreateReg(hKEY,data_Set)!=0)
		{
			MessageBox("无权限读取注册表 !","系统提示");
			return false;
		}
		return true;
	}
	
	char* data=0;
	data = QueryReg("configValue",sizeof(FTP_THREAD_DATA), hKEY);
	RegCloseKey(hKEY);
	if(data==0)
		return false;
	memset(&info, 0, sizeof(FTP_THREAD_DATA));
	memcpy(&info, data , sizeof(FTP_THREAD_DATA));
	delete data; 

	char filePath[MAX_PATH]={0};
	sprintf(filePath, "%s\\%s\\LaneConfig.dat", info.localPath, info.cCameraName);
	FILE* pLane = fopen(filePath,"r");
	if(pLane!=NULL){
		fread(&mysLaneConfig, sizeof(Tel_LaneConfig),1,pLane);
		fclose(pLane);
	}

	if (mysLaneConfig.lane.iNum > 0)
	{
//		m_regionname.InsertString(iNumber,config[0]);
//		iNumber ++;
	}
	int iNumber = 0;
	if (mysLaneConfig.detRegion.iNum > 0)
	{
		m_regionname.InsertString(iNumber,config[0]);
		regionList[iNumber] = mysLaneConfig.detRegion.iNum ;
		iNumber ++;
	}
	if (mysLaneConfig.parkingRegion.iNum > 0)
	{
		m_regionname.InsertString(iNumber,config[1]);
		regionList[iNumber] = mysLaneConfig.parkingRegion.iNum ;
		iNumber ++;
	}
	
	if (mysLaneConfig.yellowLineRegion.iNum > 0)
	{
		m_regionname.InsertString(iNumber,config[2]);
		regionList[iNumber] = mysLaneConfig.yellowLineRegion.iNum ;
		iNumber ++;
	}
	m_regionname.SetCurSel(0);

	CString str;
	for(i=0; i<regionList[0]; i++){
		str.Format("%d", i);
		m_regionid.AddString(str);
	}
	m_regionid.SetCurSel(0);

	for ( i = 0; i < 9; i ++)
	{
		m_operate.InsertString(i,coperate[i]);
	}
	m_operate.SetCurSel(0);

	for ( i = 0; i < 3; i ++)
	{
		m_mode.InsertString(i,cmode[i]);
	}
	m_mode.SetCurSel(0);

	// 为列表框控件添加表头 
	LV_COLUMN col;
	col.mask =	LVCF_FMT|LVCF_SUBITEM|LVCF_TEXT|LVCF_WIDTH;
	col.fmt = LVCFMT_LEFT;
	m_listoperate.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES); 

	//col.pszText = _T("索引");// 添加列表控件的表头
	//col.iSubItem = 0;
	//col.cx = 60;
	//m_listoperate.InsertColumn(0, &col);

	col.pszText = _T("区域名");
	col.iSubItem = 0;
	col.cx = 150;
	m_listoperate.InsertColumn(1, &col);	

	col.pszText = _T("区域ID");
	col.iSubItem = 1;
	col.cx = 110;
	m_listoperate.InsertColumn(2, &col);	

	col.pszText = _T("操作类型");
	col.iSubItem = 2;
	col.cx = 160;
	m_listoperate.InsertColumn(3, &col);	
	
	col.pszText = _T("检测模式");
	col.iSubItem = 3;
	col.cx = 160;
	m_listoperate.InsertColumn(3, &col);	
	return true;
}

BOOL OperationConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

//	if(!inited) 
	InitDlg();
//	inited = true;
	LoadInfo();
//	AfxMessageBox("Init");

	return TRUE;  
}

int OperationConfig::JudgeSame()
{
	CString strTempRegionName,strTempRegionID,strTempDecType;
	CString strRegionName,strRegionID,strDecType;
	
	BOOL bSame = 1;
	int iNameIndex1, iNameIndex2, iNameIndex3;

	iNameIndex1 =((CComboBox*)GetDlgItem(IDC_REGION_NAME))->GetCurSel();	
	iNameIndex2 =((CComboBox*)GetDlgItem(IDC_REGION_ID))->GetCurSel();
	iNameIndex3 =((CComboBox*)GetDlgItem(IDC_OPERATE))->GetCurSel();

	if(iNameIndex1<0 || iNameIndex2<0 || iNameIndex3<0 ) return -1;

/*	iNameIndex1 = iNameIndex1<0? 0:iNameIndex1;
	iNameIndex2 = iNameIndex2<0? 0:iNameIndex2;
	iNameIndex3 = iNameIndex3<0? 0:iNameIndex3;
*/
	((CComboBox*)GetDlgItem(IDC_REGION_NAME))->GetLBText(iNameIndex1,strTempRegionName);
	((CComboBox*)GetDlgItem(IDC_REGION_ID))->GetLBText(iNameIndex2,strTempRegionID);
	((CComboBox*)GetDlgItem(IDC_OPERATE))->GetLBText(iNameIndex3,strTempDecType);



	for (int i = 0; i < m_listoperate.GetItemCount(); i ++)
	{
		strRegionName = m_listoperate.GetItemText(i,0);
		strRegionID = m_listoperate.GetItemText(i,1);
		strDecType = m_listoperate.GetItemText(i,2);

		if (!strTempRegionName.CompareNoCase(strRegionName) && 
			!strTempRegionID.CompareNoCase(strRegionID) &&
			!strTempDecType.CompareNoCase(strDecType))
		{
			bSame = 0;
			break;
		}
		else bSame = 1;

	}

	return bSame;
}
void OperationConfig::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	LV_ITEM item;
	item.mask = LVIF_TEXT;
	int iPos;
	int iTempListNumber = m_listoperate.GetItemCount();
	char *p;
	CString str;
	int iNameIndex;
	int check = JudgeSame();
	if (check==-1){
		MessageBox("请选择数据");
		return ;
	}
	else if(check==0){
		MessageBox("配置重复！");
		return;
	}

	item.iItem = iTempListNumber;
	item.iSubItem = 0;
	iNameIndex =((CComboBox*)GetDlgItem(IDC_REGION_NAME))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_REGION_NAME))->GetLBText(iNameIndex,str);
	p = (LPSTR)(LPCTSTR) str;
	item.pszText =  p;
	iPos = m_listoperate.InsertItem(&item);

	item.iItem = iPos;
	item.iSubItem = 1;
	iNameIndex =((CComboBox*)GetDlgItem(IDC_REGION_ID))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_REGION_ID))->GetLBText(iNameIndex,str);
	p = (LPSTR)(LPCTSTR) str;
	item.pszText = p;
	m_listoperate.SetItem(&item);

	item.iItem = iPos;
	item.iSubItem = 2;
	iNameIndex =((CComboBox*)GetDlgItem(IDC_OPERATE))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_OPERATE))->GetLBText(iNameIndex,str);
	p = (LPSTR)(LPCTSTR) str;
	item.pszText = p;
	m_listoperate.SetItem(&item);

	item.iItem = iPos;
	item.iSubItem = 3;
	iNameIndex =((CComboBox*)GetDlgItem(IDC_MODE))->GetCurSel();
	((CComboBox*)GetDlgItem(IDC_MODE))->GetLBText(iNameIndex,str);
	p = (LPSTR)(LPCTSTR) str;
	item.pszText = p;
	m_listoperate.SetItem(&item);

}


void OperationConfig::OnCbnSelchangeRegionName()
{
	UpdateData(true);
	int index = m_regionname.GetCurSel();
	CString str;
	m_regionid.ResetContent();
	int i;
	for(i=0; i<regionList[index]; i++){
		str.Format("%d", i);
		m_regionid.AddString(str);
	}
	m_regionid.SetCurSel(0);
	// 
/*	int iNameIndex =((CComboBox*)GetDlgItem(IDC_REGION_NAME))->GetCurSel();
	CString str;

	((CComboBox*)GetDlgItem(IDC_REGION_NAME))->GetLBText(iNameIndex,str);
	char* tempchar = (LPSTR)(LPCTSTR) str;
	int i;
	char s[25];

	m_regionid.ResetContent();

	if (strcmp(tempchar,"车道区域") == 0)
	{
		for (i = 0; i < mysLaneConfig.lane.iNum; i ++)
		{
			sprintf(s, "%d", mysLaneConfig.lane.region[i].iID); 
			m_regionid.InsertString(i,s);
		}

	}
	if (strcmp(tempchar,"违章停车区域") == 0)
	{
		for (i = 0; i < mysLaneConfig.parkingRegion.iNum; i ++)
		{
			sprintf(s, "%d", mysLaneConfig.parkingRegion.region[i].iID); 
			m_regionid.InsertString(i,s);
		}
	}
	if (strcmp(tempchar,"检测区域") == 0)
	{
		for (i = 0; i < mysLaneConfig.detRegion.iNum; i ++)
		{
			sprintf(s, "%d", mysLaneConfig.detRegion.region[i].iID); 
			m_regionid.InsertString(i,s);
		}
	}
	if (strcmp(tempchar,"黄线区域") == 0)
	{
		for (i = 0; i < mysLaneConfig.yellowLineRegion.iNum; i ++)
		{
			sprintf(s, "%d", mysLaneConfig.yellowLineRegion.region[i].iID); 
			m_regionid.InsertString(i,s);
		}
	}

*/
	return;
}

void OperationConfig::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	int i,j;
	CString strRegionName,strRegionID,strDecType,strMode,str;

	mysOperate.iNum = 0;
	for ( i = 0; i < m_listoperate.GetItemCount(); i ++)
	{
		mysOperate.iNum ++;
		strRegionName = m_listoperate.GetItemText(i,0);
		strRegionID = m_listoperate.GetItemText(i,1);
		strDecType = m_listoperate.GetItemText(i,2);
		strMode = m_listoperate.GetItemText(i,3);

		mysOperate.operate[mysOperate.iNum].iID = atoi(strRegionID);

		for ( j = 0; j < 4; j ++)
		{
			str.Format("%s",config[j]);
			if (!strRegionName.CompareNoCase(str))
			{
				mysOperate.operate[mysOperate.iNum].iRegionType = j ;
				break;
			}
		}


		for ( j = 0; j < 9; j ++)
		{
			str.Format("%s",coperate[j]);
			if (!strDecType.CompareNoCase(str))
			{
				mysOperate.operate[mysOperate.iNum].iOperateType = j;
				break;
			}
		}

		for ( j = 0; j < 3; j ++)
		{
			str.Format("%s",cmode[j]);
			if (!strMode.CompareNoCase(str))
			{
				mysOperate.operate[mysOperate.iNum].iDetMode = j;
				break;
			}
		}
		
	}
	str.Format("%d",mysOperate.iNum);
	CString strShow;
	strShow = "共存储" + str + "个操作！";    

//	MessageBox(strShow);

	CDialog::OnOK();

	return;
}

void OperationConfig::OnBnClickedDel()
{
	// TODO: 在此添加控件通知处理程序代码

	int count  =m_listoperate.GetItemCount();
	for (int i = count-1; i >=0 ; i--)
	{
		if (m_listoperate.GetItemState(i,LVIS_SELECTED) == LVIS_SELECTED)
		{
			m_listoperate.DeleteItem(i);
		}
	}

	return;
}


int OperationConfig::DoModal() 
{
//	LoadInfo();
	return CDialog::DoModal();
}


BOOL OperationConfig::PreCreateWindow(CREATESTRUCT& cs) 
{
	memset(&mysOperate,0,sizeof(Tel_Operate));
	memset(&mysLaneConfig,0,sizeof(Tel_LaneConfig));

	return CDialog::PreCreateWindow(cs);
}
