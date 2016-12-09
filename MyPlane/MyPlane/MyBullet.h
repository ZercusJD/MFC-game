#pragma once
#include "Object.h"

class MyBullet :
	public Object
{
public:
	MyBullet(int x,int y);
	~MyBullet();

	static const int PLANE_WIDTH = 17;//�����ӵ��Ŀ��
	static const int PLANE_HEIGHT = 40;//�����ӵ��ĳ���

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImageW();

	/*�õ�ս�����ڵľ�������*/
	CRect GetRect()
	{
		return CRect(CPoint(objPos.x,objPos.y), CPoint(objPos.x + PLANE_WIDTH, objPos.y + PLANE_HEIGHT));
	}

private:
	static CImageList m_Images;/*�洢�ӵ�ͼƬ*/
};

