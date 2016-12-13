#include "stdafx.h"
#include "EnemyBullet.h"
CImageList EnemyBullet::m_Images;
CImageList EnemyBullet::boss_Images;

EnemyBullet::EnemyBullet(int x, int y)
{
	objPos.x = x ;
	objPos.y = y ;
	type = 0;
}


EnemyBullet::~EnemyBullet()
{
}

BOOL EnemyBullet::Draw(CDC *pDC, BOOL bPause)
{
	if (type == 0){
		m_Images.Draw(pDC, 0, objPos, ILD_TRANSPARENT);
	}
	else if (type == 1){
		boss_Images.Draw(pDC, 0, objPos, ILD_TRANSPARENT);
	}
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

	CBitmap bmp1;
	if (!bmp1.LoadBitmap(IDB_BITMAP12))//boss bullet
		return FALSE;

	if (!boss_Images.Create(55, 140, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial��ʼ����
		return FALSE;//cx,cy ͼƬ�Ŀ��

	boss_Images.Add(&bmp1, RGB(255, 255, 255));
	//boss_Images.Add(&bmp1, RGB(0, 0, 0));

	return TRUE;
}