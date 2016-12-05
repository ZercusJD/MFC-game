#pragma once

#include "Object.h"
class Plane:public Object
{
public:
	Plane();
	~Plane();

	static const int PLANE_WIDTH = 128;//设置战机的宽度
	static const int PLANE_HEIGHT = 88;//设置战机的长度

	BOOL Draw(CDC *pDC, BOOL bPause);

	BOOL LoadImageW();

	/*得到战机所在的矩形区域*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + PLANE_WIDTH, objPos.y + PLANE_HEIGHT));
	}

	/*战机是否可以发射子弹*/
	BOOL isFired();

private:
	CImageList m_Images;/*存储战机图片*/
};

