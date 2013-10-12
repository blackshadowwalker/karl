#include "StdAfx.h"
#include "Util.h"


void __cdecl kprintf(const char *format, ...)
{
	char buf[4096]={0}, *p = buf;
    va_list args;
    va_start(args, format);
    p += _vsnprintf(p,4096, format, args);
    va_end(args);
//	*(p) = '\n';
    OutputDebugString(buf);
}

void __cdecl logprintf(const char *format, ...)
{
	char buf[4096]={0}, *p = buf;
    va_list args;
    va_start(args, format);
    p += _vsnprintf(p, sizeof buf - 1, format, args);
    va_end(args);

	time_t rawtime;
	struct tm * timeinfo;
	char timE [80];
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	strftime ( timE,80,"%Y/%m/%d %I:%M:%S",timeinfo);

    FILE* fp = fopen("f:/kplugin.log", "a+");
	if(fp!=NULL){
		fprintf(fp, "[%s] %s \n", timE, buf);
		fclose(fp);
	}
}


Util::Util(void)
{
	GdiplusStartup(&m_pGdiToken,&m_gdiplusStartupInput,NULL);
}

Util::~Util(void)
{
}

// origin=0 :left-top, origin=1 : left-bottom
void Util::DrawImg2Hdc(CWnd* cWnd,UINT id, Image *image, int origin)
{
	if(image==0) return;
	CRect rect;
	CDC* pDC = cWnd->GetDlgItem(id)->GetDC();
	cWnd->GetDlgItem(id)->GetWindowRect(&rect);
	Graphics graphics( pDC->m_hDC);

	if(origin){
		Graphics ggg(image);
		ggg.TranslateTransform(0, 0);
		ggg.DrawImage(image, 0, image->GetHeight(), image->GetWidth(), -image->GetHeight());
	}

	RectF r(0, 0, rect.Width(), rect.Height());
	graphics.DrawImage(image, r,  0,  0, image->GetWidth(), image->GetHeight(),UnitPixel);
}
Image* Util::KLoadImage(CString filename)
{
	LPWSTR strjpg = new WCHAR[255];
	LPTSTR lpStr2 = filename.GetBuffer( filename.GetLength() );
	int nLen2 = MultiByteToWideChar(CP_ACP, 0,lpStr2, -1, NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, lpStr2, -1, strjpg, nLen2);

	Image *image=0;
	image=Image::FromFile(strjpg,0);
	return image;
}

void Util::alert(char *text)
{
	MessageBox(0, text,"", MB_OK);
}
