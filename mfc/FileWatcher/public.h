//public.h


#pragma once
/**************** defines ***************************/

#define REG_UNKNOW				0 
#define REG_REGISTER			1 //��ע��
#define REG_NOT_REGISTER		-1 //ûע��
#define REG_INIT				-2 //�״�ʹ��
#define REG_SYSTEM_ERROR		-3 //ϵͳ����
#define REG_SYS_TIME_CHANGED	-4 //ϵͳʱ�䱻�ı�
#define REG_SYS_REG_CHANGED		-5 //ע������ݱ��ı�


/*************************************************/


char		*GetWindowPath();//���ϵͳ�̷�·��
TCHAR*		g_GetIniPath(void);
CString		ConvertString(CString strText);
//Set static text in dialogue box (English->current language)
void		g_SetWndStaticText(CWnd * pWnd);
TCHAR*		g_GetSetPath(void);

void		EventLog(char* info);//��ʷ��¼�ļ�
void		Split(const CString& src, CString delimit, CStringList* pOutList, int num=0, CString nullSubst="");

void __cdecl kprintf(const char *format, ...);



//�ж��ļ�/�ļ����Ƿ����
//�ж��ļ���	FindFirstFileExists(lpPath, FALSE);  
//�ж��ļ��У�	FindFirstFileExists(lpPath, FILE_ATTRIBUTE_DIRECTORY);  
BOOL		FindFirstFileExists(LPCTSTR lpPath, DWORD dwFilter);
bool		KCreateFolder(CString folder);
bool		RemoveDir(const char* szFileDir);
CString		SelectFolder(CWnd *hWnd);//ѡ���ļ��� �Ի���
void		ListAllFiles(char *Path, CListBox *pList);

//ע�����ز���
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

