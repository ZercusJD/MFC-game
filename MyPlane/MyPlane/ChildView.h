
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once
#include"Object.h"
#include"Plane.h"
#include"MyBullet.h"
#include"Enemy.h"
#include"EnemyBullet.h"
#include"Boss.h"

// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
	CRect m_client;
	CDC *cDC;
	CBitmap m_cacheCBitmap;//����λͼ
	int CTop,CBottom;

	/*������Ϸ����*/
	Plane *myPlane;
	Boss *boss = NULL;

	/*��������*/
	CObList myBulletList;
	CObList enemyList;
	CObList enemyBulletList;

	CObList bossbullet0, bossbullet1, bossbullet2, bossbullet3, bossbullet4;

	int Score = 0;
	int life = 3;

	BOOL start = TRUE;
	BOOL bossMode = false;
	BOOL bossMove = false;
	int bossDirect;
	int Stage = 0;

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

