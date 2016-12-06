
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
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
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

	SetTimer(1,100,NULL);

	//在绘制完图后,使窗口区有效  
	ValidateRect(&m_client);
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	cDC = this->GetDC();   //获得当前窗口的DC     
	GetClientRect(&m_client);   //获得窗口的尺寸 

	m_cacheCBitmap.LoadBitmap(IDB_BITMAP2);
	CDC m_cacheDC;//cache cdc
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheDC.SelectObject(m_cacheCBitmap);

	myPlane->Draw(/*cDC*/&m_cacheDC, TRUE);
	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);//加入绘制的代码
	
	/*if (GetKeyState(0x57))
		myPlane->SetPoint(myPlane->GetPoint().x , myPlane->GetPoint().y-10);
	else if (GetKeyState(0x53))
		myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y + 10);
	else if (GetKeyState(0x41))
		myPlane->SetPoint(myPlane->GetPoint().x-10, myPlane->GetPoint().y);
	else if (GetKeyState(0x44))
		myPlane->SetPoint(myPlane->GetPoint().x+10, myPlane->GetPoint().y);*/

	switch (nIDEvent)
	{
	case 1:{
		
		break;
	}
	}

	m_cacheCBitmap.DeleteObject();
	m_cacheDC.DeleteDC();//释放缓冲DC
	ReleaseDC(cDC);//释放DC  

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	myPlane->SetPoint(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CWnd::OnLButtonDown(nFlags, point);
}
