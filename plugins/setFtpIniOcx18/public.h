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

static char* config[5] = { "�������","Υ��ͣ������","��������","ֹͣ��","ץ����"};//��������
static char* num[4] = {"1","2","3","4"};
static char* coperate[9] = {"CH-�����","NX-����","KK-����","ST-�շ�վͣ����","TC-Υ��ͣ��",
                     "BD-Υ����","YX-ѹ����","CL-������ͳ��","PD-�Ŷӳ���"};//��������
static char* cmode[3] = {"��ͷ���","��β���","��ͷ��β���"};//���ģʽ

//��ͨ�¼����ͣ��������ü���¼���
#define		LEN_EVENT	11
static char *eventID[LEN_EVENT]={"CHD","CLL","KK","NX","PDCD","SFZ","TLSJC","WCP","WGBD","WZTC","YHX"};
static char *eventVal[LEN_EVENT]={"�����","������","����","����","�Ŷӳ���","�շ�վ��ͣ����","ͣ��ʱ�����","�޳���","Υ����","Υ��ͣ��","ѹ����"};

Tel_Point	Point2Telpoint(CPoint pt);
CPoint		Telpoint2Point(Tel_Point pt);

char		*GetWindowPath();//���ϵͳ�̷�·��
bool		KCreateFolder(CString folder);// �����ļ��У����Դ��������༶�����ڵ�Ŀ¼
bool		RemoveDir(const char* szFileDir);//
//ע�����ز���
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
