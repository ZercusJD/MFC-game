#include "stdafx.h"
#include "Plane.h"


Plane::Plane()
{
	objPos.x = 1277/2-PLANE_WIDTH/2;
	objPos.y = 719-PLANE_HEIGHT-10;
}


Plane::~Plane()
{
}

BOOL Plane::Draw(CDC *pDC, BOOL bPause)
{
	m_Images.Draw(pDC, 0, objPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL Plane::LoadImageW()
{
	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_BITMAP3))
		return FALSE;

	if (!m_Images.Create(128, 88, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度

	m_Images.Add(&bmp, RGB(0, 0, 0));

	return TRUE;
}