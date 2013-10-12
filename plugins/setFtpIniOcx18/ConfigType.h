#ifndef CONFIG_TYPE_H
#define CONFIG_TYPE_H

#define  CAL_POINT_NUM     4  //标定点数目
#define  MAX_LIGHT_NUM     4  //信号灯最大数目
#define  MAX_NUM           4   //车道最大数目 检测区域最大数目
#define  MAX_OPERATE_NUM   20  //操作的最大数目


#define  CIRCULAR          0  //圆形
#define  ARROW             1  //箭头形

#define  LANE_REGION       1  //车道区域
#define  PARKING_REGION    2  //违章停车区域
#define  DET_REGION        3  //检测区域
#define  YELLOW_REGION     4  //黄线区域

#define  HEAD              1     //车头模式
#define  TAI               2     //车尾模式
#define  HEAD_TAIL         3     //车头车尾模式

#define  CH                1    //闯红灯
#define  NX                2    //逆行
#define  KK                3    //卡口
#define  ST                4    //收费站停车场
#define  TC                5    //违章停车
#define  BD                6    //违规变道
#define  YX                7    //压黄线
#define  CL                8    //车流量统计
#define  PD                9    //排队长度


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
	int iLightID;    //此项是给车道单独用的，用于指示对应的信号灯的ID
	int iID;
}Tel_Region;

/****************车辆标定参数结构体****************/

typedef struct
{
	int iMaxVehicleWidth;           //单位cm
	int iMinVehicleWidth;           //单位cm
	int iCalibrationHorizontalDis;  //单位cm
	int iCalibrationVerticalDis;    //单位cm

	Tel_Point CalibrationPoint[CAL_POINT_NUM]; //标记点坐标
	Tel_Point GenerationPoint[CAL_POINT_NUM];  //生成点坐标
}Tel_VehicleCalibration;
/****************车辆标定参数结构体****************/

/****************信号灯结构体****************/

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
/****************信号灯结构体****************/



/****************车道配置结构体****************/
typedef struct
{
	int iNum;
	Tel_Region region[MAX_NUM];// MAX_NUM = 4
}Tel_ConfigRegion;

typedef struct
{
	Tel_ConfigRegion lane;             //车道信息
	Tel_ConfigRegion detRegion;        //检测区域，车辆检测区域，或者针对收费站等的车牌识别区域
	Tel_ConfigRegion parkingRegion;    //违章停车检测区域
	Tel_ConfigRegion yellowLineRegion; //黄线区域

	Tel_Line stopLine;        //停止线
	Tel_Line triggerLine;     //抓拍线，在这条线上能识别车牌
	Tel_Line detVehicleLine;  //车辆检测跟踪线，给车辆检测算法预留的项
}Tel_LaneConfig;
/****************车道配置结构体****************/



/****************操作结构体****************/
typedef struct
{
	int iRegionType; //区域类型
	int iID;         //区域ID
	int iOperateType;//操作类型
	int iDetMode;    //检测模式
}Tel_SingleOperate;


typedef struct
{
	int iNum;
	Tel_SingleOperate operate[MAX_OPERATE_NUM];
}Tel_Operate;

/****************操作结构体****************/

#endif