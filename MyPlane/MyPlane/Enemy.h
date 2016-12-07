#pragma once
#include "Object.h"
class Enemy :
	public Object
{
public:
	Enemy(int x, int y);
	~Enemy();

	int enemyType;//�ɻ�����

	static const int PLANE_WIDTH = 17;//���õл��Ŀ��
	static const int PLANE_HEIGHT = 40;//���õл��ĳ���

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImageW();

	/*�õ��л����ڵľ�������*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + PLANE_WIDTH, objPos.y + PLANE_HEIGHT));
	}

private:
	static CImageList m_Images1;/*�洢�л�ͼƬ ��ɫС�ɻ�*/
	static CImageList m_Images2;/*�洢�л�ͼƬ ��ɫС�ɻ�*/
	static CImageList m_Images3;/*�洢�л�ͼƬ ��ɫ��ɻ�*/
};

