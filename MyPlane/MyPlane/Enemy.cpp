#include "stdafx.h"
#include "Enemy.h"
CImageList Enemy::m_Images1;
CImageList Enemy::m_Images2;
CImageList Enemy::m_Images3;

Enemy::Enemy(int x,int y)
{
	objPos.x = x;
	objPos.y = y;
	enemyType = 0;
}


Enemy::~Enemy()
{
}

BOOL Enemy::Draw(CDC *pDC, BOOL bPause)
{
	switch (enemyType)
	{
	case 0:{m_Images1.Draw(pDC, 0, objPos, ILD_TRANSPARENT); break; }
	case 1:{m_Images3.Draw(pDC, 0, objPos, ILD_TRANSPARENT); break; }
	//case 2:{m_Images3.Draw(pDC, 0, objPos, ILD_TRANSPARENT); break; }
	default:{break; }
	}
	return TRUE;
}

BOOL Enemy::LoadImageW()
{
	//return Object::LoadImage(m_Images, IDB_BITMAP3, RGB(0, 0, 0), 50, 60, 1);
	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_BITMAP6))
		return FALSE;
	if (!m_Images1.Create(108, 88, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	m_Images1.Add(&bmp, RGB(0, 0, 0));

	CBitmap bmp2;
	if (!bmp2.LoadBitmap(IDB_BITMAP7))
		return FALSE;
	if (!m_Images2.Create(108, 88, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	m_Images2.Add(&bmp2, RGB(0, 0, 0));

	CBitmap bmp3;
	if (!bmp3.LoadBitmap(IDB_BITMAP8))
		return FALSE;
	if (!m_Images3.Create(108, 88, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	m_Images3.Add(&bmp3, RGB(0, 0, 0));

	return TRUE;
}
