// LaneConfig.cpp : implementation file
//

#include "stdafx.h"
#include "setIniOcx.h"
#include "LaneConfig.h"

#include "public.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// LaneConfig dialog
bool LaneConfig::inited = false;

LaneConfig::LaneConfig(CWnd* pParent /*=NULL*/)
	: CDialog(LaneConfig::IDD, pParent)
	, m_info(_T(""))
{
	//{{AFX_DATA_INIT(LaneConfig)
	img = 0;
	pConfigImage  = 0;
	inited = false;
	ptNum = 0;
	ptNum_i = 0;
	lptNum = 0;
	lptNum_i = 0;
	ptSum =0;
	modified = false;
	startDraw = false;
	modified = false;
	m_dc =0;
	//}}AFX_DATA_INIT
}

void LaneConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LaneConfig)
	DDX_Control(pDX, IDC_CONFIGTYPE, m_configtype);
	DDX_Control(pDX, IDC_NUM, m_number);
	DDX_Control(pDX, IDC_ID, m_ID);
	DDX_Control(pDX, IDC_SRC, m_src);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_STATIC2, m_info);
}


BEGIN_MESSAGE_MAP(LaneConfig, CDialog)
	//{{AFX_MSG_MAP(LaneConfig)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_START_DRAW, OnStartDraw)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_FORGO, OnForgo)
	ON_BN_CLICKED(IDC_RETURN, OnReturn)
	ON_CBN_SELCHANGE(IDC_CONFIGTYPE, OnSelchangeConfigtype)
	ON_CBN_SETFOCUS(IDC_CONFIGTYPE, OnSetfocusConfigtype)
	ON_WM_CREATE()
	ON_CBN_SETFOCUS(IDC_NUM, OnSetfocusNum)
	ON_CBN_SELCHANGE(IDC_NUM, OnSelchangeNum)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_DELETE_RGN, &LaneConfig::OnBnClickedDeleteRgn)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LaneConfig message handlers



BOOL LaneConfig::OnInitDialog() 
{
	//	if(!inited) 		memset(&tempLaneConfig,0,sizeof(Tel_LaneConfig));
	inited = true;
	startDraw = false;

	CDialog::OnInitDialog();

	GetDlgItem(IDC_START_DRAW)->EnableWindow(true);
	GetDlgItem(IDC_SAVE)->EnableWindow(false);
	GetDlgItem(IDC_FORGO)->EnableWindow(false);

	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);// gdi+ com init and start

	int i;
	for ( i = 0; i < 5; i ++)
	{
		m_configtype.InsertString(i,config[i]);
	}

	m_number.InsertString(0,"0");
	m_ID.InsertString(0,"0");
	for ( i = 0; i < 4; i ++)
	{
		m_number.InsertString(i+1,num[i]);
		m_ID.InsertString(i+1,num[i]);
	}

	m_configtype.SetCurSel(1);
	//	OnSelchangeConfigtype();
	m_number.SetCurSel(0);
	m_ID.SetCurSel(0);

	pConfigImage = img;
	//	pDrawImage = cvCloneImage(pConfigImage);

		UpdateDraws();

	return TRUE;  
}

void LaneConfig::OnPaint() 
{
	CPaintDC dc(this); 
	ShowPic();
	//	UpdateDraws();
	UpdateShow();
}
void LaneConfig::ShowPic()
{
	if(img==NULL) return;
	CRect rect;
	GetDlgItem(IDC_SRC)->GetClientRect(&rect);
	DrawImg2Hdc( img, IDC_SRC, this, rect);
}
/*
判断点pt 在多边形 pList 内部还是外部 
方法: 弧长法
优点：实现简单，具有很高的精度，只做乘法和减法
条件：点集合pList 是按照逆时针/逆时针排列的
http://blog.163.com/liling2009@126/blog/static/776556032011927105344884/
*/
bool PtInRectArc(CPoint pt, CPoint *list, int n)
{
	CPoint *pList = new CPoint[n] ;
	memcpy(pList, list, n*sizeof(CPoint));
	if(n<=0) return false;
	int t1, t2, sum, f, i;  
	for(int i = 0; i<n; i++) 
	{
		pList[i].x -= pt.x;
		pList[i].y -= pt.y;  
	}
	t1 = pList[0].x>=0 ?(pList[0].y>=0?0:3) :(pList[0].y>=0?1:2);    
	for(sum = 0, i = 1; i < n; i++)  
	{  
		if(!pList[i].x && !pList[i].y) break;              
		f = pList[i].y * pList[i-1].x - pList[i].x * pList[i-1].y;    
		if(!f && pList[i-1].x*pList[i].x <= 0 && pList[i-1].y*pList[i].y <= 0) break;    
		t2 = pList[i].x>=0 ?(pList[i].y>=0?0:3) :(pList[i].y>=0?1:2);    
		if(t2 ==(t1 + 1) % 4) sum += 1;          
		else if(t2 ==(t1 + 3) % 4) sum -= 1;    
		else if(t2 ==(t1 + 2) % 4)                
		{                                              
			if(f > 0) sum += 2;  
			else sum -= 2;  
		}  
		t1 = t2;  
	}  
	if(i<n || sum) return true;  
	return false;  

}

BOOL LaneConfig::PreTranslateMessage(MSG* pMsg) 
{
	UpdateData();
	CRect r;
	CPoint point;
	CString str;

	m_src.GetClientRect(&r);
	m_dc = GetDlgItem(IDC_SRC)->GetDC();

	point = pMsg->pt;
	m_src.ScreenToClient(&point);
	CPen penR(PS_SOLID, 1, RGB(255,0,0));
	CPen penG(PS_SOLID, 1, RGB(0,255,0));
	CPen penB(PS_SOLID, 1, RGB(0,0,255));
	CBrush brushR;
	brushR.CreateSolidBrush(RGB(255,0,0));

	CString strInfo;
	if(pMsg->message == WM_LBUTTONDOWN)
	{
	//	MessageBox("WM_LBUTTONDOWN ");
		strInfo.Format("point:(%d,%d)  Rect:(%d,%d)(%d,%d)",point.x, point.y, r.left, r.top, r.right, r.bottom );		
		if( PtInRect(r,point ))
		{
			//鼠标点击的位置在该画图区域
			strInfo.Format("%s   PtInRect: YES ", strInfo);
			m_info = strInfo;
			UpdateData(false);
			if(!startDraw)
			{
				// 选择浏览模式
				MessageBox("选择浏览模式 ");
				int selIndex = m_configtype.GetCurSel();
				if(selIndex<=2)// Region
				{
					if(ptNum_i>=4){
						return true;
					}
					CPoint** list;
					//config[5] = { "检测区域","违章停车区域","黄线区域",  "停止线","抓拍线"};//区域名称
					int sum=0;
					switch(selIndex)
					{
					case 0: //检测区域
						sum = tempLaneConfig.detRegion.iNum;
						list = new CPoint*[sum];
						for(int k=0; k<sum; k++)
						{	
							list[k] = new CPoint[5];
							list[k][0] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.detRegion.region[k].LeftTop));
							list[k][1] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.detRegion.region[k].RightTop));
							list[k][2] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.detRegion.region[k].RightBottom));
							list[k][3] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.detRegion.region[k].LeftBottom));
							list[k][4] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.detRegion.region[k].LeftTop));
							bool isIn =  PtInRectArc( point ,list[k], 5);
							if(isIn)
							{
								m_ID.SetCurSel(k+1);
								CBrush brush(RGB(rand()%256, rand()%256, rand()%256));//画刷 
								CClientDC dc(CWnd::FromHandle(m_src.GetSafeHwnd()));
								dc.SelectObject(&brush);
								dc.Polygon(list[k],5);
								//	dc.FillRect(CRect(list[k][0],list[k][2]),&brush);
								int dt=3;
								dc.Ellipse(point.x-dt, point.y-dt, point.x+dt, point.y+dt);
								break;
							}
						}
						break;
					case 1: //违章停车区域
						sum = tempLaneConfig.parkingRegion.iNum;
						list = new CPoint*[sum];
						for(int k=0; k<sum; k++)
						{	
							list[k] = new CPoint[5];
							list[k][0] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.parkingRegion.region[k].LeftTop));
							list[k][1] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.parkingRegion.region[k].RightTop));
							list[k][2] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.parkingRegion.region[k].RightBottom));
							list[k][3] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.parkingRegion.region[k].LeftBottom));
							list[k][4] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.parkingRegion.region[k].LeftTop));
							bool isIn =  PtInRectArc( point ,list[k], 5);
							if(isIn)
							{
								m_ID.SetCurSel(k+1);
								CBrush brush(RGB(rand()%256, rand()%256, rand()%256));//画刷 
								CClientDC dc(CWnd::FromHandle(m_src.GetSafeHwnd()));
								dc.SelectObject(&brush);
								dc.Polygon(list[k],5);
								//dc.FillRect(CRect(list[k][0],list[k][2]),&brush);
								int dt=3;
								dc.Ellipse(point.x-dt, point.y-dt, point.x+dt, point.y+dt);
								break;
							}
							//MessageBox("违章停车区域");
						}
						break;
					case 2: //黄线区域
						sum = tempLaneConfig.yellowLineRegion.iNum;
						list = new CPoint*[sum];
						for(int k=0; k<sum; k++)
						{	
							list[k] = new CPoint[5];
							list[k][0] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.yellowLineRegion.region[k].LeftTop));
							list[k][1] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.yellowLineRegion.region[k].RightTop));
							list[k][2] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.yellowLineRegion.region[k].RightBottom));
							list[k][3] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.yellowLineRegion.region[k].LeftBottom));
							list[k][4] =  M2CConvertPt( Telpoint2Point( tempLaneConfig.yellowLineRegion.region[k].LeftTop));
							bool isIn =  PtInRectArc( point ,list[k], 5);
							if(isIn)
							{
								m_ID.SetCurSel(k+1);
								CBrush brush(RGB(rand()%256, rand()%256, rand()%256));//画刷 
								CClientDC dc(CWnd::FromHandle(m_src.GetSafeHwnd()));
								dc.SelectObject(&brush);
								dc.Polygon(list[k],5);
								//dc.FillRect(CRect(list[k][0],list[k][2]),&brush);
								int dt=3;
								dc.Ellipse(point.x-dt, point.y-dt, point.x+dt, point.y+dt);
								break;
							}
						}
						break;
					}

					if(list!=0)
						delete list;
				}
			}
			else if (startDraw) //	WM_LBUTTONDOWN
			{
				//画区域或者线模式
				if(m_configtype.GetCurSel()<=2)// Region
				{
					MessageBox("画区域模式 ");
					if(ptNum_i>=4){
						startDraw = false;
						return true;
					}
					m_dc->SelectObject(&brushR);
					int dt=3;
					m_dc->Ellipse(point.x-dt, point.y-dt, point.x+dt, point.y+dt);

					pt[ptNum][ptNum_i++] = point;
					if(ptNum_i>=2) {
						m_dc->SelectObject(&penG);
						m_dc->MoveTo(pt[ptNum][ptNum_i-1]);
						m_dc->LineTo(pt[ptNum][ptNum_i-2]);
					}
					if(ptNum_i==4){// the 4 points of one Region
						m_dc->SelectObject(&penG);
						m_dc->MoveTo(pt[ptNum][0]);
						m_dc->LineTo(pt[ptNum][ptNum_i-1]);

						GetDlgItem(IDC_SAVE)->EnableWindow(true);
						GetDlgItem(IDC_FORGO)->EnableWindow(true);

						if( ptNum < m_number.GetCurSel()-1) {
							ptNum_i = 0;
							ptNum++;
							m_ID.SetCurSel(ptNum);
							str.Format("请画第 %d 个区域",ptNum+1);
							AfxMessageBox(str);
						}
						else
						{
							startDraw = false;
						}
					}
				}
				else {//Line
					MessageBox("startDraw  线模式");
					if(lptNum_i>=2){
						startDraw = false;
						return true;
					}
					m_dc->SelectObject(&brushR);
					int dt=3;
					m_dc->Ellipse(point.x-dt, point.y-dt, point.x+dt, point.y+dt);

					lpt[lptNum][lptNum_i++] = point;
					if(lptNum_i==2) {
						m_dc->SelectObject(&penG);
						m_dc->MoveTo(lpt[lptNum][lptNum_i-1]);
						m_dc->LineTo(lpt[lptNum][lptNum_i-2]);

						GetDlgItem(IDC_SAVE)->EnableWindow(true);
						GetDlgItem(IDC_FORGO)->EnableWindow(true);
						startDraw = false;
						/*
						if( lptNum < m_number.GetCurSel()) {
						lptNum_i = 0;
						lptNum++;
						m_ID.SetCurSel(lptNum);
						str.Format("请画第 %d 条线",lptNum+1);
						AfxMessageBox(str);
						}
						*/
					}
				}

			}
		}
	}
	if (PtInRect(r,point ) && pMsg->message == WM_MOUSEMOVE) 
	{


	}
	if (PtInRect(r,point ) && pMsg->message == WM_LBUTTONUP)
	{
		iPointIndex = -1;
	}
	
	
	return CDialog::PreTranslateMessage(pMsg);
}

void LaneConfig::DrawImage()
{

}

void LaneConfig::OnStartDraw() 
{
	UpdateData(true);

	if(m_number.GetCurSel()<1)
		return;

	ptNum = 0;
	ptNum_i = 0;
	lptNum = 0;
	lptNum_i = 0;
	startDraw = true;

	m_configtype.EnableWindow(false);
	m_number.EnableWindow(false);
	m_ID.EnableWindow(false);
	GetDlgItem(IDC_START_DRAW)->EnableWindow(false);

	Invalidate();
}

void LaneConfig::OnSave() 
{
	int iTypeIndex =((CComboBox*)GetDlgItem(IDC_CONFIGTYPE))->GetCurSel();	
	CString lbStr, tstr;
	int i=0;
	int index = m_configtype.GetCurSel();
	//	m_configtype.GetLBText(index, lbStr);
	switch(index)
	{
	case 0:
		tempLaneConfig.detRegion.iNum = m_number.GetCurSel()+1;
		for(i=0;i<tempLaneConfig.detRegion.iNum; i++){
			tempLaneConfig.detRegion.region[i].iID = i + 1;
			tempLaneConfig.detRegion.region[i].LeftTop = Point2Telpoint( C2MConvertPt(pt[i][0]) );
			tempLaneConfig.detRegion.region[i].RightTop = Point2Telpoint( C2MConvertPt(pt[i][1]) );
			tempLaneConfig.detRegion.region[i].RightBottom = Point2Telpoint( C2MConvertPt(pt[i][2]) );
			tempLaneConfig.detRegion.region[i].LeftBottom = Point2Telpoint( C2MConvertPt(pt[i][3]) );
		}
		break;
	case 1:
		tempLaneConfig.parkingRegion.iNum = m_number.GetCurSel()+1;
		for(i=0;i<tempLaneConfig.parkingRegion.iNum; i++){
			tempLaneConfig.parkingRegion.region[i].iID = i + 1;
			tempLaneConfig.parkingRegion.region[i].LeftTop = Point2Telpoint( C2MConvertPt(pt[i][0]) );
			tempLaneConfig.parkingRegion.region[i].RightTop = Point2Telpoint( C2MConvertPt(pt[i][1]) );
			tempLaneConfig.parkingRegion.region[i].RightBottom = Point2Telpoint( C2MConvertPt(pt[i][2]) );
			tempLaneConfig.parkingRegion.region[i].LeftBottom = Point2Telpoint( C2MConvertPt(pt[i][3]) );
		}
		break;
	case 2:
		tempLaneConfig.yellowLineRegion.iNum = m_number.GetCurSel()+1;
		for(i=0;i<tempLaneConfig.yellowLineRegion.iNum; i++){
			tempLaneConfig.yellowLineRegion.region[i].iID = i + 1;
			tempLaneConfig.yellowLineRegion.region[i].LeftTop = Point2Telpoint( C2MConvertPt(pt[i][0]) );
			tempLaneConfig.yellowLineRegion.region[i].RightTop = Point2Telpoint( C2MConvertPt(pt[i][1]) );
			tempLaneConfig.yellowLineRegion.region[i].RightBottom = Point2Telpoint( C2MConvertPt(pt[i][2]) );
			tempLaneConfig.yellowLineRegion.region[i].LeftBottom = Point2Telpoint( C2MConvertPt(pt[i][3]) );
		}
		break;
	case 3:
		for(i=0;i<1; i++){
			tempLaneConfig.stopLine.startPoint = Point2Telpoint( C2MConvertPt(lpt[i][0]) );
			tempLaneConfig.stopLine.endPoint = Point2Telpoint( C2MConvertPt(lpt[i][1]) );
		}
		break;
	case 4:
		for(i=0;i<1; i++){
			tempLaneConfig.triggerLine.startPoint = Point2Telpoint( C2MConvertPt(lpt[i][0]) );
			tempLaneConfig.triggerLine.endPoint = Point2Telpoint( C2MConvertPt(lpt[i][1]) );
		}
		break;
	default:
		break;
	}
	modified = true;
	startDraw = false;

	m_configtype.EnableWindow(true);
	m_number.EnableWindow(true);
	m_ID.EnableWindow(true);

	GetDlgItem(IDC_START_DRAW)->EnableWindow(true);
	GetDlgItem(IDC_SAVE)->EnableWindow(false);
	GetDlgItem(IDC_FORGO)->EnableWindow(false);

}

//放弃
void LaneConfig::OnForgo() 
{
	m_configtype.EnableWindow(true);
	m_number.EnableWindow(true);
	m_ID.EnableWindow(true);

	GetDlgItem(IDC_START_DRAW)->EnableWindow(true);
	GetDlgItem(IDC_SAVE)->EnableWindow(false);
	GetDlgItem(IDC_FORGO)->EnableWindow(false);
}

void LaneConfig::OnReturn() 
{
	CDialog::OnOK();	
}

//屏幕坐标转换到与图像相对的实际坐标
CPoint LaneConfig::C2MConvertPt(CPoint cpt)
{
	CRect rect;
	m_src.GetWindowRect(rect);
	ScreenToClient(&rect);
	double bw = img->GetWidth()*1.0 / rect.Width();
	double bh = img->GetHeight()*1.0 / rect.Height();
	cpt.x *= (long)bw;
	cpt.y *= (long)bh;
	return cpt;
}
//图像的实际坐标转换到屏幕坐标
CPoint LaneConfig::M2CConvertPt(CPoint cpt)
{
	CRect rect;
	m_src.GetWindowRect(rect);
	ScreenToClient(&rect);
	double bw = img->GetWidth()*1.0 / rect.Width();
	double bh = img->GetHeight()*1.0 / rect.Height();
	cpt.x /= (long)bw;
	cpt.y /= (long)bh;
	return cpt;
}
// 更新界面的区域或线
long LaneConfig::UpdateDraws(void)
{
	int i;
	int index = m_configtype.GetCurSel();
	switch(index)
	{
	case 0:
		ptSum = tempLaneConfig.detRegion.iNum;
		for(i=0;i<tempLaneConfig.detRegion.iNum; i++){
			tempLaneConfig.detRegion.region[i].iID;
			pt[i][0] = M2CConvertPt( Telpoint2Point(tempLaneConfig.detRegion.region[i].LeftTop) ) ;
			pt[i][1] = M2CConvertPt( Telpoint2Point(tempLaneConfig.detRegion.region[i].RightTop ));
			pt[i][2] = M2CConvertPt( Telpoint2Point(tempLaneConfig.detRegion.region[i].RightBottom ));
			pt[i][3] = M2CConvertPt( Telpoint2Point(tempLaneConfig.detRegion.region[i].LeftBottom ));
		}
		drawtype = DrawRegion;
		break;
	case 1:
		ptSum = tempLaneConfig.parkingRegion.iNum;
		for(i=0;i<tempLaneConfig.parkingRegion.iNum; i++){
			tempLaneConfig.parkingRegion.region[i].iID;
			pt[i][0] = M2CConvertPt( Telpoint2Point(tempLaneConfig.parkingRegion.region[i].LeftTop) ) ;
			pt[i][1] = M2CConvertPt( Telpoint2Point(tempLaneConfig.parkingRegion.region[i].RightTop ));
			pt[i][2] = M2CConvertPt( Telpoint2Point(tempLaneConfig.parkingRegion.region[i].RightBottom ));
			pt[i][3] = M2CConvertPt( Telpoint2Point(tempLaneConfig.parkingRegion.region[i].LeftBottom ));
		}
		drawtype = DrawRegion;
		break;
	case 2:
		ptSum = tempLaneConfig.yellowLineRegion.iNum;
		for(i=0;i<tempLaneConfig.yellowLineRegion.iNum; i++){
			tempLaneConfig.yellowLineRegion.region[i].iID ;
			pt[i][0] = M2CConvertPt( Telpoint2Point(tempLaneConfig.yellowLineRegion.region[i].LeftTop) ) ;
			pt[i][1] = M2CConvertPt( Telpoint2Point(tempLaneConfig.yellowLineRegion.region[i].RightTop ));
			pt[i][2] = M2CConvertPt( Telpoint2Point(tempLaneConfig.yellowLineRegion.region[i].RightBottom ));
			pt[i][3] = M2CConvertPt( Telpoint2Point(tempLaneConfig.yellowLineRegion.region[i].LeftBottom ));
		}
		drawtype = DrawRegion;
		break;
	case 3:
		ptSum = 1;
		for(i=0;i<1; i++){
			lpt[i][0] = M2CConvertPt( Telpoint2Point(tempLaneConfig.stopLine.startPoint ));
			lpt[i][1] = M2CConvertPt( Telpoint2Point(tempLaneConfig.stopLine.endPoint ));
		}
		drawtype = Line;
		break;
	case 4:
		ptSum = 1;
		for(i=0;i<1; i++){
			lpt[i][0] = M2CConvertPt( Telpoint2Point(tempLaneConfig.triggerLine.startPoint ));
			lpt[i][1] = M2CConvertPt( Telpoint2Point(tempLaneConfig.triggerLine.endPoint ));
		}
		drawtype = Line;
		break;
	default:
		break;
	}

	//	int sel = ptSum-1 >=0? ptSum : 0;
	m_number.SetCurSel(ptSum);
	if(ptSum>0) m_ID.SetCurSel(1);
	else m_ID.SetCurSel(0);
	UpdateShow();
	return 0;
}

void LaneConfig::OnSelchangeConfigtype() 
{
	//	UpdateWindow();
	Invalidate();
	UpdateData();	
	UpdateDraws();
}	

void LaneConfig::UpdateShow()
{

	CPen penR(PS_SOLID, 1, RGB(255,0,0));
	CPen penG(PS_SOLID, 1, RGB(0,255,0));
	CPen pen(PS_SOLID, 1, RGB(rand()%256, rand()%256, rand()%256));
	CBrush brushR;
	brushR.CreateSolidBrush(RGB(255,0,0));

	//	AfxMessageBox("UpdateShow");
	int i,j;
	if(drawtype==DrawRegion){
		for(i=0; i<ptSum; i++){ 
			for(j=0; j<4; j++){ 
				CPoint point(pt[i][j]);

				m_dc->SelectObject(&brushR);
				int dt=3;
				m_dc->Ellipse(point.x-dt, point.y-dt, point.x+dt, point.y+dt);

				if(j>=1) {
					m_dc->SelectObject(&pen);
					m_dc->MoveTo(pt[i][j-1]);
					m_dc->LineTo(pt[i][j]);
				}
				if(j==3){
					m_dc->SelectObject(&pen);
					m_dc->MoveTo(pt[i][0]);
					m_dc->LineTo(pt[i][3]);
				}
			}
		}
	}
	else if(drawtype==Line){
		for(i=0; i<1; i++){ 
			for(j=0; j<2; j++){ 
				CPoint point(lpt[i][j]);

				m_dc->SelectObject(&brushR);
				int dt=3;
				m_dc->Ellipse(point.x-dt, point.y-dt, point.x+dt, point.y+dt);

				if(j>=1) {
					m_dc->SelectObject(&pen);
					m_dc->MoveTo(lpt[i][j-1]);
					m_dc->LineTo(lpt[i][j]);
				}
			}
		}
	}

}


void LaneConfig::OnSetfocusConfigtype() 
{
	//	Invalidate();	
}

int LaneConfig::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}

BOOL LaneConfig::PreCreateWindow(CREATESTRUCT& cs) 
{
	memset(&tempLaneConfig,0,sizeof(Tel_LaneConfig));
	return CDialog::PreCreateWindow(cs);
}

void LaneConfig::OnSetfocusNum() 
{
	//	Invalidate();
}

void LaneConfig::OnSelchangeNum() 
{

}

void LaneConfig::OnCancel() 
{
	/*	if(modified){
	int ret = MessageBox("是否保存?", "重要提示", MB_YESNOCANCEL | MB_ICONWARNING |MB_ICONQUESTION  );
	if( ret==IDYES ){
	OnSave();
	CDialog::OnOK();
	}
	else if(ret==IDCANCEL)
	return;
	else ;
	}*/
	CDialog::OnCancel();
}


void LaneConfig::OnBnClickedDeleteRgn()
{
	//删除某个区域
	UpdateData();
	int i;
	int indexType	=  m_configtype.GetCurSel();
	int indexID		=  m_ID.GetCurSel();
	switch(indexType)
	{
	case 0:
		if(indexID<tempLaneConfig.detRegion.iNum)
		{
			int k=0; 
			while(k+1<indexID)
				k++;
			for( ; k<tempLaneConfig.detRegion.iNum-1; k++)
			{
				tempLaneConfig.detRegion.region[k] =tempLaneConfig.detRegion.region[k+1];
			}
		}
		tempLaneConfig.detRegion.iNum--;
		tempLaneConfig.detRegion.iNum = tempLaneConfig.detRegion.iNum<0? 0: tempLaneConfig.detRegion.iNum;
		break;
	case 1:
		if(indexID<tempLaneConfig.parkingRegion.iNum)
		{
			int k=0; 
			while(k+1<indexID)
				k++;
			for( ; k<tempLaneConfig.parkingRegion.iNum-1; k++)
			{
				tempLaneConfig.parkingRegion.region[k] =tempLaneConfig.parkingRegion.region[k+1];
			}
		}
		tempLaneConfig.parkingRegion.iNum--;
		tempLaneConfig.parkingRegion.iNum = tempLaneConfig.parkingRegion.iNum<0? 0: tempLaneConfig.parkingRegion.iNum;
		break;
	case 2:
		if(indexID<tempLaneConfig.yellowLineRegion.iNum)
		{
			int k=0; 
			while(k+1<indexID)
				k++;
			for( ; k<tempLaneConfig.yellowLineRegion.iNum-1; k++)
			{
				tempLaneConfig.yellowLineRegion.region[k] =tempLaneConfig.yellowLineRegion.region[k+1];
			}
		}
		tempLaneConfig.yellowLineRegion.iNum--;
		tempLaneConfig.yellowLineRegion.iNum = tempLaneConfig.yellowLineRegion.iNum<0? 0: tempLaneConfig.yellowLineRegion.iNum;
		break;
	case 3:
		tempLaneConfig.stopLine.startPoint = tempLaneConfig.stopLine.endPoint = Point2Telpoint(CPoint(0,0));
		break;
	case 4:
		tempLaneConfig.triggerLine.startPoint = tempLaneConfig.triggerLine.endPoint = Point2Telpoint(CPoint(0,0));
		break;
	case 5:
		break;
	}
	OnSelchangeConfigtype();
}


