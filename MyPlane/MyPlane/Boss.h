#pragma once
#include "Object.h"
#include"Plane.h"
#include"EnemyBullet.h"
class Boss :
	public Object
{
public:
	Boss();
	Boss(int x, int y);
	~Boss();
	BOOL Draw(CDC *pDC, BOOL bPause);
	
	void bossBulletMove(CObList *bulletList, int x, int y, CDC *pDC);
	BOOL bossHitMe(CObList *bulletList, Plane *myPlane,int &life);
	BOOL bossCrash(Plane *myPlane);
	static BOOL LoadImageW();
	int life;

	/*�õ�boss���ڵľ�������*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + 360, objPos.y + 250));
	}

	//void bossBattle(Plane me);
private:
	static CImageList m_Images;
};

