// Progress.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "Progress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgress dialog


CProgress::CProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgress)
	m_title = _T("");
	m_totalSize = _T("");
	m_curSize = _T("");
	m_Percentage = _T("");
	//}}AFX_DATA_INIT
}


void CProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgress)
	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
	DDX_Text(pDX, IDC_TITLE, m_title);
	DDX_Text(pDX, IDC_TOTAL_SIZE, m_totalSize);
	DDX_Text(pDX, IDC_CURRENT_SIZE, m_curSize);
	DDX_Text(pDX, IDC_Percentage, m_Percentage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgress, CDialog)
	//{{AFX_MSG_MAP(CProgress)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProgress message handlers
void CProgress::SetProcessPos(int pos)
{
	m_progress.SetPos(pos);
}

void CProgress::ShowProcess(long totalSize, long curSize, char* filename, int flag)
{
	int low=0, up=0;
	m_progress.GetRange(low, up);
	float b = curSize*1.0/totalSize;
	m_progress.SetPos( up*b );
	CString strShow;
	switch(flag){
		case 0:
		case 1:
			strShow = "";
			break;
		case -1:
			strShow = "上传/下载失败";
			break;
		case -2:
			strShow = "文件不存在";
			break;
	}
	if(flag==1){
		m_title.Format("正在上传文件: %s  %s", filename, strShow);
	}
	else m_title.Format("正在下载文件: %s  %s", filename, strShow);

	int unit = 2;
	if(totalSize>unit) {
		m_totalSize.Format("%0.2g KB", totalSize*1.0/unit);
		m_curSize.Format("%0.2g KB", curSize*1.0/unit);
	}
	else { 
		m_totalSize.Format("%d B", totalSize);
		m_curSize.Format("%d B", curSize);
	}
	m_Percentage.Format("%d %%", (int)(b*100.0));

	UpdateData(false);
}

BOOL CProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_progress.SetRange(1,1024);
	m_progress.SetStep(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgress::Close()
{
	CDialog::OnOK();
}

void CProgress::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));	
	CDialog::OnLButtonDown(nFlags, point);
}
