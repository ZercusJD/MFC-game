
// ChildView.h : CChildView 类的接口
//


#pragma once
#include"Object.h"
#include"Plane.h"

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:
	CRect m_client;
	CBitmap m_bgBitmap; //背景位图对象
	CDC m_bgcDC;       //背景DC

	/*创建各个游戏对象*/
	Plane *myPlane;

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
};

