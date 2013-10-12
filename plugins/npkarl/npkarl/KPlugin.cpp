#include "KPlugin.h"

#include "afxwin.h"


#ifdef XP_WIN
#include <windows.h>
#include <windowsx.h>
#endif

#ifdef XP_MAC
#include <TextEdit.h>
#endif

#ifdef XP_UNIX
#include <string.h>
#endif

#include "npfunctions.h"


#define DECLARE_NPOBJECT_CLASS_WITH_BASE(_class, ctor)                        \
static NPClass s##_class##_NPClass = {                                        \
  NP_CLASS_STRUCT_VERSION_CTOR,                                               \
  ctor,                                                                       \
  ScriptablePluginObjectBase::_Deallocate,                                    \
  ScriptablePluginObjectBase::_Invalidate,                                    \
  ScriptablePluginObjectBase::_HasMethod,                                     \
  ScriptablePluginObjectBase::_Invoke,                                        \
  ScriptablePluginObjectBase::_InvokeDefault,                                 \
  ScriptablePluginObjectBase::_HasProperty,                                   \
  ScriptablePluginObjectBase::_GetProperty,                                   \
  ScriptablePluginObjectBase::_SetProperty,                                   \
  ScriptablePluginObjectBase::_RemoveProperty,                                \
  ScriptablePluginObjectBase::_Enumerate,                                     \
  ScriptablePluginObjectBase::_Construct                                      \
}

#define GET_NPOBJECT_CLASS(_class) &s##_class##_NPClass


////// functions /////////
NPError NS_PluginInitialize()
{
  return NPERR_NO_ERROR;
}
     
void NS_PluginShutdown()
{
}
     
nsPluginInstanceBase * NS_NewPluginInstance(nsPluginCreateData * aCreateDataStruct)
{
  if(!aCreateDataStruct)
    return NULL;
     
  KPlugin * plugin = new KPlugin(aCreateDataStruct->instance);
  return plugin;
}
     
void NS_DestroyPluginInstance(nsPluginInstanceBase * plugin)
{
  if(plugin)
    delete (KPlugin *)plugin;
}


////// KPlugin /////////
CMainDlg *KPlugin::m_dlg=0;

KPlugin::KPlugin(NPP pNPInstance) : nsPluginInstanceBase(),
	m_pNPInstance(pNPInstance),
	m_bInitialized(FALSE)
{
	const char *ua = NPN_UserAgent(m_pNPInstance);
	strcpy(m_String, ua);
	m_dlg = 0;
	image = 0;
	playStarted = false;
}


KPlugin::~KPlugin(void)
{
}

#define WIDTHBYTES(bits) (((bits)+31)/32*4)
#define WIDTHSTEP(width)	((width*3+3)/4*4)
long nframe =0;
void callbackDecoderHandle(LPVOID lpobj, unsigned char* rgb24, int   outSize, int width, int height){

	KPlugin* plugin = (KPlugin*)lpobj;
	char str[256]={0};
	sprintf(str, "Resolution: %d X %d  @Frame: %d ", width, height , ++nframe);
	kprintf("%s", str );
	logprintf(str);

	/*
	RECT rc;
	GetClientRect(plugin->m_hWnd, &rc);
	Bitmap bmp(width, height , WIDTHSTEP(width),PixelFormat24bppRGB, rgb24); 

	CRect rect = rc;
	Graphics *graphics = Graphics::FromHWND(plugin->m_hWnd);
	graphics->DrawImage(plugin->image,0,0, rect.Width(), rect.Height());
	*/
}


static void MessageInfo(LPVOID lpobj, WORD errorCode, char* Message){
	KPlugin* plugin = (KPlugin*)lpobj;
	char str[256]={0};
	sprintf(str, "VideoMessageBack [CODE:%d]:  %s  %s\0", errorCode, Message, plugin->m_String);
	kprintf("%s", str );
	logprintf(str);
	if(errorCode==3)
		plugin->playStarted = true;
	else
		plugin->playStarted = false;

//	IDECODER_Stop(plugin->m_hPlay);
 }


#ifdef XP_WIN
static LRESULT CALLBACK PluginWinProc(HWND, UINT, WPARAM, LPARAM);
static WNDPROC lpOldProc = NULL;
#endif
NPBool KPlugin::init(NPWindow* pNPWindow)  {  
	if(pNPWindow == NULL)
		return false;

#ifdef XP_WIN
	m_hWnd = (HWND)pNPWindow->window;
	if(m_hWnd == NULL)
		return false;

	// subclass window so we can intercept window messages and
	// do our drawing to it
	lpOldProc = SubclassWindow(m_hWnd, (WNDPROC)PluginWinProc);

	// associate window with our CPlugin object so we can access 
	// it in the window procedure
	SetWindowLongPtr(m_hWnd, GWLP_USERDATA, (LONG_PTR)this);
#endif

	m_Window = pNPWindow;
	image = Util::KLoadImage("d:/wall/001.jpg");

	
	m_dlg = new CMainDlg;
//	m_dlg->Create(IDD_DLG_MAIN,  CWnd::FromHandle(m_hWnd));

	m_bInitialized = true;
	bInitialized = true;

	logprintf("KPlugin::init");
	return true;
}

int16_t KPlugin::handleEvent(void* event)
{
#ifdef XP_MAC
  NPEvent* ev = (NPEvent*)event;
  if (m_Window) {
    Rect box = { m_Window->y, m_Window->x,
                 m_Window->y + m_Window->height, m_Window->x + m_Window->width };
    if (ev->what == updateEvt) {
      ::TETextBox(m_String, strlen(m_String), &box, teJustCenter);
    }
  }
#endif
  return 0;
}

#ifdef XP_WIN
static LRESULT CALLBACK PluginWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	KPlugin * p = (KPlugin *)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	HDC hdc = BeginPaint(hWnd, &ps);
	switch (msg) {
	case WM_PAINT:
		{
			// draw a frame and display the string
			RECT rc;
			GetClientRect(hWnd, &rc);
			FrameRect(hdc, &rc, GetStockBrush(BLACK_BRUSH));

			if(p) {
				if (p->m_String[0] == 0) {
					strcpy("foo", p->m_String);
				}
				//    DrawText(hdc, p->m_String, strlen(p->m_String), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
			strcpy(p->m_String, "This is the plugin draw text.");
			DrawText(hdc,  p->m_String, strlen(p->m_String), &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			CRect rect = rc;
			//	CWnd *cwnd1 = CWnd::FromHandle(p->m_hWnd);	CDC *cdc = cwnd1->GetDC();
				Graphics *graphics = Graphics::FromHWND(p->m_hWnd);
				graphics->DrawImage(p->image,0,0, rect.Width(), rect.Height());

			//	KPlugin::m_dlg->MoveWindow(rect , TRUE);

			EndPaint(hWnd, &ps);
		}
		break;
	case WM_LBUTTONDOWN:  
		Beep(1000,200);  
		if(p->bInitialized){
			DWORD dwReserve = 0x00; 
			bool bok = IDECODER_SetDecoder(&p->m_hPlay, "rtsp://10.168.1.226/live1.sdp" , &dwReserve);
			
			IDECODER_SetCallBack(p->m_hPlay, p, callbackDecoderHandle, MessageInfo);//for callback
			IDECODER_Start(p->m_hPlay);
			logprintf("IDECODER_Start ");
		}
		break;  
	case WM_MOUSEMOVE:  
	{	
		if(p->playStarted)
		{
			unsigned char* pRecv = new unsigned char[2041*1088*3]; 
			memset(pRecv, 0x00, 2041*1088*3); 
			int RecvLen = 0x00; int width = 0x00; int height = 0x00; 
			IDECODER_Buffer(p->m_hPlay, pRecv,& RecvLen, & width, & height); 
			Bitmap bmp(width, height , WIDTHSTEP(width),PixelFormat24bppRGB, pRecv); 
			logprintf("WM_MOUSEMOVE: width=%d  height=%d  ", width, height);
		}
	//	int x=LOWORD(lParam);  
	//	int y=HIWORD(lParam);  
		break;
	}
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
#endif

void KPlugin::getVersion(char* *aVersion)
{
	const char *ua = NPN_UserAgent(m_pNPInstance);
	char*& version = *aVersion;
	version = (char*)NPN_MemAlloc(1 + strlen(ua));
	if (version)
		strcpy(version, ua);
}

NPObject *KPlugin::GetScriptableObject()
{
	/*
	if (!m_pScriptableObject) {
    m_pScriptableObject =
      NPN_CreateObject(m_pNPInstance,GET_NPOBJECT_CLASS(ScriptablePluginObject));
  }

  if (m_pScriptableObject) {
    NPN_RetainObject(m_pScriptableObject);
  }
  */
  return m_pScriptableObject;
}
