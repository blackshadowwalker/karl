#ifndef _ITSDEFINE_H_
#define _ITSDEFINE_H_

#pragma once


CPoint CPoint2ImagePoint(CPoint &ptSrc, SIZE rectSize, SIZE imageSize, bool bCover=false);
CPoint ImagePoint2CPoint(CPoint &ptSrc, SIZE rectSize, SIZE imageSize, bool bCover=false);


#define MAX_LANE		10 //��೵������
#define MAX_LANE_TYPE	8 //�������������Ŀ
#define	MAX_EVENT_TYPE	11 //����¼������Ŀ
#define MAX_VDREGION	20//��������������Ŀ��ȡֵ��ΧΪ5~20



struct GlobalPara{
	int		LightGroupNumber;//�źŵ����������ֵΪ4 ��ȡֵΪ1~4��
	int		LaneNumber;//������Ŀ�����ֵΪ4����һ��500W��300W��200W�����ֻ�ܼ��3��������ȡֵ��ΧΪ1~4��
	int		ScenceMode;//����ģʽ��0 �Զ��б�1 ����ģʽ��2 ҹ��ģʽ��3 �ƻ�ҹ��ģʽ
	int		VDPointNum;//��������������Ŀ��ȡֵ��ΧΪ5~20
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
	Line	ZhiStopLine;//ֱ��ֹͣ��
	Line	LeftStopLine;//��תֹͣ��
	Line	RightStopLine;//��תֹͣ��
	Line	ZhiTriggerLine;//ֱ�д����ץ����
	Line	LeftRightTriggerLine;//����תֱ��ץ����
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
typedef struct SnapLine SnapLine;//����ץ��/ֹͣ��

struct Lane{
	bool	enable;//�Ƿ����ã�Ŀǰ������ʶlane[10]ÿ���Ƿ�����
	int		LaneID;//����ID
	CLine	Line1;//����������
	CLine	Line2;//����������
	int		LaneTypeNum;//����������Ŀ:ȡֵ1~7
	int		LaneType[MAX_LANE_TYPE];//����������� 0-6: \
						0ֱ�г�����1��ת������2��ת������3��ͷ������\
						4Ϊ����ר�ó�����5Ϊ�ǻ���������6Ϊ��ͣ����
	int		LightID;//�źŵ�ID
	int		EventNumber;//����¼���Ŀ:ȡֵΪ1~11
	int		EventType[MAX_EVENT_TYPE];//�ó��������ļ���¼������б�\
						0����ƣ�1���У�2���ڣ�3Υ������4Υ��ѹ�ߣ�5β�����У�\
						6Υ��ͣ����7ռ�ù���������8ռ�ǻ���������9�󳵽��У�10������ͳ��
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

//������� ��Ԫ
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

//�������
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