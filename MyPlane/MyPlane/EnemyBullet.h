#pragma once
#include "Object.h"
class EnemyBullet :
	public Object
{
public:
	EnemyBullet(int x, int y);
	~EnemyBullet();
	int type;
	static const int PLANE_WIDTH = 30;//设置敌机子弹的宽度
	static const int PLANE_HEIGHT = 30;//设置敌机子弹的长度

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImageW();

	/*得到敌机子弹所在的矩形区域*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + PLANE_WIDTH, objPos.y + PLANE_HEIGHT));
	}

private:
	static CImageList m_Images;/*存储敌机子弹图片*/
	static CImageList boss_Images;
};

