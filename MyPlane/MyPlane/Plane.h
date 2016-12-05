#pragma once

#include "Object.h"
class Plane:public Object
{
public:
	Plane();
	~Plane();

	static const int PLANE_WIDTH = 128;//����ս���Ŀ��
	static const int PLANE_HEIGHT = 88;//����ս���ĳ���

	BOOL Draw(CDC *pDC, BOOL bPause);

	BOOL LoadImageW();

	/*�õ�ս�����ڵľ�������*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + PLANE_WIDTH, objPos.y + PLANE_HEIGHT));
	}

	/*ս���Ƿ���Է����ӵ�*/
	BOOL isFired();

private:
	CImageList m_Images;/*�洢ս��ͼƬ*/
};

