//public.h


#pragma once
/**************** defines ***************************/

#define REG_UNKNOW				0 
#define REG_REGISTER			1 //已注册
#define REG_NOT_REGISTER		-1 //没注册
#define REG_INIT				-2 //首次使用
#define REG_SYSTEM_ERROR		-3 //系统故障
#define REG_SYS_TIME_CHANGED	-4 //系统时间被改变
#define REG_SYS_REG_CHANGED		-5 //注册表数据被改变


/*************************************************/


char		*GetWindowPath();//获得系统盘符路径
TCHAR*		g_GetIniPath(void);
CString		ConvertString(CString strText);
//Set static text in dialogue box (English->current language)
void		g_SetWndStaticText(CWnd * pWnd);
TCHAR*		g_GetSetPath(void);

void		EventLog(char* info);//历史记录文件
void		Split(const CString& src, CString delimit, CStringList* pOutList, int num=0, CString nullSubst="");

void __cdecl kprintf(const char *format, ...);



//判断文件/文件夹是否存在
//判断文件：	FindFirstFileExists(lpPath, FALSE);  
//判断文件夹：	FindFirstFileExists(lpPath, FILE_ATTRIBUTE_DIRECTORY);  
BOOL		FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter);
bool		KCreateFolder(CString folder);
bool		RemoveDir(const char* szFileDir);
CString		SelectFolder(CWnd *hWnd);//选择文件夹 对话框
void		ListAllFiles(char *Path, CListBox *pList);

//注册表相关操作
bool		OpenReg(HKEY &hKEY, char *data_Set);
BYTE*		QueryReg(char *key, DWORD dataLen, HKEY hKEY);
long		CreateReg(HKEY hKEY,const char *subkey);
bool		WriteReg(HKEY &hKEY, char *data_Set);
bool		SetReg(char *key, BYTE* value, DWORD dataLen, HKEY hKEY);
//\**************************************************************/

//******** date time classes **************
char *getNowTime();
char *formatTime(time_t* t);
char *formatTMTime(struct tm *time);
void Encryption(BYTE *data, long lenData,  BYTE *key, long lenKey);
void Decryption(BYTE *data, long lenData,  BYTE *key, long lenKey);

