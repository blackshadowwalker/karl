#pragma once

#include "maindlg.h"
#include "pluginbase.h"
#include "Util.h"
#include "Sq.h"

#define _WIN32_WINNT 0x0500

class KPlugin : public nsPluginInstanceBase
{
public:
	KPlugin(NPP pNPInstance);
	~KPlugin(void);
	Image *image;

private:
	NPP m_pNPInstance;
	NPBool m_bInitialized;
	NPWindow * m_Window;
	NPStream * m_pNPStream;
	NPObject *m_pScriptableObject;

public:
	bool bInitialized;
	bool playStarted;
	
#ifdef XP_WIN
	HWND m_hWnd; 
#endif

	HANDLE m_hPlay;

	char m_String[128];

	Util util;

	int16_t handleEvent(void* event);

	void showVersion();
	void clear();
	void getVersion(char* *aVersion);

	NPObject *GetScriptableObject();

	NPBool init(NPWindow* pNPWindow);
	void shut()  {  m_bInitialized = FALSE;  }
	NPBool isInitialized()  {  return m_bInitialized;  }
	static CMainDlg *m_dlg;
};

