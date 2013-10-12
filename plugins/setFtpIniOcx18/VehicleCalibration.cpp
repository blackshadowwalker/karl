// VehicleCalibration.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "VehicleCalibration.h"

#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VehicleCalibration dialog
IMPLEMENT_DYNAMIC(VehicleCalibration, CDialog)

VehicleCalibration::VehicleCalibration(CWnd* pParent /*=NULL*/)
	: CDialog(VehicleCalibration::IDD, pParent)
{
	//{{AFX_DATA_INIT(VehicleCalibration)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void VehicleCalibration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VehicleCalibration)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VehicleCalibration, CDialog)
	//{{AFX_MSG_MAP(VehicleCalibration)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VehicleCalibration message handlers
void VehicleCalibration::ShowPic()
{
	if(img==NULL) return;
//	img = cvLoadImage("config/1.jpg",1);
//	cvNamedWindow("Picture",1);	cvShowImage("Picture",img);
	CRect rect;
 
	GetDlgItem(IDC_IMAGE_VEH)->GetClientRect(&rect);
	DrawImg2Hdc( img, IDC_IMAGE_VEH, this, rect);

}

void VehicleCalibration::OnPaint() 
{
	CPaintDC dc(this); 
	ShowPic();
}
