#include "stdafx.h"
#include "Boss.h"

CImageList Boss::m_Images;
Boss::Boss()
{
}

Boss::Boss(int x, int y)
{
	objPos.x = x;
	objPos.y = y;
	life = 500;
}

void Boss::bossBulletMove(CObList *bulletList, int x, int y, CDC *pDC)
{
	POSITION pos = bulletList->GetHeadPosition();
	while (pos != NULL)
	{
		POSITION tmp = pos;
		EnemyBullet * bullet = (EnemyBullet*)bulletList->GetNext(pos);//链表循环
		if (bullet->GetPoint().x > 0
			&&bullet->GetPoint().x < 1277
			&&bullet->GetPoint().y < 719
			&& bullet->GetPoint().y > 0)
		{
			bullet->SetPoint(bullet->GetPoint().x + x, bullet->GetPoint().y + y);
			bullet->Draw(pDC, TRUE);
		}
		else{
			bulletList->RemoveAt(tmp);
			delete bullet;
			break;
		}
	}
}

BOOL Boss::bossHitMe(CObList *bulletList, Plane *myPlane, int &life)
{
	POSITION pos = bulletList->GetHeadPosition();
	while (pos != NULL)
	{
		POSITION tmp = pos;
		EnemyBullet* bullet = (EnemyBullet*)bulletList->GetNext(pos);
		CRect r1 = bullet->GetRect();
		CRect r2 = myPlane->GetRect();
		CRect t;
		if (t.IntersectRect(&r1, &r2))
		{
			bulletList->RemoveAt(tmp);
			//delete myPlane;
			life--;
			myPlane->SetPoint(1277 / 2 - myPlane->PLANE_WIDTH / 2, 719 - myPlane->PLANE_HEIGHT - 10);
			break;
		}
	}
	return TRUE;
}

BOOL Boss::bossCrash(Plane*myPlane)
{
	CRect r1 = GetRect();
	CRect r2 = myPlane->GetRect();
	CRect t;
	if (t.IntersectRect(&r1, &r2))
	{
		//delete myPlane;
		myPlane->SetPoint(1277 / 2 - myPlane->PLANE_WIDTH / 2, 719 - myPlane->PLANE_HEIGHT - 10);
		return TRUE;
	}
	return FALSE;
}

Boss::~Boss()
{
}

BOOL Boss::Draw(CDC *pDC, BOOL bPause)
{
	m_Images.Draw(pDC, 0, objPos, ILD_TRANSPARENT);
	return TRUE;
}

BOOL Boss::LoadImageW()
{
	CBitmap bmp;
	if (!bmp.LoadBitmap(IDB_BITMAP11))
		return FALSE;
	if (!m_Images.Create(360, 250, ILC_COLOR24 | ILC_MASK, 1, 0))//nInitial初始个数
		return FALSE;//cx,cy 图片的宽度
	m_Images.Add(&bmp, RGB(0, 0, 0));
	return TRUE;
}