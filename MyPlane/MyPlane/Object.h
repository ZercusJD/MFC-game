#pragma once
#include "afx.h"
#include "Resource.h"
class Object:public CObject
{
public:
	Object(int x=0, int y=0);
	virtual ~Object();

	/*获得游戏对象的左上角坐标*/
	CPoint GetPoint()
	{
		return objPos;
	}

	/*设置游戏对象坐标*/
	void SetPoint(int x, int y)
	{
		objPos.x = x;
		objPos.y = y;
	}

	/*绘制图像*/
	virtual BOOL Draw(CDC *pDC, BOOL bPause) = 0;

	/*获得矩形区域*/
	virtual CRect GetRect() = 0;

protected:
	CPoint objPos;//游戏对象的坐标
protected:
	//static BOOL LoadImage(CImageList &imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);//加载图像
};

