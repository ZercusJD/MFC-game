
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
	EnemyBullet::LoadImageW();
	Enemy::LoadImageW();
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

	SetTimer(1,80,NULL);//����ˢ��
	SetTimer(2, 2000, NULL);//�л�����
	SetTimer(3, 1000, NULL);//�л������ӵ�
	SetTimer(0, 600, NULL);

	//�ڻ�����ͼ��,ʹ��������Ч  
	ValidateRect(&m_client);
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	cDC = this->GetDC();   //��õ�ǰ���ڵ�DC     
	GetClientRect(&m_client);   //��ô��ڵĳߴ� 

	m_cacheCBitmap.LoadBitmap(IDB_BITMAP9);
	CDC m_cacheDC;//cache cdc
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheDC.SelectObject(m_cacheCBitmap);

	if (myPlane != NULL)
		myPlane->Draw(/*cDC*/&m_cacheDC, TRUE);

	if (myPlane != NULL)
	{
		/***************************************wasd�����ҷ��ɻ��ƶ�*******************************/
		if (GetKeyState('W') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y - 20);
		if (GetKeyState('S') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y + 20);
		if (GetKeyState('A') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x - 20, myPlane->GetPoint().y);
		if (GetKeyState('D') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x + 20, myPlane->GetPoint().y);

		/************************************�ո�����ҷ��ӵ�����*************************************/
		if (GetKeyState(VK_SPACE) < 0)
		{
			MyBullet *bullet = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y);
			//bullet->Draw(&m_cacheDC, TRUE);
			myBulletList.AddTail(bullet);
		}
	}
		/*****************************************�л�����*******************************************/
		if (nIDEvent == 2)
		{
			int tx = rand() % 1200 + 10;
			int ty = 10;
			Enemy * enemy = new Enemy(tx, ty);
			enemy->enemyType = rand() % 2;//���ѡ��ɻ�����
			//enemy->Draw(&m_cacheDC, TRUE);
			enemyList.AddTail(enemy);
		}

		/******************************************�л��ƶ�*******************************************/
		POSITION pos = enemyList.GetHeadPosition();
		while (pos != NULL)
		{
			POSITION tmp = pos;
			Enemy * enemy = (Enemy*)enemyList.GetNext(pos);//����ѭ��
			if (enemy->GetPoint().x > m_client.left
				&&enemy->GetPoint().x < m_client.right
				&&enemy->GetPoint().y < m_client.bottom
				&&enemy->GetPoint().y > m_client.top)
			{
				if (enemy->enemyType == 0)
					enemy->SetPoint(enemy->GetPoint().x, enemy->GetPoint().y + 10);
				else
					enemy->SetPoint(enemy->GetPoint().x, enemy->GetPoint().y + 20);
				enemy->Draw(&m_cacheDC, TRUE);

				/***************�л������ӵ�******************/
				if (nIDEvent == 3)
				{
					EnemyBullet *enemy_bullet = new EnemyBullet(enemy->GetPoint().x, enemy->GetPoint().y);
					enemyBulletList.AddTail(enemy_bullet);
				}
			}
			else{
				enemyList.RemoveAt(tmp);
				delete enemy;
			}
		}
		/*********************************�ҷ��ӵ��ƶ�*******************************/
		POSITION pos1 = myBulletList.GetHeadPosition();
		while (pos1 != NULL)
		{
			POSITION tmp = pos1;
			MyBullet * bullet = (MyBullet*)myBulletList.GetNext(pos1);//����ѭ��
			if (bullet->GetPoint().x > m_client.left
				&&bullet->GetPoint().x < m_client.right
				&&bullet->GetPoint().y < m_client.bottom
				&&bullet->GetPoint().y > m_client.top)
			{
				bullet->SetPoint(bullet->GetPoint().x, bullet->GetPoint().y - bullet->PLANE_HEIGHT);
				bullet->Draw(&m_cacheDC, TRUE);
			}
			else{
				myBulletList.RemoveAt(tmp);
				delete bullet;
			}
		}

		/*********************************�л��ӵ��ƶ�*******************************/
		POSITION pos2 = enemyBulletList.GetHeadPosition();
		while (pos2 != NULL)
		{
			POSITION tmp = pos2;
			EnemyBullet * bullet = (EnemyBullet*)enemyBulletList.GetNext(pos2);//����ѭ��
			if (bullet->GetPoint().x > m_client.left
				&&bullet->GetPoint().x < m_client.right
				&&bullet->GetPoint().y < m_client.bottom
				&&bullet->GetPoint().y > m_client.top)
			{
				bullet->SetPoint(bullet->GetPoint().x, bullet->GetPoint().y + bullet->PLANE_HEIGHT);
				bullet->Draw(&m_cacheDC, TRUE);
			}
			else{
				enemyBulletList.RemoveAt(tmp);
				delete bullet;
			}
		}

		/************************************��ײ���******************************************/
	if (myPlane != NULL)
	{
		/*�ɻ���ײ׹��*/
		POSITION pos3 = enemyList.GetHeadPosition();
		while (pos3 != NULL)
		{
			POSITION tmp = pos3;
			Enemy*enemy = (Enemy*)enemyList.GetNext(pos3);
			CRect r1 = enemy->GetRect();
			CRect r2 = myPlane->GetRect();
			CRect t;
			if (t.IntersectRect(&r1, &r2))
			{
				//delete myPlane;
				enemyList.RemoveAt(tmp);
				start = FALSE;
			}
		}
		
		/*�л������ҷ�*/
		POSITION pos5 = enemyBulletList.GetHeadPosition();
		while (pos5 != NULL)
		{
			POSITION tmp = pos5;
			Enemy*enemy_bullet = (Enemy*)enemyList.GetNext(pos5);
			CRect r1 = enemy_bullet->GetRect();
			CRect r2 = myPlane->GetRect();
			CRect t;
			if (t.IntersectRect(&r1, &r2))
			{
				enemyBulletList.RemoveAt(tmp);
				//delete myPlane;
				start = FALSE;
			}
		}
	}

	/*���ел�*/
	POSITION pos4 = enemyList.GetHeadPosition();
	while (pos4 != NULL)
	{
		POSITION tmp1 = pos4;
		Enemy*enemy = (Enemy*)enemyList.GetNext(pos4);
		POSITION pos_my_bullet = myBulletList.GetHeadPosition();
		while (pos_my_bullet != NULL){
			POSITION tmp2 = pos_my_bullet;
			MyBullet *bullet = (MyBullet*)myBulletList.GetNext(pos_my_bullet);
			CRect r1 = enemy->GetRect();
			CRect r2 = bullet->GetRect();
			CRect t;
			if (t.IntersectRect(&r1, &r2))
			{
				enemyList.RemoveAt(tmp1);
				myBulletList.RemoveAt(tmp2);
			}
		}
	}


	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);//������ƵĴ���

	m_cacheCBitmap.DeleteObject();//�ͷŻ���λͼ
	m_cacheDC.DeleteDC();//�ͷŻ���DC
	ReleaseDC(cDC);//�ͷ�DC  

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//myPlane->SetPoint(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CWnd::OnLButtonDown(nFlags, point);
}
