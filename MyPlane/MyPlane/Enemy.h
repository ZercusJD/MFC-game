#pragma once
#include "Object.h"
class Enemy :
	public Object
{
public:
	Enemy(int x, int y);
	~Enemy();

	int enemyType;//飞机种类

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImageW();

	/*得到敌机所在的矩形区域*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + 108, objPos.y + 88));
	}

private:
	static CImageList m_Images1;/*存储敌机图片 红色小飞机*/
	static CImageList m_Images2;/*存储敌机图片 蓝色小飞机*/
	static CImageList m_Images3;/*存储敌机图片 蓝色大飞机*/
};

