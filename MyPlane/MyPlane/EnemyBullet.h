#pragma once
#include "Object.h"
class EnemyBullet :
	public Object
{
public:
	EnemyBullet(int x, int y);
	~EnemyBullet();
	int type;
	static const int PLANE_WIDTH = 30;//���õл��ӵ��Ŀ��
	static const int PLANE_HEIGHT = 30;//���õл��ӵ��ĳ���

	BOOL Draw(CDC *pDC, BOOL bPause);

	static BOOL LoadImageW();

	/*�õ��л��ӵ����ڵľ�������*/
	CRect GetRect()
	{
		return CRect(objPos, CPoint(objPos.x + PLANE_WIDTH, objPos.y + PLANE_HEIGHT));
	}

private:
	static CImageList m_Images;/*�洢�л��ӵ�ͼƬ*/
	static CImageList boss_Images;
};

