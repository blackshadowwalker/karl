//public.h

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ConfigType.h"

//void DrawImg2Hdc(IplImage *img, UINT id, CDC *pDC, CRect rect);
/*
void	DrawImgFile2Hdc(CString filename, UINT id, CWnd* cWnd, CRect rect);
void	DrawImg2Hdc(Image *image, UINT id, CWnd* cWnd, CRect rect);
Image*	KLoadImage(CString filename);
*/

static char* config[5] = { "检测区域","违章停车区域","黄线区域","停止线","抓拍线"};//区域名称
static char* num[4] = {"1","2","3","4"};
static char* coperate[9] = {"CH-闯红灯","NX-逆行","KK-卡口","ST-收费站停车场","TC-违章停车",
                     "BD-违规变道","YX-压黄线","CL-车流量统计","PD-排队长度"};//操作类型
static char* cmode[3] = {"车头检测","车尾检测","车头车尾检测"};//检查模式

//交通事件类型，用来设置监控事件段
#define		LEN_EVENT	11
static char *eventID[LEN_EVENT]={"CHD","CLL","KK","NX","PDCD","SFZ","TLSJC","WCP","WGBD","WZTC","YHX"};
static char *eventVal[LEN_EVENT]={"闯红灯","车流量","卡口","逆行","排队长度","收费站、停车场","停留时间过长","无车牌","违规变道","违章停车","压黄线"};

Tel_Point	Point2Telpoint(CPoint pt);
CPoint		Telpoint2Point(Tel_Point pt);

char		*GetWindowPath();//获得系统盘符路径
bool		KCreateFolder(CString folder);// 创建文件夹，可以创建连续多级不存在的目录
bool		RemoveDir(const char* szFileDir);//
//注册表相关操作
static LPCTSTR data_Set = "Software\\Teleframe\\ocxConfig\\";
void		SetRegPath(CString str);
LPCTSTR		GetRegPath();
bool		OpenReg(HKEY &hKEY);
long		CreateReg(HKEY hKEY,const char *subkey);
bool		WriteReg(HKEY &hKEY);
char*		QueryReg(char *key, DWORD dataLen, HKEY hKEY);
bool		SetReg(char *key, char* value, DWORD dataLen, HKEY hKEY);
//\**************************************************************/
void Split(const CString& src, CString delimit, CStringList* pOutList, int num=0, CString nullSubst="");
