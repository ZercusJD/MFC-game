
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
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_TIMER()
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
	//�������ݵ�DC
	m_bgcDC.CreateCompatibleDC(NULL);
	//����Դ�м���λͼ
	m_bgBitmap.LoadBitmap(IDB_BITMAP2);
	//ѡ��λͼ����
	m_bgcDC.SelectObject(&m_bgBitmap);

	SetTimer(1,100,NULL);
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:{
		CDC *cDC = this->GetDC();   //��õ�ǰ���ڵ�DC     
		GetClientRect(&m_client);   //��ô��ڵĳߴ�  
		cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_bgcDC, 0, 0, SRCCOPY);//������ƵĴ���

		myPlane->Draw(cDC, TRUE);
		if (myPlane->GetPoint().x<600)
			myPlane->SetPoint(myPlane->GetPoint().x+10,myPlane->GetPoint().y);

		ReleaseDC(cDC);//�ͷ�DC  
		break;
	}
	}
	CWnd::OnTimer(nIDEvent);
}
