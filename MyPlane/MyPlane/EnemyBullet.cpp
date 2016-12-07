#include "stdafx.h"
#include "EnemyBullet.h"
CImageList EnemyBullet::m_Images;

EnemyBullet::EnemyBullet(int x, int y)
{
	objPos.x = x + 108/2 - 15;
	objPos.y = y + 30;
}


EnemyBullet::~EnemyBullet()
{
}

BOOL EnemyBullet::Draw(CDC *pDC, BOOL bPause)
{
	m_Images.Draw(pDC, 0, objPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL EnemyBullet::LoadImageW()
{
	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_BITMAP5))//�������ӵ�
		return FALSE;

	if (!m_Images.Create(30, 30, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��

	m_Images.Add(&bmp, RGB(0, 0, 0));

	return TRUE;
}