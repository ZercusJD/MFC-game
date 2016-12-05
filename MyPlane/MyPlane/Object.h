#pragma once
#include "afx.h"
#include "Resource.h"
class Object:public CObject
{
public:
	Object(int x=0, int y=0);
	virtual ~Object();

	/*�����Ϸ��������Ͻ�����*/
	CPoint GetPoint()
	{
		return objPos;
	}

	/*������Ϸ��������*/
	void SetPoint(int x, int y)
	{
		objPos.x = x;
		objPos.y = y;
	}

	/*����ͼ��*/
	virtual BOOL Draw(CDC *pDC, BOOL bPause) = 0;

	/*��þ�������*/
	virtual CRect GetRect() = 0;

protected:
	CPoint objPos;//��Ϸ���������
protected:
	//static BOOL LoadImage(CImageList &imgList, UINT bmpID, COLORREF crMask, int cx, int cy, int nInitial);//����ͼ��
};

