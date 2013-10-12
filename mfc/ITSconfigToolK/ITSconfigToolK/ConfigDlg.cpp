// ConfigDlg.cpp : 实现文件
//
/*
* call this dialog demo :
* CConfigDlg dlg;
* dlg.setBackgroundImage(imgPath);
* dlg.DoModel();
*
*/

#include "stdafx.h"
#include <math.h>
#include <stdio.h>
 
#include "ITSconfigToolK.h"
#include "ConfigDlg.h"
#include "afxdialogex.h"
#include "public.h"

#define PointColor		RGB(255,0,0) // 点的颜色
#define selectedColor	RGB(0,255,0) // 当前选择的线/车道的显示颜色
#define LineColor		RGB(255,0,0) // 车道/线的显示颜色

#define penWidth	5	//画笔粗细
#define lineSpan	10	//
#define radius		5	//圆点半径
#define radiueSpan	50	//
#define point2LineSpan	penWidth*2+radius	//鼠标点与圆心的MAX距离


//场景模式
#define screenModeLen 4
const char*screemMode[screenModeLen]={"自动判别","白天模式","夜晚模式","黄昏夜晚模式"};

#define	snapLineLen		5
const char *snapLineString[snapLineLen] ={"直行停止线","左转停止线","右转停止线","直行闯红灯抓拍线","左右转直行抓拍线"};
const char *snapLineVar[snapLineLen] ={"ZhiStopLine","LeftStopLine","RightStopLine","ZhiTriggerLine","LeftRightTriggerLine"};

// CConfigDlg 对话框

IMPLEMENT_DYNAMIC(CConfigDlg, CDialogEx)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CConfigDlg::IDD, pParent)
{
	m_dc = 0;
	img = 0;
	memset(bgPicPath,0,256);
	rectId = 0;
	bStartDrawSnapLine = false;
	bStartDrawLaneLine = false;
	bSetSnapLines = false;
	bSetLaneLines = false;
	bModefyLane = false;
	bSetCaseRect = false;
	bEditCaseRect = false;
	
	memset(bgPicPath, 0, 256);

	lButtonDown = false;
	selectedPoint = 1;

	m_groupBoxLaneType = 0;
	m_groupBoxEventType = 0;

	retNum = 0;
	pointPtr = 0;
	memset(&m_snapLine, 0, sizeof(SnapLine));
	memset(&tempLine, 0, sizeof(Line));
	memset(tempstr, 0, 256);
}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCREEN_MODE, m_screenMode);
	DDX_Control(pDX, IDC_LIGHT_NUM, m_LightGroupNumber);
	DDX_Control(pDX, ID_IMAGE, m_imageFrame);
	DDX_Control(pDX, IDC_SNAP_LINES, m_snapLines);
	DDX_Control(pDX, IDC_LIGHT_ID, m_lightId);
	DDX_Control(pDX, IDC_LANE_ID, m_laneId);
	DDX_Control(pDX, IDC_VD_REGION_EDIT, bEditRectCon);

	DDX_Control(pDX, IDC_LANE_LINE, m_lane_line);
	DDX_Control(pDX, IDC_STATIC_SMALL, m_status);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialogEx)
	ON_BN_CLICKED(ID_TEST, &CConfigDlg::OnBnClickedTest)
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BT_ADD_SNAP_LINE, &CConfigDlg::OnBnClickedBtAddSnapLine)
	ON_BN_CLICKED(IDC_BT_SAVE, &CConfigDlg::OnBnClickedBtSave)
	ON_BN_CLICKED(IDC_BT_SET_LANE, &CConfigDlg::OnBnClickedBtSetLine)
	ON_CBN_SELCHANGE(IDC_LIGHT_NUM, &CConfigDlg::OnCbnSelchangeLightNum)
	ON_BN_CLICKED(IDC_BT_SET_LANE_PROP, &CConfigDlg::OnBnClickedBtSetLaneProp)
	ON_BN_CLICKED(IDC_BT_LANE_ADD, &CConfigDlg::OnBnClickedBtLaneAdd)
	ON_BN_CLICKED(IDC_BT_LANE_MODEFY, &CConfigDlg::OnBnClickedBtLaneModefy)
	ON_BN_CLICKED(IDC_BT_LANE_DELETE, &CConfigDlg::OnBnClickedBtLaneDelete)
	ON_BN_CLICKED(IDC_BT_LANE_CANCEL, &CConfigDlg::OnBnClickedBtLaneCancel)
	ON_CBN_SELCHANGE(IDC_LANE_ID, &CConfigDlg::OnCbnSelchangeLaneId)
	ON_BN_CLICKED(IDC_BT_SET_CASE_RECT, &CConfigDlg::OnBnClickedBtSetCaseRect)
	ON_BN_CLICKED(IDC_VD_REGION_EDIT, &CConfigDlg::OnBnClickedVdRegionEdit)
	ON_CBN_SELCHANGE(IDC_SNAP_LINES, &CConfigDlg::OnCbnSelchangeSnapLines)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CConfigDlg 消息处理程序


void CConfigDlg::PreInitDialog()
{
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);

	CDialogEx::PreInitDialog();
}

void CConfigDlg::setBackgroundImage(char *path)
{
	if(path==0 || strlen(path)<3)
		return;
	memcpy(bgPicPath, path, strlen(path));
}

BOOL CConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	int i,j;
	for(i=0; i<screenModeLen;i++)
		m_screenMode.AddString(screemMode[i]);
	for(i=0; i<snapLineLen; i++)
		m_snapLines.AddString(snapLineString[i]);

	m_LightGroupNumber.ResetContent();
	for(i=1; i<=4; i++){
		str.Format("%d",i);
		m_LightGroupNumber.AddString(str);
	}
	m_lightId.ResetContent();
	for(i=0; i<4; i++){
		str.Format("%d",i+1);
		m_lightId.AddString(str);
	}
	m_lightId.SetCurSel(0);
	m_screenMode.SetCurSel(0);
	m_LightGroupNumber.SetCurSel(0);
	m_snapLines.SetCurSel(0);

	for(i=1; i<=2; i++){
		str.Format("%d",i);
		m_lane_line.AddString(str);
	}
	if(strlen(bgPicPath)>2)
		setImage(bgPicPath,0);
	else
		setImage("d:\\wall\\001.jpg",0);
	readConfig();

	CRect checkboxRect, groupRect, r;
	int k;
	m_groupBoxLaneType = (CButton*)GetDlgItem(IDC_GROUP_LANETYPE);
	m_groupBoxLaneType->GetWindowRect(&groupRect);
	ScreenToClient(&groupRect);
	int checkid = IDC_LAN_TYPE_0;
	for(k=0;k<MAX_LANE_TYPE;k++){
		CButton *bt = (CButton*)GetDlgItem(checkid+k);
		bt->GetWindowRect(&checkboxRect);
		ScreenToClient(&checkboxRect);
		r.SetRect(checkboxRect.left - groupRect.left, 
					checkboxRect.top - groupRect.top,
					checkboxRect.right - groupRect.left,
					checkboxRect.bottom - groupRect.top);
		bt->SetParent((CButton*)m_groupBoxLaneType);
		bt->MoveWindow(r);
	}
//	m_groupBoxEventType->ShowWindow(true);

	char name[256]={0};
	m_groupBoxEventType = (CButton*)GetDlgItem(IDC_GROUP_EVENTTYPE);
	m_groupBoxEventType->GetWindowRect(&groupRect);
	ScreenToClient(&groupRect);
	checkid = IDC_EVENTTYPE_0;
	for(k=0;k<MAX_EVENT_TYPE;k++){
		CButton *bt = (CButton*)GetDlgItem(checkid+k);
		bt->GetWindowRect(&checkboxRect);
		ScreenToClient(&checkboxRect);
		r.SetRect(checkboxRect.left - groupRect.left, 
					checkboxRect.top - groupRect.top,
					checkboxRect.right - groupRect.left,
					checkboxRect.bottom - groupRect.top);
		bt->SetParent((CButton*)m_groupBoxEventType);
		bt->MoveWindow(r);
	}
	
	LaneVisible(false);
	LineVisible(false);
	VdRegionVisible(false);

	m_groupBoxEventType->EnableWindow(false);
	m_groupBoxLaneType->EnableWindow(false);
	GetDlgItem(IDC_LIGHT_ID)->EnableWindow(false);

	OnBnClickedBtSetLaneProp();

	return TRUE; 
}
// load and show image
// setImage(bgPicPath);
long CConfigDlg::setImage(char* filepath, bool bSHow /* = true */)
{
	if(strstr(filepath,":")==0)
		sprintf(bgPicPath,"%s/%s",CITSconfigToolKApp::getAppPath(),filepath);
	else
		sprintf(bgPicPath, filepath);
	if(img!=NULL)
		delete img;
	img = KLoadImage(bgPicPath);
	rectId = ID_IMAGE;
	//draw background-image
	CRect rect;
	GetDlgItem(rectId)->GetClientRect(&rect);
	if(img && rectId>1 && bSHow)
		DrawImg2Hdc( img, rectId, this, rect);
//	Invalidate();
	return 0;
}

void CConfigDlg::OnBnClickedTest()
{
	m_groupBoxEventType->ShowWindow(SW_SHOW);
	m_groupBoxEventType->MoveWindow(CRect(1,1,100,100));
}


void CConfigDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if ( ! lButtonDown){
		m_status.SetWindowText("");
		UpdateData(false);
		return ;
	}
	CRect r;
	m_imageFrame.GetWindowRect(&r);
	ScreenToClient(&r);
	if(!r.PtInRect(point))
		return;
	CPoint cpt(r.left,r.top);

	point = point - cpt;

	CDC *dc = m_dc;
	CBrush brushR;
	brushR.CreateSolidBrush(PointColor);
	CPen penR(PS_SOLID, penWidth ,PointColor);
	dc->SelectObject(&penR);
	//设置抓拍线
	if(bSetSnapLines){
		int index = m_snapLines.GetCurSel();
		if(index<0)
			return ;
		Line line = m_snapLine.getLine(index);
		tempcstr.Format("[%d](%d,%d)",index, line.startPoint.x, line.startPoint.y);
		if(selectedPoint==1){
			line.startPoint = point;
		}else if(selectedPoint==2)
			line.endPoint = point;
		else
			return;

		m_snapLine.setLine(index, line);
		OnCbnSelchangeSnapLines();
	}else if(bSetCaseRect){
		//设置感兴趣区域
		if(selectedCasePointIndex<0 || selectedCasePointIndex>=MAX_VDREGION)
			;
		else{
			vdRegion.vdRegionElem[selectedCasePointIndex].point = point;
			ReDrawCaseRect();
		}

	}else //设置停止/违章线
	if(bSetLaneLines){
		int lanid = m_laneId.GetCurSel();
		int lineid = m_lane_line.GetCurSel();
		if(lanid==-1 || lineid==-1)
			return;

		CLine *line=0;
		if(lineid==0) line = &m_lane[lanid].Line1;
		else if(lineid==1) line = &m_lane[lanid].Line2;

		if(selectedPoint==1){
			line->startPoint = point;
		}else if(selectedPoint==2)
			line->endPoint = point;
		else 
			return;
		OnCbnSelchangeLaneId();
	}

	tempcstr +="OnMouseMove";
	m_status.SetWindowText(tempcstr);
	UpdateData(false);

	CDialogEx::OnMouseMove(nFlags, point);
}

void CConfigDlg::OnLButtonDown(UINT nFlags, CPoint pt)
{
	lButtonDown = true;
	UpdateData(true);
	
	CPoint point;

	CRect r;
	m_imageFrame.GetWindowRect(&r);
	ScreenToClient(&r);
	if(r.PtInRect(pt))
	{
		int i=0;
		int dt=radius;
		CDC *dc = m_dc;
		CBrush brushR;
		brushR.CreateSolidBrush(selectedColor);
		CPen penR(PS_SOLID, penWidth,selectedColor);
		dc->SelectObject(&penR);
		CPoint cpt(r.left,r.top);

		point = pt - cpt;
		Line *gline=0;
		
		//重画区域
		//画停止/违章线 Line
		if(bStartDrawSnapLine)
		{
			dc->Ellipse(point.x-dt,point.y-dt, point.x+dt,point.y+dt);
			pointPtr ++;
			if(pointPtr==1)
				tempLine.startPoint = point;
			else if(pointPtr==2){
				tempLine.endPoint = point;
				dc->MoveTo(CPoint(tempLine.startPoint));
				dc->LineTo(CPoint(tempLine.endPoint));
				int index = m_snapLines.GetCurSel();
				m_snapLine.setLine(index, tempLine);
				bStartDrawSnapLine = false;
			}
		}
		// 检测区域
		else if(bSetCaseRect && bEditCaseRect){
			dc->Ellipse(point.x-dt,point.y-dt, point.x+dt,point.y+dt);
			pointPtr ++;
			if(vdRegion.length()>=MAX_VDREGION)
			{
				bEditCaseRect = false;
			}
			CPoint p = point;
			vdRegion.add(p);
			if(pointPtr>=2){
				setImage(bgPicPath);
				CPoint  firstPoint;
				bool	bFirst=true;
				for(i=0;i<MAX_VDREGION;i++){
					if(vdRegion.vdRegionElem[i].enable){
						if(!bFirst)
							dc->LineTo(vdRegion.vdRegionElem[i].point);
						dc->MoveTo(vdRegion.vdRegionElem[i].point);
						if(bFirst)
							firstPoint = vdRegion.vdRegionElem[i].point;
						bFirst = false;
					}
				}
				if(vdRegion.length()>=3)
					dc->LineTo(firstPoint);
			}
		}
		//画车道 Lane
		else if(bStartDrawLaneLine)
		{
			dc->Ellipse(point.x-dt,point.y-dt, point.x+dt,point.y+dt);
			tempLane.enable = true;
			pointPtr ++;
			if(pointPtr==1)
				tempLane.Line1.startPoint = point;
			else if(pointPtr==2){
				tempLane.Line1.endPoint = point;
				dc->MoveTo(CPoint(tempLane.Line1.startPoint));
				dc->LineTo(CPoint(tempLane.Line1.endPoint));
			}
			else if(pointPtr==3)
				tempLane.Line2.startPoint = point;
			else if(pointPtr==4){
				tempLane.Line2.endPoint = point;
				dc->MoveTo(CPoint(tempLane.Line2.startPoint));
				dc->LineTo(CPoint(tempLane.Line2.endPoint));

				int checkSum = 0;
				// checke other checkboxs
				//check lanetype
				int checkid = IDC_LAN_TYPE_0;
				checkSum = 0;
				for(i=0;i<MAX_LANE_TYPE;i++){
					CButton *bt = (CButton*)m_groupBoxLaneType->GetDlgItem(checkid+i);
					int bCheck = bt->GetCheck();
					tempLane.LaneType[i] = bCheck;
					if(bCheck==1) checkSum ++;
				}
				if(checkSum==0){
					alert("至少选择一个车道类型,返回重新添加!");
					OnBnClickedBtLaneCancel();
					return ;
				}
				tempLane.LaneTypeNum = checkSum;
				//check event
				checkid = IDC_EVENTTYPE_0;
				checkSum = 0;
				for(i=0;i<MAX_EVENT_TYPE;i++){
					CButton *bt = (CButton*)m_groupBoxEventType->GetDlgItem(checkid+i);
					int bCheck = bt->GetCheck();
					tempLane.EventType[i] = bCheck;
					if(bCheck==1) checkSum ++;
				}
				if(checkSum==0){
					alert("至少选择一个事件类型,返回重新添加!");
					OnBnClickedBtLaneCancel();
					return ;
				}
				tempLane.EventNumber = checkSum;
				//set light id
				tempLane.LightID = m_lightId.GetCurSel()<0? 1:(m_lightId.GetCurSel()+1);
				//copy lane info from templane 2 m_lane[i] whith is not enable
				if(bModefyLane){
					int index = m_laneId.GetCurSel();
					CString idstr;
					m_laneId.GetLBText(index, idstr);
					int selID = atoi(idstr);
				//	memcpy(&m_lane[index], &tempLane, sizeof(Lane));//这个地方是错误的，应该是获得TEXT，而不是 index ,\
																因为 如果删除了某个非最大ID的车道，此时index 和 text 不一致
					memcpy(&m_lane[index], &tempLane, sizeof(Lane));
				}
				else{
					for(i=0; i<MAX_LANE; i++){
						if(m_lane[i].enable==false){
							tempLane.LaneID = i+1;
							memcpy(&m_lane[i], &tempLane, sizeof(Lane));
							break;
						}
					}
					//画车道完成后，再添加该车道
					int lanid = tempLane.LaneID;
					tempcstr.Format("%d",lanid);
					m_laneId.AddString(tempcstr);
					m_laneId.SetCurSel(lanid-1);
				}
				bStartDrawLaneLine = false;
				m_groupBoxEventType->EnableWindow(false);
				m_groupBoxLaneType->EnableWindow(false);
				GetDlgItem(IDC_LIGHT_ID)->EnableWindow(false);
				GetDlgItem(IDC_BT_LANE_ADD)->EnableWindow(true);
				GetDlgItem(IDC_BT_LANE_CANCEL)->EnableWindow(false);
			}
		}
		else
		//拖动区域
		//设置抓拍线
		if(bSetSnapLines){
			for(int i=0; i<m_snapLine.Length(); i++)
			{
				Line line = m_snapLine.getLine(i);

				bool bOutLine = (point.x - line.startPoint.x)*(point.x-line.endPoint.x)>0 || (point.y - line.startPoint.y)*(point.y-line.endPoint.y)>0;
				int dis = DisPoint2Line(point,line);
				if(dis<point2LineSpan && !bOutLine){
					m_snapLines.SetCurSel(i);
					OnCbnSelchangeSnapLines();

					gline = &line;
					int dis1 = sqrt(pow((double)(point.x-gline->startPoint.x),2) + pow((double)(point.y-gline->startPoint.y),2));
					int dis2 = sqrt(pow((double)(point.x-gline->endPoint.x),2) + pow((double)(point.y-gline->endPoint.y),2));
					if(dis1<dis2 && dis1<radiueSpan){
						selectedPoint = 1;
					}
					else if(dis2<radiueSpan)
						selectedPoint = 2;
					else
						selectedPoint = -1;
					break;
				}
			}
		}else
		//设置停止/违章线
		if(bSetLaneLines){
			for(int i=0; i<MAX_LANE; i++){
				if(m_lane[i].enable){
					
					gline = &m_lane[i].Line1;
					int dis1 = sqrt(pow((double)(point.x-gline->startPoint.x),2) + pow((double)(point.y-gline->startPoint.y),2));
					int dis2 = sqrt(pow((double)(point.x-gline->endPoint.x),2) + pow((double)(point.y-gline->endPoint.y),2));
					if(dis1<dis2 && dis1<radiueSpan){
						selectedPoint = 1;
					}
					else if(dis2<radiueSpan)
						selectedPoint = 2;
					else
						selectedPoint = -1;

					bool bOutLine = (point.x - m_lane[i].Line1.startPoint.x)*(point.x-m_lane[i].Line1.endPoint.x)>0 || (point.y - m_lane[i].Line1.startPoint.y)*(point.y-m_lane[i].Line1.endPoint.y)>0;
					if(DisPoint2Line(point,m_lane[i].Line1)<point2LineSpan && !bOutLine){
						m_laneId.SetCurSel(i);
						m_lane_line.SetCurSel(0);
						OnCbnSelchangeLaneId();
						break;
					}

					gline = &m_lane[i].Line2;
					dis1 = sqrt(pow((double)(point.x-gline->startPoint.x),2) + pow((double)(point.y-gline->startPoint.y),2));
					dis2 = sqrt(pow((double)(point.x-gline->endPoint.x),2) + pow((double)(point.y-gline->endPoint.y),2));
					if(dis1<dis2 && dis1<radiueSpan){
						selectedPoint = 1;
					}
					else if(dis2<radiueSpan)
						selectedPoint = 2;
					else
						selectedPoint = -1;

					bOutLine = (point.x - m_lane[i].Line2.startPoint.x)*(point.x-m_lane[i].Line2.endPoint.x)>0 || (point.y - m_lane[i].Line2.startPoint.y)*(point.y-m_lane[i].Line2.endPoint.y)>0;
					if(DisPoint2Line(point,m_lane[i].Line2)<point2LineSpan && !bOutLine){
						m_laneId.SetCurSel(i);
						m_lane_line.SetCurSel(1);
						OnCbnSelchangeLaneId();
						break;
					}

				}
			}
		}else if(bSetCaseRect){
			//设置拖动检测区域点
			int minDis=-1;
			int minIndex=-1;
			int dis =0;
			for(i=0;i<MAX_VDREGION;i++){
				if(vdRegion.vdRegionElem[i].enable){
					double disx = point.x - vdRegion.vdRegionElem[i].point.x;
					double disy = point.y - vdRegion.vdRegionElem[i].point.y;
					tempcstr.Format("%d,%d",disx,disy);
				//	MessageBox(tempcstr);
					dis = sqrt(pow(disx,2) + pow(disy,2));
					if(i==0)
						minDis = dis;
					if(dis<radiueSpan && dis<=minDis){
						minDis = dis;
						minIndex = i;
						selectedCasePointIndex = i;
						dc->Ellipse(vdRegion.vdRegionElem[i].point.x - dt, vdRegion.vdRegionElem[i].point.y-dt,  vdRegion.vdRegionElem[i].point.x+dt, vdRegion.vdRegionElem[i].point.y+dt);
						ReDrawCaseRect();
					}
				}
			}
			
		}
	}
	else
		PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM((DWORD_PTR)(point.x), (DWORD_PTR)(point.y)));
	tempcstr.Format("OnLButtonDown (%d,%d)", point.x, point.y);
	m_status.SetWindowText(tempcstr);
	UpdateData(false);

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CConfigDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	if(&m_imageFrame!=NULL)
		m_dc = m_imageFrame.GetDC();
	//draw background-image
	int i;
	if(img && rectId>1000 )
	{
		CRect rect;
		GetDlgItem(rectId)->GetClientRect(&rect);
		DrawImg2Hdc( img, rectId, this, rect);

		int dt=radius;
		CDC *dc = m_dc;
		CBrush brushR;
		brushR.CreateSolidBrush(PointColor);
		CPen penR(PS_SOLID, penWidth,PointColor);
		dc->SelectObject(&penR);

		CRect r;
		m_imageFrame.GetWindowRect(&r);
		ScreenToClient(&r);

		//设置停止线
		if(bSetSnapLines)
		{
			for(i=0; i<m_snapLine.Length(); i++)
			{
				Line line = m_snapLine.getLine(i);
				CPoint t = line.startPoint - line.endPoint;
				if(abs(t.x)==0 && abs(t.y)==0 )
					continue;
	
				dc->MoveTo(CPoint(line.startPoint));
				dc->LineTo(CPoint(line.endPoint));
			}
		}
		//set Lane
		if(bSetLaneLines){
			for(i=0; i<MAX_LANE; i++){
				if(m_lane[i].enable){
					
					dc->MoveTo(CPoint(m_lane[i].Line1.startPoint));
					dc->LineTo(CPoint(m_lane[i].Line1.endPoint));
					dc->MoveTo(CPoint(m_lane[i].Line2.startPoint));
					dc->LineTo(CPoint(m_lane[i].Line2.endPoint));
				}
			}
		}
		if(bSetCaseRect)
		{
			setImage(bgPicPath);
			CPoint  firstPoint;
			bool	bFirst=true;
			for(i=0;i<MAX_VDREGION;i++){
				if(vdRegion.vdRegionElem[i].enable){
					if(!bFirst)
						dc->LineTo(vdRegion.vdRegionElem[i].point);
					dc->MoveTo(vdRegion.vdRegionElem[i].point);
					if(bFirst)
						firstPoint = vdRegion.vdRegionElem[i].point;
					bFirst = false;
				}
			}
			if(vdRegion.length()>=3)
				dc->LineTo(firstPoint);
		}
	}
}

void CConfigDlg::ReDrawCaseRect(){
	setImage(bgPicPath);
	CPoint  firstPoint;
	bool	bFirst=true;
	int i=0;
	m_dc = m_imageFrame.GetDC();

	CDC *dc = m_dc;

	CPen penR(PS_SOLID, penWidth,PointColor);
	CPen greenPen(PS_SOLID, penWidth,selectedColor);
	dc->SelectObject(&penR);

	int dt = radius;
	for(i=0;i<MAX_VDREGION;i++){
		if(vdRegion.vdRegionElem[i].enable){
			if(!bFirst)
				dc->LineTo(vdRegion.vdRegionElem[i].point);
			dc->MoveTo(vdRegion.vdRegionElem[i].point);
			if(bFirst)
				firstPoint = vdRegion.vdRegionElem[i].point;
			bFirst = false;

			if(selectedCasePointIndex==i)
				dc->SelectObject(&greenPen);
				
			dc->Ellipse(vdRegion.vdRegionElem[i].point.x - dt, vdRegion.vdRegionElem[i].point.y-dt,  vdRegion.vdRegionElem[i].point.x+dt, vdRegion.vdRegionElem[i].point.y+dt);
			
			dc->SelectObject(&penR);
		}
		
	}
	dc->SelectObject(&penR);
	if(vdRegion.length()>=3)
		dc->LineTo(firstPoint);
}


void CConfigDlg::OnBnClickedBtAddSnapLine()
{
	if(m_snapLines.GetCurSel()<0)
	{
		alert("请选择停止线类型");
		m_snapLines.SetFocus();
		return;
	}
	pointPtr = 0;
	bStartDrawSnapLine = true;
	memset(&tempLine, 0, sizeof(Line));
	m_dc = m_imageFrame.GetDC();
}
void CConfigDlg::OnBnClickedBtSave(){
	bEditRectCon.SetCheck(false);
	OnBnClickedVdRegionEdit();

	if(saveConfig())
		alert("保存成功!");
	readConfig();
	OnPaint();
}
bool CConfigDlg::saveConfig()
{
	UpdateData(true);
	int checkSum = 0;
	int i;

	//Format CPoint 2 imagePoints 
	CRect	rectRect;
	SIZE	rectSize, imageSize;
	imageSize.cx = img->GetWidth();
	imageSize.cy = img->GetHeight();
	m_imageFrame.GetWindowRect(&rectRect);
	rectSize.cx = rectRect.Width();
	rectSize.cy = rectRect.Height();
	for(i=0;i<MAX_LANE;i++){
		if(m_lane[i].enable)
			m_lane[i].FormatImagePoint(rectSize, imageSize);
	}
	tempLane.FormatImagePoint(rectSize, imageSize);
	vdRegion.FormatImagePoint(rectSize, imageSize);
	m_snapLine.FormatImagePoint(rectSize, imageSize);

	//update some data
	// checke other checkboxs
	//check lanetype
	if(bModefyLane){
		int checkid = IDC_LAN_TYPE_0;
		checkSum = 0;
		for(i=0;i<MAX_LANE_TYPE;i++){
			CButton *bt = (CButton*)m_groupBoxLaneType->GetDlgItem(checkid+i);
			int bCheck = bt->GetCheck();
			tempLane.LaneType[i] = bCheck;
			if(bCheck==1) checkSum ++;
		}
		if(checkSum==0){
			GetDlgItem(IDC_BT_LANE_ADD)->EnableWindow(true);
			GetDlgItem(IDC_BT_LANE_CANCEL)->EnableWindow(false);
			alert("至少选择一个车道类型,返回重新添加!");
			OnBnClickedBtLaneCancel();
			return false;
		}
		tempLane.LaneTypeNum = checkSum;
		//check event
		checkid = IDC_EVENTTYPE_0;
		checkSum = 0;
		for(i=0;i<MAX_EVENT_TYPE;i++){
			CButton *bt = (CButton*)m_groupBoxEventType->GetDlgItem(checkid+i);
			int bCheck = bt->GetCheck();
			tempLane.EventType[i] = bCheck;
			if(bCheck==1) checkSum ++;
		}
		if(checkSum==0){
			GetDlgItem(IDC_BT_LANE_ADD)->EnableWindow(true);
			GetDlgItem(IDC_BT_LANE_CANCEL)->EnableWindow(false);
			alert("至少选择一个事件类型,返回重新添加!");
			OnBnClickedBtLaneCancel();
			return false;
		}
		tempLane.EventNumber = checkSum;
		//set light id
		tempLane.LightID = m_lightId.GetCurSel()<0? 1:(m_lightId.GetCurSel()+1);
		//copy lane info from templane 2 m_lane[i] whith is not enable

		int index = m_laneId.GetCurSel();
		memcpy(&m_lane[index], &tempLane, sizeof(Lane));
	}

	CString str;
	char lpFileName[256]={0};
	char lineStr[256] ={0} ;
	sprintf(lpFileName,"%s\\LaneConfig.ini",CITSconfigToolKApp::m_appPath);

	//GlobalPara
	int LightGroupNumber  = m_LightGroupNumber.GetCurSel()+1;
	str.Format("%d",LightGroupNumber);
	WritePrivateProfileString("GlobalPara","LightGroupNumber",str, lpFileName);
	str.Format("%d",  m_screenMode.GetCurSel());
	WritePrivateProfileString("GlobalPara","ScenceMode",str, lpFileName);

	//save line 停止线
	for(i=0; i<m_snapLine.Length(); i++)
		WritePrivateProfileString("Line",snapLineVar[i], m_snapLine.formatLine(m_snapLine.getLine(i),lineStr), lpFileName);
	
	//save Lane 车道
	int laneSum = 0;
	CString laneName;
	for(i=0; i<MAX_LANE; i++){
		if(m_lane[i].enable){
			laneSum++;
			laneName.Format("Lane%d",laneSum);
			str.Format("%d",m_lane[i].LaneID);
			WritePrivateProfileString(laneName,"LaneID",str, lpFileName);
			WritePrivateProfileString(laneName,"Line1",m_lane[i].formatLine(m_lane[i].Line1,tempstr), lpFileName);
			WritePrivateProfileString(laneName,"Line2",m_lane[i].formatLine(m_lane[i].Line2,tempstr), lpFileName);
			str.Format("%d",m_lane[i].LaneTypeNum);
			WritePrivateProfileString(laneName,"LaneTypeNum", str, lpFileName);
			WritePrivateProfileString(laneName,"LaneType", m_lane[i].formatLineType(tempstr), lpFileName);
			str.Format("%d",m_lane[i].LightID);
			WritePrivateProfileString(laneName,"LightID", str, lpFileName);
			str.Format("%d",m_lane[i].EventNumber);
			WritePrivateProfileString(laneName,"EventNumber", str, lpFileName);
			WritePrivateProfileString(laneName,"EventType ", m_lane[i].formatEventType(tempstr), lpFileName);
		}
	}
	str.Format("%d",laneSum);
	WritePrivateProfileString("GlobalPara","LaneNumber",str, lpFileName);

	//save vdRegion
	str.Format("%d",vdRegion.length());
	WritePrivateProfileString("GlobalPara", "GlobalPara", str, lpFileName);
	WritePrivateProfileString("VDRegion", "Points", vdRegion.formatPoint(), lpFileName);
	
	m_groupBoxEventType->EnableWindow(false);
	m_groupBoxLaneType->EnableWindow(false);
	GetDlgItem(IDC_LIGHT_ID)->EnableWindow(false);

	//Format imagePoints 2 CPoint
	imageSize.cx = img->GetWidth();
	imageSize.cy = img->GetHeight();
	m_imageFrame.GetWindowRect(&rectRect);
	rectSize.cx = rectRect.Width();
	rectSize.cy = rectRect.Height();
	for(i=0;i<MAX_LANE;i++){
		if(m_lane[i].enable)
			m_lane[i].FormatCPoint(rectSize, imageSize);
	}
	tempLane.FormatCPoint(rectSize, imageSize);
	vdRegion.FormatCPoint(rectSize, imageSize);
	m_snapLine.FormatCPoint(rectSize, imageSize);

	return true;
}
int	CConfigDlg::readConfig()
{
	char lpFileName[256]={0};
	char retString[256]={0};
	Line tLine;
	int i,k;
	sprintf(lpFileName,"%s\\LaneConfig.ini",CITSconfigToolKApp::m_appPath);

	//read Lines
	for(i=0; i<m_snapLine.Length(); i++)
	{
		retNum = GetPrivateProfileString("Line",snapLineVar[i],"{(0,0),(0,0)}", retString, 256, lpFileName);
		sscanf(retString, "{(%d,%d),(%d,%d)}", &tLine.startPoint.x, &tLine.startPoint.y, 
				&tLine.endPoint.x, &tLine.endPoint.y);
		m_snapLine.setLine(i, tLine);
	}

	//get LightGroupNumber
	retNum = GetPrivateProfileString("GlobalPara","LightGroupNumber","0", retString, 256, lpFileName);
	int LightGroupNumber = atoi(retString);
	m_LightGroupNumber.SetCurSel(LightGroupNumber-1);
	OnCbnSelchangeLightNum();

	//get ScenceMode 场景模式
	retNum = GetPrivateProfileString("GlobalPara","ScenceMode","0", retString, 256, lpFileName);
	int ScenceMode = atoi(retString);
	m_screenMode.SetCurSel(ScenceMode);

	//get Lane sum
	retNum = GetPrivateProfileString("GlobalPara","LaneNumber","0", retString, 256, lpFileName);
	int LaneNumber = atoi(retString);

	//read vdRegion Point Sum;
	retNum = GetPrivateProfileString("GlobalPara","GlobalPara","0", retString, 256, lpFileName);
	int GlobalPara = atoi(retString);
	//read vdRegion points 
	retNum = GetPrivateProfileString("VDRegion","Points","0", retString, 256, lpFileName);
	retString[strlen(retString)-1] = '\0';
	retString[0] = ' ';
	char **dest = new char*[GlobalPara];
	charRplace(retString, "),", ")#");
	charRplace(retString, "(", "");
	int retlen = splitchar(retString, dest,GlobalPara, "#");
	int *value = new int[GlobalPara];
	memset(value, 0 , GlobalPara);
	//int x,y;
	for(k=0; k<GlobalPara; k++){
		sscanf(dest[k], "%d,%d", &vdRegion.vdRegionElem[k].point.x, &vdRegion.vdRegionElem[k].point.y );
	//	sscanf(dest[k], "%d,%d)", &x, &y );		
		vdRegion.vdRegionElem[k].enable = true;
	}
	//read  Lane config
	CString LandName ="";
	char	format[256] = {0};
	m_laneId.ResetContent();
	for(i=0; i<MAX_LANE; i++){
		m_lane[i].enable = false;
	}
	for(i=0; i<LaneNumber; i++){

		tempcstr.Format("%d",i+1);
		m_laneId.AddString(tempcstr);

		memset(&m_lane[i], 0, sizeof(Lane));
		LandName.Format("Lane%d",i+1);
		retNum = GetPrivateProfileString(LandName,"LaneID","0", retString, 256, lpFileName);
		m_lane[i].LaneID = atoi(retString);
		retNum = GetPrivateProfileString(LandName,"Line1","{(0,0),(0,0)}", retString, 256, lpFileName);
		sscanf(retString, "{(%d,%d),(%d,%d)}",&m_lane[i].Line1.startPoint.x,  &m_lane[i].Line1.startPoint.y, &m_lane[i].Line1.endPoint.x, &m_lane[i].Line1.endPoint.y);
		retNum = GetPrivateProfileString(LandName,"Line2","{(0,0),(0,0)}", retString, 256, lpFileName);
		sscanf(retString, "{(%d,%d),(%d,%d)}",&m_lane[i].Line2.startPoint.x,  &m_lane[i].Line2.startPoint.y, &m_lane[i].Line2.endPoint.x, &m_lane[i].Line2.endPoint.y);

		//get LaneTypeNum
		retNum = GetPrivateProfileString(LandName,"LaneTypeNum","0", retString, 256, lpFileName);
		m_lane[i].LaneTypeNum = atoi(retString);
		
		//get LaneType
		tempstr[0] = '{';
		for(k=0;k<m_lane[i].LaneTypeNum;k++){
			strcat(tempstr,"0,");
		}
		tempstr[strlen(tempstr)-1]='}';
		tempstr[strlen(tempstr)]='\0';
		retNum = GetPrivateProfileString(LandName,"LaneType",tempstr, retString, 256, lpFileName);
		retString[strlen(retString)-1] = '\0';
		retString[0] = ' ';
		char **dest = new char*[m_lane[i].LaneTypeNum];
		int retlen = splitchar(retString, dest, m_lane[i].LaneTypeNum, ",");
		int *value = new int[m_lane[i].LaneTypeNum];
		memset(value, 0 , m_lane[i].LaneTypeNum);
		for(k=0;k<m_lane[i].LaneTypeNum;k++){
			sscanf(dest[k], "%d", &value[k]);
			m_lane[i].LaneType[value[k]] = 1;
		}
		//get LightID
		retNum = GetPrivateProfileString(LandName,"LightID","0", retString, 256, lpFileName);
		m_lane[i].LightID = atoi(retString);

		//get EventNumber
		retNum = GetPrivateProfileString(LandName,"EventNumber","0", retString, 256, lpFileName);
		m_lane[i].EventNumber = atoi(retString);

		//get EventType
		tempstr[0] = '{';
		for(k=0;k<m_lane[i].LaneTypeNum;k++){
			strcat(tempstr,"0,");
		}
		tempstr[strlen(tempstr)-1]='}';
		tempstr[strlen(tempstr)]='\0';
		retNum = GetPrivateProfileString(LandName,"EventType",tempstr, retString, 256, lpFileName);
		retString[strlen(retString)-1] = '\0';
		retString[0] = ' ';
		char **dest2 = new char*[m_lane[i].EventNumber];
		int retlen2 = splitchar(retString, dest2, m_lane[i].EventNumber, ",");
		int *value2 = new int[m_lane[i].EventNumber];
		memset(value, 0 , m_lane[i].EventNumber);
		for(k=0;k<m_lane[i].EventNumber;k++){
			sscanf(dest2[k], "%d", &value2[k]);
			m_lane[i].EventType[value2[k]] = 1;
		}
		//set this lane Enable
		m_lane[i].enable = true;
		delete []dest;
		delete value;
	}

	//Format imagePoints 2 CPoint
	CRect	rectRect;
	SIZE	rectSize, imageSize;
	imageSize.cx = img->GetWidth();
	imageSize.cy = img->GetHeight();
	m_imageFrame.GetWindowRect(&rectRect);
	rectSize.cx = rectRect.Width();
	rectSize.cy = rectRect.Height();
	for(i=0;i<MAX_LANE;i++){
		if(m_lane[i].enable)
			m_lane[i].FormatCPoint(rectSize, imageSize);
	}
	vdRegion.FormatCPoint(rectSize, imageSize);
	m_snapLine.FormatCPoint(rectSize, imageSize);

	return 0;
}
//设置停止线
void CConfigDlg::OnBnClickedBtSetLine()
{
	if(bSetSnapLines)
		return;
	bSetCaseRect = false;
	bSetSnapLines = true;
	bSetLaneLines = false;
	memset(&tempLine,0, sizeof(Line));

	LaneVisible(false);
	LineVisible(true);
	VdRegionVisible(false);

	setImage(bgPicPath);
//	Invalidate();
}


void CConfigDlg::OnCbnSelchangeLightNum()
{
	/*
	CString str;
	int i;
	m_lightId.ResetContent();
	for(i=0; i<m_LightGroupNumber.GetCurSel()+1; i++){
		str.Format("%d",i+1);
		m_lightId.AddString(str);
	}
	if(m_LightGroupNumber.GetCurSel()<0)
		m_lightId.AddString("1");
	m_lightId.SetCurSel(0);
	*/
}

//设置车道属性
void CConfigDlg::OnBnClickedBtSetLaneProp()
{
	if(bSetLaneLines)
		return ;
	bSetCaseRect = false;
	bSetSnapLines = false;
	bSetLaneLines = true;

	LaneVisible(true);
	LineVisible(false);
	VdRegionVisible(false);

	setImage(bgPicPath);
//	Invalidate();
}


void CConfigDlg::OnBnClickedBtLaneAdd()
{
	//添加车道
	bModefyLane = false;
	bStartDrawLaneLine = true;
	memset(&tempLane,0, sizeof(Lane));
	pointPtr = 0;
	m_dc = m_imageFrame.GetDC();

	m_groupBoxEventType->EnableWindow(true);
	m_groupBoxLaneType->EnableWindow(true);
	GetDlgItem(IDC_LIGHT_ID)->EnableWindow(true);
	GetDlgItem(IDC_BT_LANE_ADD)->EnableWindow(false);
	GetDlgItem(IDC_BT_LANE_CANCEL)->EnableWindow(true);
}


void CConfigDlg::OnBnClickedBtLaneModefy()
{
	bModefyLane = true;
	bStartDrawLaneLine = true;
	memset(&tempLane,0, sizeof(Lane));
	pointPtr = 0;
	m_dc = m_imageFrame.GetDC();
	int index = m_laneId.GetCurSel();
	memcpy(&tempLane, &m_lane[index],  sizeof(Lane));

	m_groupBoxEventType->EnableWindow(true);
	m_groupBoxLaneType->EnableWindow(true);
	GetDlgItem(IDC_LIGHT_ID)->EnableWindow(true);
}


void CConfigDlg::OnBnClickedBtLaneDelete()
{
	int index = m_laneId.GetCurSel();
	if(index<0){
		alert("请先选择车道ID");
		return;
	}
	CString selidstr;
	m_laneId.GetLBText(index, selidstr);
	int selid = atoi(selidstr);
	memset(&m_lane[selid-1], 0, sizeof(Lane));
	m_lane[selid-1].enable = false;
//	m_laneId.DeleteString(index);
	saveConfig();
	readConfig();//
	OnPaint();
	UpdateData(false);
//	Invalidate();
}


void CConfigDlg::OnBnClickedBtLaneCancel()
{
	bModefyLane = false;
	bStartDrawLaneLine = false;
	m_groupBoxEventType->EnableWindow(false);
	m_groupBoxLaneType->EnableWindow(false);
	GetDlgItem(IDC_LIGHT_ID)->EnableWindow(false);
	GetDlgItem(IDC_BT_LANE_ADD)->EnableWindow(true);
	GetDlgItem(IDC_BT_LANE_CANCEL)->EnableWindow(false);

	setImage(bgPicPath);
	OnPaint();
	//	Invalidate();
}

//抓拍线类型 select changed
void CConfigDlg::OnCbnSelchangeSnapLines()
{
	UpdateData(true);
	CDC *dc = m_dc;
	CBrush brushR;
	brushR.CreateSolidBrush(PointColor);
	int index = m_snapLines.GetCurSel();
	CRect r;
	m_imageFrame.GetWindowRect(&r);
	ScreenToClient(&r);
	setImage(bgPicPath);
	for(int i=0; i<m_snapLine.Length(); i++)
	{
		CPen penR;
		if(index==i)
			penR.CreatePen(PS_SOLID, penWidth, selectedColor);
		else
			penR.CreatePen(PS_SOLID, penWidth, LineColor);
		dc->SelectObject(&penR);

		Line line = m_snapLine.getLine(i);
		CPoint t = line.startPoint - line.endPoint;
		if(abs(t.x)==0 && abs(t.y)==0 )
			continue;
		CPoint pt1(CPoint(line.startPoint));
		CPoint pt2(CPoint(line.endPoint));
		dc->MoveTo(pt1);
		dc->LineTo(pt2);
		if((index==i)){
			int dt=radius;
			dc->Ellipse(pt1.x-dt, pt1.y-dt,  pt1.x+dt, pt1.y+dt);
			dc->Ellipse(pt2.x-dt, pt2.y-dt,  pt2.x+dt, pt2.y+dt);
		}
	}
}

//车道 select changed
void CConfigDlg::OnCbnSelchangeLaneId()
{
	int k;
	int index = m_laneId.GetCurSel();
	int lineIndex = m_lane_line.GetCurSel();
	if(index < 0)
		return;
	int checkid = IDC_LAN_TYPE_0;
	for(k=0;k<MAX_LANE_TYPE;k++){
		CButton *bt = (CButton*)m_groupBoxLaneType->GetDlgItem(checkid+k);
		bt->SetCheck(m_lane[index].LaneType[k]);
	}
	char name[256]={0};
	checkid = IDC_EVENTTYPE_0;
	for(k=0;k<MAX_EVENT_TYPE;k++){
		CButton *bt = (CButton*)m_groupBoxEventType->GetDlgItem(checkid+k);
		bt->GetWindowText(name,256);
		bt->SetCheck(m_lane[index].EventType[k]);
	}
	//light ID
	m_lightId.SetCurSel(m_lane[index].LightID>0? m_lane[index].LightID-1:1);
	//re draw this lane with other color
	CDC *dc = m_dc;
	CBrush brushR;
	brushR.CreateSolidBrush(PointColor);
	
	CRect r;
	m_imageFrame.GetWindowRect(&r);
	ScreenToClient(&r);
	setImage(bgPicPath);
	dc->SetMapMode(MM_TEXT);
	
	for(int i=0; i<MAX_LANE; i++){
		if(m_lane[i].enable){
			CPen penR;
			if(index==i)
				penR.CreatePen(PS_SOLID, penWidth, selectedColor);
			else
				penR.CreatePen(PS_SOLID, penWidth, LineColor);
			dc->SelectObject(&penR);
			
			CPoint pt11(m_lane[i].Line1.startPoint);
			CPoint pt12(m_lane[i].Line1.endPoint);
			CPoint pt21(m_lane[i].Line2.startPoint);
			CPoint pt22(m_lane[i].Line2.endPoint);

			dc->MoveTo(pt11);
			dc->LineTo(pt12);
			dc->MoveTo(pt21);
			dc->LineTo(pt22);

			int dt=radius;
			if(index==i){
				if(lineIndex==0){
					dc->Ellipse(pt11.x - dt, pt11.y-dt,  pt11.x+dt, pt11.y+dt);
					dc->Ellipse(pt12.x - dt, pt12.y-dt,  pt12.x+dt, pt12.y+dt);
				}else if(lineIndex==1){
					dc->Ellipse(pt21.x - dt, pt21.y-dt, pt21.x+dt, pt21.y+dt);
					dc->Ellipse(pt22.x - dt, pt22.y-dt, pt22.x+dt, pt22.y+dt);
				}
			}	
		}
	}
	UpdateData(false);
}

// 设置检测区域(感兴趣区域)
void CConfigDlg::OnBnClickedBtSetCaseRect()
{
	if(bSetCaseRect)
		return;
	bSetCaseRect = true;
	bSetSnapLines = false;
	bSetLaneLines = false;

	bModefyLane = false;
	bStartDrawLaneLine = false;

	LaneVisible(false);
	LineVisible(false);
	VdRegionVisible(true);
	
	setImage(bgPicPath);
//	Invalidate();
}

void CConfigDlg::OnBnClickedVdRegionEdit()
{
	UpdateData(true);
	bEditCaseRect = bEditRectCon.GetCheck()==1? true:false;
	if(bEditCaseRect){
		pointPtr = 0;
		vdRegion.reset();
		setImage(bgPicPath);
	}
}
void CConfigDlg::VdRegionVisible(bool bShow){
	GetDlgItem(IDC_VD_REGION_EDIT)->ShowWindow(bShow);
}
void CConfigDlg::LineVisible(bool bShow){
	GetDlgItem(IDC_LABEL_LINETYPE)->ShowWindow(bShow);
	GetDlgItem(IDC_SNAP_LINES)->ShowWindow(bShow);
	GetDlgItem(IDC_BT_ADD_SNAP_LINE)->ShowWindow(bShow);
	GetDlgItem(IDC_BT_SNAP_CANCEL)->ShowWindow(bShow);
}
void CConfigDlg::LaneVisible(bool bShow){
	GetDlgItem(IDC_LABEL_LANID)->ShowWindow(bShow);
	GetDlgItem(IDC_LANE_ID)->ShowWindow(bShow);
	GetDlgItem(IDC_LABEL_LIGHTID)->ShowWindow(bShow);
	GetDlgItem(IDC_LIGHT_ID)->ShowWindow(bShow);
	GetDlgItem(IDC_BT_LANE_MODEFY)->ShowWindow(bShow);
	GetDlgItem(IDC_BT_LANE_ADD)->ShowWindow(bShow);
	GetDlgItem(IDC_BT_LANE_DELETE)->ShowWindow(bShow);
	GetDlgItem(IDC_BT_LANE_CANCEL)->ShowWindow(bShow);
	GetDlgItem(IDC_GROUP_LANE_OPERA)->ShowWindow(bShow);
	m_groupBoxEventType->ShowWindow(bShow);
	m_groupBoxLaneType->ShowWindow(bShow);

}



void CConfigDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	lButtonDown = false;
	selectedPoint = -1;
	selectedCasePointIndex = -1;
	m_status.SetWindowText("OnLButtonUp");
	UpdateData(false);

	CDialogEx::OnLButtonUp(nFlags, point);
}
