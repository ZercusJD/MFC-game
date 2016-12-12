
// ChildView.h : CChildView 类的接口
//


#pragma once
#include"Object.h"
#include"Plane.h"
#include"MyBullet.h"
#include"Enemy.h"
#include"EnemyBullet.h"
#include"Scene.h"

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:
	CRect m_client;
	CDC *cDC;
	CBitmap m_cacheCBitmap;//缓冲位图
	int CTop,CBottom;

	/*创建游戏对象*/
	Plane *myPlane;

	/*对象链表*/
	CObList myBulletList;
	CObList enemyList;
	CObList enemyBulletList;

	int mySpeed;
	int enemySpeed;
	int bulletSpeed;

	BOOL start = TRUE;

// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

