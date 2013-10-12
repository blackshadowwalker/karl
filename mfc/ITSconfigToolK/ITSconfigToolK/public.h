
/*
* Date: 2013/8/19 15:22
* Author: Karl
*/
//public.h

#include "ITSdefine.h"

static int	lastErrorCode =0;
static char lastError[256]={0};
char*		getLastError();
int			setLastError(char *info);
int			getLastErrorCode();
int			setLastErrorCode(int code);

char *getThisPath(CWinApp *app,char *path=0);

void alert(char *text);

Image* KLoadImage(CString filename);
void DrawImg2Hdc(Image *image, UINT id, CWnd* cWnd, CRect rect);
/*************************************************/

//判断文件/文件夹是否存在
//判断文件：	FindFirstFileExists(lpPath, FALSE);  
//判断文件夹：	FindFirstFileExists(lpPath, FILE_ATTRIBUTE_DIRECTORY);  
BOOL		FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter);
int			splitchar(char *src,  char**dest, int destlen, char *splitstr=0, int maxlen=0);
void		charRplace(char *src, char *oldRp, char* newRp);
bool		KCreateFolder(CString folder);
bool		RemoveDir(const char* szFileDir);
CString		SelectFolder(CWnd *hWnd);//选择文件夹 对话框

TCHAR* g_GetIniPath(void);
char* ConvertInfo(char* strText);
CString ConvertString(CString strText);
//Set static text in dialogue box (English->current language)
void g_SetWndStaticText(CWnd * pWnd);
TCHAR* g_GetSetPath(void);

void EventLog(char* info);//历史记录文件

//注册表相关操作
bool		OpenReg(HKEY &hKEY, char *data_Set);
BYTE*		QueryReg(char *key, DWORD dataLen, HKEY hKEY);
long		CreateReg(HKEY hKEY,const char *subkey);
bool		WriteReg(HKEY &hKEY, char *data_Set);
bool		SetReg(char *key, BYTE* value, DWORD dataLen, HKEY hKEY);
//\**************************************************************/

//******** date time classes **************
char *formatTime(time_t* t);
char *formatTMTime(struct tm *time);
void Encryption(BYTE *data, long lenData,  BYTE *key, long lenKey);
void Decryption(BYTE *data, long lenData,  BYTE *key, long lenKey);

/**********  math *************/

// 点到直线的距离
double DisPoint2Line( CPoint pt, CLine line );

/**********************************/