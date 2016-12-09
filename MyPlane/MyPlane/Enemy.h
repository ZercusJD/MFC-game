#pragma once
#include "Object.h"
class Enemy :
	public Object
{
public:
	Enemy(int x, int y);
	~Enemy();

	int enemyType;//�ɻ�����

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImageW();

	/*�õ��л����ڵľ�������*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + 108, objPos.y + 88));
	}

private:
	static CImageList m_Images1;/*�洢�л�ͼƬ ��ɫС�ɻ�*/
	static CImageList m_Images2;/*�洢�л�ͼƬ ��ɫС�ɻ�*/
	static CImageList m_Images3;/*�洢�л�ͼƬ ��ɫ��ɻ�*/
};

