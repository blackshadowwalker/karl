#ifndef DEFINE_UTIL
#define DEFINE_UTIL

#pragma once

#define STRING(x) #x

typedef unsigned long ULONG_PTR, *PULONG_PTR;
#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib, "GdiPlus.lib")
static ULONG_PTR m_pGdiToken;
static struct GdiplusStartupInput m_gdiplusStartupInput;

void __cdecl kprintf(const char *format, ...);
void __cdecl logprintf(const char *format, ...);

enum ImageOrigin{
	LeftTop,
	LeftBottom
};

class Util
{
public:
	Util(void);
	
	static void alert(char *text);
	static void DrawImg2Hdc(CWnd* cWnd,UINT id, Image *image, int origin=ImageOrigin::LeftTop);// origin=0 :left-top, origin=1 : left-bottom
	static Image* KLoadImage(CString filename);


	~Util(void);
};

#endif