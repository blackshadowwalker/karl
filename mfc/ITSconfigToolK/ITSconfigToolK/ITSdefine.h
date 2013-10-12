#ifndef _ITSDEFINE_H_
#define _ITSDEFINE_H_

#pragma once


CPoint CPoint2ImagePoint(CPoint &ptSrc, SIZE rectSize, SIZE imageSize, bool bCover=false);
CPoint ImagePoint2CPoint(CPoint &ptSrc, SIZE rectSize, SIZE imageSize, bool bCover=false);


#define MAX_LANE		10 //最多车道数码
#define MAX_LANE_TYPE	8 //车道类型最多数目
#define	MAX_EVENT_TYPE	11 //检测事件最多数目
#define MAX_VDREGION	20//车辆检测区域点数目：取值范围为5~20



struct GlobalPara{
	int		LightGroupNumber;//信号灯组数：最大值为4 ，取值为1~4。
	int		LaneNumber;//车道数目：最大值为4，但一般500W，300W，200W相机均只能监控3个车道，取值范围为1~4。
	int		ScenceMode;//场景模式：0 自动判别，1 白天模式，2 夜晚模式，3 黄昏夜晚模式
	int		VDPointNum;//车辆检测区域点数目：取值范围为5~20
	GlobalPara()
	{
		LightGroupNumber = 0;
		LaneNumber = 0;
		ScenceMode = 0;
		VDPointNum = 0;
	}
};
typedef struct GlobalPara GlobalPara;



struct Line{
	CPoint	startPoint;
	CPoint	endPoint;
	Line operator+(const Line &p){
		Line l;
		l.startPoint = startPoint + p.startPoint;
		l.endPoint = endPoint + p.endPoint;
		return l;
	}
	Line operator-(const Line &p){
		Line l;
		l.startPoint = startPoint - p.startPoint;
		l.endPoint = endPoint - p.endPoint;
		return l;
	}
};
typedef struct Line CLine;

struct SnapLine{
	Line	ZhiStopLine;//直行停止线
	Line	LeftStopLine;//左转停止线
	Line	RightStopLine;//右转停止线
	Line	ZhiTriggerLine;//直行闯红灯抓拍线
	Line	LeftRightTriggerLine;//左右转直行抓拍线
	SnapLine()
	{
		;
	}
	void FormatImagePoint(SIZE rectSize, SIZE imageSize){

		CPoint2ImagePoint(ZhiStopLine.startPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(ZhiStopLine.endPoint, rectSize, imageSize, true);

		CPoint2ImagePoint(LeftStopLine.startPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(LeftStopLine.endPoint, rectSize, imageSize, true);

		CPoint2ImagePoint(RightStopLine.startPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(RightStopLine.endPoint, rectSize, imageSize, true);

		CPoint2ImagePoint(ZhiTriggerLine.startPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(ZhiTriggerLine.endPoint, rectSize, imageSize, true);

		CPoint2ImagePoint(LeftRightTriggerLine.startPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(LeftRightTriggerLine.endPoint, rectSize, imageSize, true);
	}
	void FormatCPoint(SIZE rectSize, SIZE imageSize){
		
		ImagePoint2CPoint(ZhiStopLine.startPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(ZhiStopLine.endPoint, rectSize, imageSize, true);

		ImagePoint2CPoint(LeftStopLine.startPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(LeftStopLine.endPoint, rectSize, imageSize, true);

		ImagePoint2CPoint(RightStopLine.startPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(RightStopLine.endPoint, rectSize, imageSize, true);

		ImagePoint2CPoint(ZhiTriggerLine.startPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(ZhiTriggerLine.endPoint, rectSize, imageSize, true);

		ImagePoint2CPoint(LeftRightTriggerLine.startPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(LeftRightTriggerLine.endPoint, rectSize, imageSize, true);

	}
	int		Length(){ return 5;};
	char*	formatLine(CLine line, char* lineStr=0)
	{
		if(lineStr==NULL)
		//	return NULL;
			lineStr = new char[256];
		//{(x1,y1),(x2,y2)}
		sprintf(lineStr,"{(%d,%d),(%d,%d)}", line.startPoint.x, line.startPoint.y,\
						line.endPoint.x, line.endPoint.y);
		return lineStr;
	}
	CLine	getLine(int i)
	{
		switch(i){
		case 0:
			return ZhiStopLine;
			break;
		case 1:
			return LeftStopLine;
			break;
		case 2:
			return RightStopLine;
			break;
		case 3:
			return ZhiTriggerLine;
			break;
		case 4:
			return LeftRightTriggerLine;
			break;
		default:
			 ;
		}
	}
	void setLine(int i, CLine tempLine)
	{
		switch(i)
		{
		case 0:
			ZhiStopLine = tempLine;
			break;
		case 1:
			LeftStopLine = tempLine;
			break;
		case 2:
			RightStopLine = tempLine;
			break;
		case 3:
			ZhiTriggerLine = tempLine;
			break;
		case 4:
			LeftRightTriggerLine = tempLine;
			break;
		}
	}

};
typedef struct SnapLine SnapLine;//各种抓拍/停止线

struct Lane{
	bool	enable;//是否启用，目前用来标识lane[10]每个是否已用
	int		LaneID;//车道ID
	CLine	Line1;//车道线左线
	CLine	Line2;//车道线右线
	int		LaneTypeNum;//车道类型数目:取值1~7
	int		LaneType[MAX_LANE_TYPE];//车道类型组合 0-6: \
						0直行车道，1左转车道，2右转车道，3掉头车道，\
						4为公交专用车道，5为非机动车道，6为禁停车道
	int		LightID;//信号灯ID
	int		EventNumber;//检测事件数目:取值为1~11
	int		EventType[MAX_EVENT_TYPE];//该车道所做的检测事件类型列表：\
						0闯红灯，1逆行，2卡口，3违规变道，4违章压线，5尾号限行，\
						6违章停车，7占用公交车道，8占非机动车道，9大车禁行，10车流量统计
	Lane(){
		enable = false;
	}
	void FormatImagePoint(SIZE rectSize, SIZE imageSize){
		CPoint2ImagePoint(Line1.startPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(Line1.endPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(Line2.startPoint, rectSize, imageSize, true);
		CPoint2ImagePoint(Line2.endPoint, rectSize, imageSize, true);
	}
	void FormatCPoint(SIZE rectSize, SIZE imageSize){
		ImagePoint2CPoint(Line1.startPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(Line1.endPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(Line2.startPoint, rectSize, imageSize, true);
		ImagePoint2CPoint(Line2.endPoint, rectSize, imageSize, true);
	}
	char*	formatLine(CLine line, char* lineStr=0)
	{
		if(lineStr==NULL)
		//	return NULL;
			lineStr = new char[256];
		//{(x1,y1),(x2,y2)}
		sprintf(lineStr,"{(%d,%d),(%d,%d)}", line.startPoint.x, line.startPoint.y,\
						line.endPoint.x, line.endPoint.y);
		return lineStr;
	}
	char*	formatLineType(char* lineStr=0){
		if(lineStr==NULL)
			lineStr = new char[256];
		char temp[256]={0};
		sprintf(lineStr,"{");
		int i=0;
		for(i=0;i<MAX_LANE_TYPE;i++)
			if(LaneType[i]==1){
				sprintf(temp,"%d,",i);
				strcat(lineStr,temp);
			}
		lineStr[strlen(lineStr)-1]='\0';
		strcat(lineStr,"}");
		return lineStr;
	}
	char*	formatEventType(char* lineStr=0){
		if(lineStr==NULL)
			lineStr = new char[256];
		char temp[256]={0};
		sprintf(lineStr,"{");
		int i=0;
		for(i=0;i<MAX_EVENT_TYPE;i++)
			if(EventType[i]==1){
				sprintf(temp,"%d,",i);
				strcat(lineStr,temp);
			}
		lineStr[strlen(lineStr)-1]='\0';
		strcat(lineStr,"}");
		return lineStr;	
	}
};
typedef struct Lane Lane;

//检测区域 基元
struct VdRegionElem{
	CPoint	point;
	bool	enable;
	VdRegionElem()
	{
		enable = false;
		point.x = point.y = 0;
	}
};
typedef struct VdRegionElem VdRegionElem;

//检测区域
struct VdRegion{
	VdRegionElem	vdRegionElem[MAX_VDREGION];
	void FormatImagePoint(SIZE rectSize, SIZE imageSize){
		int i=0;
		while(i<MAX_VDREGION){
			if(vdRegionElem[i].enable)
				CPoint2ImagePoint(vdRegionElem[i].point, rectSize, imageSize, true);
			i++;
		}
	}
	void FormatCPoint(SIZE rectSize, SIZE imageSize){
		int i=0;
		while(i<MAX_VDREGION){
			if(vdRegionElem[i].enable)
				ImagePoint2CPoint(vdRegionElem[i].point, rectSize, imageSize, true);
			i++;
		}
	}
	int length(){
		int len=0;
		for(int i=0;i<MAX_VDREGION;i++){
			len += vdRegionElem[i].enable==true? 1:0;
		}
		return len;
	}
	bool add(CPoint p){
		if(length() >= MAX_VDREGION)
			return false;
		int i = 0;
		while(vdRegionElem[i].enable && i++<MAX_VDREGION)
			;
		vdRegionElem[i].point = p;
		vdRegionElem[i].enable = true;
	}
	void reset(){
		int i=0;
		while(i<MAX_VDREGION)
			vdRegionElem[i++].enable  = false;
	}
	char *formatPoint(char* lineStr=0){
		if(lineStr==NULL)
			lineStr = new char[256];
		char temp[256]={0};
		sprintf(lineStr,"{");
		int i=0;
		for(i=0;i<MAX_VDREGION;i++)
			if(vdRegionElem[i].enable==true){
				sprintf(temp,"(%d,%d),",vdRegionElem[i].point.x, vdRegionElem[i].point.y);
				strcat(lineStr,temp);
			}
		lineStr[strlen(lineStr)-1]='\0';
		strcat(lineStr,"}");
		return lineStr;	
	}
};
typedef struct VdRegion VdRegion;


#endif