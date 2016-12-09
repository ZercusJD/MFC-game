#include "stdafx.h"
#include "MyBullet.h"

CImageList MyBullet::m_Images;

MyBullet::MyBullet(int x,int y)
{
	objPos.x = x + 64 - 9;
	objPos.y = y - 50;
}


MyBullet::~MyBullet()
{
}

BOOL MyBullet::Draw(CDC *pDC, BOOL bPause)
{
	m_Images.Draw(pDC, 0, objPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL MyBullet::LoadImageW()
{
	//return Object::LoadImage(m_Images, IDB_BITMAP3, RGB(0, 0, 0), 50, 60, 1);
	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_BITMAP4))//IDB_BITMAP10
		return FALSE;

	if (!m_Images.Create(17, 40, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度

	m_Images.Add(&bmp, RGB(0, 0, 0));

	return TRUE;
}
