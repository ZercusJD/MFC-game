#pragma once
#include "Object.h"

class MyBullet :
	public Object
{
public:
	MyBullet(int x,int y);
	~MyBullet();

	static const int PLANE_WIDTH = 17;//设置子弹的宽度
	static const int PLANE_HEIGHT = 40;//设置子弹的长度

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImageW();

	/*得到战机所在的矩形区域*/
	CRect GetRect()
	{
		return CRect(CPoint(objPos.x,objPos.y), CPoint(objPos.x + PLANE_WIDTH, objPos.y + PLANE_HEIGHT));
	}

private:
	static CImageList m_Images;/*存储子弹图片*/
};

