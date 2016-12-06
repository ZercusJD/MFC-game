
// ChildView.cpp : CChildView ���ʵ��
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

	MyBullet::LoadImageW();
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



// CChildView ��Ϣ�������

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
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������
 
	// TODO:  �ڴ˴������Ϣ����������

	SetTimer(1,100,NULL);

	//�ڻ�����ͼ��,ʹ��������Ч  
	ValidateRect(&m_client);
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	cDC = this->GetDC();   //��õ�ǰ���ڵ�DC     
	GetClientRect(&m_client);   //��ô��ڵĳߴ� 

	m_cacheCBitmap.LoadBitmap(IDB_BITMAP2);
	CDC m_cacheDC;//cache cdc
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheDC.SelectObject(m_cacheCBitmap);

	if (myPlane!=NULL)
	    myPlane->Draw(/*cDC*/&m_cacheDC, TRUE);

	/***************************************���Ʒɻ��ƶ�*******************************/
	if (GetKeyState('W')<0)
		myPlane->SetPoint(myPlane->GetPoint().x , myPlane->GetPoint().y-20);
	if (GetKeyState('S')<0)
		myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y + 20);
	if (GetKeyState('A')<0)
		myPlane->SetPoint(myPlane->GetPoint().x-20, myPlane->GetPoint().y);
	if (GetKeyState('D')<0)
		myPlane->SetPoint(myPlane->GetPoint().x+20, myPlane->GetPoint().y);

	/************************************�ո�����ӵ�����*************************************/
	if (GetKeyState(VK_SPACE) < 0)
	{
		MyBullet *bullet = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y);
		bullet->Draw(&m_cacheDC, TRUE);
		myBulletList.AddTail(bullet);
	}

	switch (nIDEvent)
	{
	case 1:{
		
		break;
	}
	}

	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);//������ƵĴ���

	m_cacheCBitmap.DeleteObject();
	m_cacheDC.DeleteDC();//�ͷŻ���DC
	ReleaseDC(cDC);//�ͷ�DC  

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	myPlane->SetPoint(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnLButtonDown(nFlags, point);
}
