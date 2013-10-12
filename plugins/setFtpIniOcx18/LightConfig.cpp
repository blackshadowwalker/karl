// LightConfig.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "LightConfig.h"

#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LightConfig dialog


LightConfig::LightConfig(CWnd* pParent /*=NULL*/)
	: CDialog(LightConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(LightConfig)
		img=0;
	//}}AFX_DATA_INIT
}


void LightConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LightConfig)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LightConfig, CDialog)
	//{{AFX_MSG_MAP(LightConfig)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LightConfig message handlers

void LightConfig::ShowPic()
{
	if(img==NULL) return;
//	img = cvLoadImage("config/1.jpg",1);
//	cvNamedWindow("Picture",1);	cvShowImage("Picture",img);
	CRect rect; 
	GetDlgItem(IDC_IMAGE_LIGHT)->GetClientRect(&rect);
	DrawImg2Hdc( img, IDC_IMAGE_LIGHT, this, rect);

}

BOOL LightConfig::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  
}

void LightConfig::OnPaint() 
{
	CPaintDC dc(this);  
	ShowPic();
}
