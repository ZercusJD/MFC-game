
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

	SetTimer(1,80,NULL);//界面刷新
	SetTimer(2, 2000, NULL);//敌机出现
	SetTimer(3, 1000, NULL);//敌机发射子弹
	SetTimer(0, 600, NULL);

	//在绘制完图后,使窗口区有效  
	ValidateRect(&m_client);
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	cDC = this->GetDC();   //获得当前窗口的DC     
	GetClientRect(&m_client);   //获得窗口的尺寸 

	m_cacheCBitmap.LoadBitmap(IDB_BITMAP9);
	CDC m_cacheDC;//cache cdc
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheDC.SelectObject(m_cacheCBitmap);

	if (myPlane != NULL)
		myPlane->Draw(/*cDC*/&m_cacheDC, TRUE);

	if (myPlane != NULL)
	{
		/***************************************wasd控制我方飞机移动*******************************/
		if (GetKeyState('W') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y - 20);
		if (GetKeyState('S') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y + 20);
		if (GetKeyState('A') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x - 20, myPlane->GetPoint().y);
		if (GetKeyState('D') < 0)
			myPlane->SetPoint(myPlane->GetPoint().x + 20, myPlane->GetPoint().y);

		/************************************空格控制我方子弹发射*************************************/
		if (GetKeyState(VK_SPACE) < 0)
		{
			MyBullet *bullet = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y);
			//bullet->Draw(&m_cacheDC, TRUE);
			myBulletList.AddTail(bullet);
		}
	}
		/*****************************************敌机出现*******************************************/
		if (nIDEvent == 2)
		{
			int tx = rand() % 1200 + 10;
			int ty = 10;
			Enemy * enemy = new Enemy(tx, ty);
			enemy->enemyType = rand() % 2;//随机选择飞机种类
			//enemy->Draw(&m_cacheDC, TRUE);
			enemyList.AddTail(enemy);
		}

		/******************************************敌机移动*******************************************/
		POSITION pos = enemyList.GetHeadPosition();
		while (pos != NULL)
		{
			POSITION tmp = pos;
			Enemy * enemy = (Enemy*)enemyList.GetNext(pos);//链表循环
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

				/***************敌机发射子弹******************/
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
		/*********************************我方子弹移动*******************************/
		POSITION pos1 = myBulletList.GetHeadPosition();
		while (pos1 != NULL)
		{
			POSITION tmp = pos1;
			MyBullet * bullet = (MyBullet*)myBulletList.GetNext(pos1);//链表循环
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

		/*********************************敌机子弹移动*******************************/
		POSITION pos2 = enemyBulletList.GetHeadPosition();
		while (pos2 != NULL)
		{
			POSITION tmp = pos2;
			EnemyBullet * bullet = (EnemyBullet*)enemyBulletList.GetNext(pos2);//链表循环
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

		/************************************碰撞检测******************************************/
	if (myPlane != NULL)
	{
		/*飞机相撞坠毁*/
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
		
		/*敌机击中我方*/
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

	/*击中敌机*/
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


	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);//加入绘制的代码

	m_cacheCBitmap.DeleteObject();//释放缓冲位图
	m_cacheDC.DeleteDC();//释放缓冲DC
	ReleaseDC(cDC);//释放DC  

	CWnd::OnTimer(nIDEvent);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//myPlane->SetPoint(point.x, point.y);
	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CWnd::OnLButtonDown(nFlags, point);
}
