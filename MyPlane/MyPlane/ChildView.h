
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once
#include"Object.h"
#include"Plane.h"
#include"MyBullet.h"
#include"Enemy.h"
#include"EnemyBullet.h"
#include"Scene.h"

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

	/*��������*/
	CObList myBulletList;
	CObList enemyList;
	CObList enemyBulletList;

	int mySpeed;
	int enemySpeed;
	int bulletSpeed;

	BOOL start = TRUE;

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

