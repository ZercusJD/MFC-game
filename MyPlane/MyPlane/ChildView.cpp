
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "MyPlane.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	myPlane = new Plane;//128*88
	myPlane->LoadImageW();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO:  在此处添加消息处理程序代码
	//创建兼容的DC
	m_bgcDC.CreateCompatibleDC(NULL);
	//从资源中加载位图
	m_bgBitmap.LoadBitmap(IDB_BITMAP2);
	//选择位图对象
	m_bgcDC.SelectObject(&m_bgBitmap);

	SetTimer(1,100,NULL);
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:{
		CDC *cDC = this->GetDC();   //获得当前窗口的DC     
		GetClientRect(&m_client);   //获得窗口的尺寸  
		cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_bgcDC, 0, 0, SRCCOPY);//加入绘制的代码

		myPlane->Draw(cDC, TRUE);
		if (myPlane->GetPoint().x<600)
			myPlane->SetPoint(myPlane->GetPoint().x+10,myPlane->GetPoint().y);

		ReleaseDC(cDC);//释放DC  
		break;
	}
	}
	CWnd::OnTimer(nIDEvent);
}
