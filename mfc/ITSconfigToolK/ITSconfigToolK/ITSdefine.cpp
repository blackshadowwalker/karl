

#include "stdafx.h"
#include "ITSdefine.h"

CPoint CPoint2ImagePoint(CPoint &ptSrc, SIZE rectSize, SIZE imageSize, bool bCover){
	CPoint ptDest;
	float dtx = imageSize.cx / rectSize.cx;
	float dty = imageSize.cx / rectSize.cy; 
	ptDest.x = ptSrc.x*1.0 * dtx;
	ptDest.y = ptSrc.y*1.0 * dty;
	if(bCover)
		ptSrc = ptDest;
	return ptDest;
}
CPoint ImagePoint2CPoint(CPoint &ptSrc, SIZE rectSize, SIZE imageSize, bool bCover){
	CPoint ptDest;
	float dtx = imageSize.cx / rectSize.cx;
	float dty = imageSize.cx / rectSize.cy; 
	ptDest.x = ptSrc.x*1.0 / dtx;
	ptDest.y = ptSrc.y*1.0 / dty;
	if(bCover)
		ptSrc = ptDest;
	return ptDest;
}