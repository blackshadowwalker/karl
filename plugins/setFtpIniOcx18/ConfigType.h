#ifndef CONFIG_TYPE_H
#define CONFIG_TYPE_H

#define  CAL_POINT_NUM     4  //�궨����Ŀ
#define  MAX_LIGHT_NUM     4  //�źŵ������Ŀ
#define  MAX_NUM           4   //���������Ŀ ������������Ŀ
#define  MAX_OPERATE_NUM   20  //�����������Ŀ


#define  CIRCULAR          0  //Բ��
#define  ARROW             1  //��ͷ��

#define  LANE_REGION       1  //��������
#define  PARKING_REGION    2  //Υ��ͣ������
#define  DET_REGION        3  //�������
#define  YELLOW_REGION     4  //��������

#define  HEAD              1     //��ͷģʽ
#define  TAI               2     //��βģʽ
#define  HEAD_TAIL         3     //��ͷ��βģʽ

#define  CH                1    //�����
#define  NX                2    //����
#define  KK                3    //����
#define  ST                4    //�շ�վͣ����
#define  TC                5    //Υ��ͣ��
#define  BD                6    //Υ����
#define  YX                7    //ѹ����
#define  CL                8    //������ͳ��
#define  PD                9    //�Ŷӳ���


typedef struct
{
	int ix;
	int iy;
}Tel_Point;



typedef struct
{
	Tel_Point startPoint;
	Tel_Point endPoint;
}Tel_Line;

typedef struct
{
	Tel_Point LeftTop;
	int iHeight;
	int iWidth;
}Tel_Rect;

typedef struct
{
	Tel_Point LeftTop;
	Tel_Point RightTop;
	Tel_Point LeftBottom;
	Tel_Point RightBottom;
	int iLightID;    //�����Ǹ����������õģ�����ָʾ��Ӧ���źŵƵ�ID
	int iID;
}Tel_Region;

/****************�����궨�����ṹ��****************/

typedef struct
{
	int iMaxVehicleWidth;           //��λcm
	int iMinVehicleWidth;           //��λcm
	int iCalibrationHorizontalDis;  //��λcm
	int iCalibrationVerticalDis;    //��λcm

	Tel_Point CalibrationPoint[CAL_POINT_NUM]; //��ǵ�����
	Tel_Point GenerationPoint[CAL_POINT_NUM];  //���ɵ�����
}Tel_VehicleCalibration;
/****************�����궨�����ṹ��****************/

/****************�źŵƽṹ��****************/

typedef struct
{
	int iID;	
	int iLightShape;
	Tel_Rect SearchRect;
	Tel_Rect TemplateRect;
	Tel_Rect RedRect;
	Tel_Rect GreenRect;
	Tel_Rect YellowRect;

}Tel_SingleLight;

typedef struct
{
	int iNum;

    Tel_SingleLight sLight[MAX_LIGHT_NUM];

}Tel_LightConfig;
/****************�źŵƽṹ��****************/



/****************�������ýṹ��****************/
typedef struct
{
	int iNum;
	Tel_Region region[MAX_NUM];// MAX_NUM = 4
}Tel_ConfigRegion;

typedef struct
{
	Tel_ConfigRegion lane;             //������Ϣ
	Tel_ConfigRegion detRegion;        //������򣬳���������򣬻�������շ�վ�ȵĳ���ʶ������
	Tel_ConfigRegion parkingRegion;    //Υ��ͣ���������
	Tel_ConfigRegion yellowLineRegion; //��������

	Tel_Line stopLine;        //ֹͣ��
	Tel_Line triggerLine;     //ץ���ߣ�������������ʶ����
	Tel_Line detVehicleLine;  //�����������ߣ�����������㷨Ԥ������
}Tel_LaneConfig;
/****************�������ýṹ��****************/



/****************�����ṹ��****************/
typedef struct
{
	int iRegionType; //��������
	int iID;         //����ID
	int iOperateType;//��������
	int iDetMode;    //���ģʽ
}Tel_SingleOperate;


typedef struct
{
	int iNum;
	Tel_SingleOperate operate[MAX_OPERATE_NUM];
}Tel_Operate;

/****************�����ṹ��****************/

#endif