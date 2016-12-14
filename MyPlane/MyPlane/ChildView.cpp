
// ChildView.cpp : CChildView ���ʵ��
//

#include "stdafx.h"
#include "MyPlane.h"
#include "ChildView.h"

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#include <MMSYSTEM.H>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{ 
	CTop = 0;
	CBottom = 719;
	bossDirect = 1;
	myPlane = new Plane;//128*88
	myPlane->LoadImageW();

	MyBullet::LoadImageW();
	EnemyBullet::LoadImageW();
	Enemy::LoadImageW();
	Boss::LoadImageW();
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

	SetTimer(1,70,NULL);//����ˢ��
	SetTimer(2, 800, NULL);//�л������Լ������ӵ�
	SetTimer(3, 500, NULL);//�����ƶ�
	SetTimer(4, 10000, NULL);//boss����
	SetTimer(5, 20000, NULL);//first stage
	SetTimer(6, 15000, NULL);//boss move
	SetTimer(7, 40000, NULL);//second stage
	SetTimer(8, 300, NULL);//boss shoot

	//SetTimer(0, 600, NULL);

	//�ڻ�����ͼ��,ʹ��������Ч  
	ValidateRect(m_client);
	
	// ��ҪΪ������Ϣ������ CWnd::OnPaint()
}



void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	cDC = this->GetDC();   //��õ�ǰ���ڵ�DC     
	GetClientRect(m_client);   //��ô��ڵĳߴ�
	//m_client.top = CTop;
	//m_client.bottom = CBottom;

	m_cacheCBitmap.LoadBitmap(IDB_BITMAP9);
	CDC m_cacheDC;//cache cdc
	m_cacheDC.CreateCompatibleDC(NULL);
	m_cacheDC.SelectObject(m_cacheCBitmap);

	if (pause == 0){
		CImage image;//��������
		image.Load(_T("./image/galaxy.bmp"));
		int height = m_client.Height();
		m_client.bottom = CBottom;
		m_client.top = CTop;
		image.StretchBlt(m_cacheDC, m_client, SRCCOPY);//�����¶�
		m_client.bottom -= height;
		m_client.top -= height;
		image.StretchBlt(m_cacheDC, m_client, SRCCOPY);

		if (myPlane != NULL)
			myPlane->Draw(/*cDC*/&m_cacheDC, TRUE);

		if (myPlane != NULL)
		{
			/***************************************wasd�����ҷ��ɻ��ƶ�*******************************/
			if (GetKeyState('W') < 0)
				myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y - 30);
			if (GetKeyState('S') < 0)
				myPlane->SetPoint(myPlane->GetPoint().x, myPlane->GetPoint().y + 30);
			if (GetKeyState('A') < 0)
				myPlane->SetPoint(myPlane->GetPoint().x - 30, myPlane->GetPoint().y);
			if (GetKeyState('D') < 0)
				myPlane->SetPoint(myPlane->GetPoint().x + 30, myPlane->GetPoint().y);

			/************************************�ո�����ҷ��ӵ�����*************************************/
			if (GetKeyState(VK_SPACE) < 0)
			{
				MyBullet *bullet = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y);
				//bullet->Draw(&m_cacheDC, TRUE);
				myBulletList.AddTail(bullet);
				PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			}
		}

		if (/*nIDEvent == 4*/bossMode==FALSE&&Score == 20)
		{
			bossMode = TRUE;
			Stage = 1;
			KillTimer(4);
		}
		if (boss!=NULL&&bossMode&&boss->life==200)
		{
			bossMode = TRUE;
			Stage = 2;
			KillTimer(7);
		}
		if (boss!=NULL&&bossMode&&boss->life == 400){
			bossMove = TRUE;
			KillTimer(6);
		}
		if (!bossMode)//����bossģʽ
		{
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
		}
		/******************************************�л��ƶ�*******************************************/
		POSITION pos = enemyList.GetHeadPosition();
		while (pos != NULL)
		{
			POSITION tmp = pos;
			Enemy * enemy = (Enemy*)enemyList.GetNext(pos);//����ѭ��
			if (enemy->GetPoint().x > m_client.left
				&&enemy->GetPoint().x < m_client.right
				&&enemy->GetPoint().y < 719
				&& enemy->GetPoint().y > 0)
			{
				if (enemy->enemyType == 0)
					enemy->SetPoint(enemy->GetPoint().x, enemy->GetPoint().y + 20);
				else
					enemy->SetPoint(enemy->GetPoint().x, enemy->GetPoint().y + 20);
				enemy->Draw(&m_cacheDC, TRUE);

				/***************�л������ӵ�******************/
				if (nIDEvent == 2)
				{
					EnemyBullet *enemy_bullet = new EnemyBullet(
						enemy->GetPoint().x + 108 / 2 - 15,
						enemy->GetPoint().y + 30);
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
				&&bullet->GetPoint().y < 719
				&& bullet->GetPoint().y > 0)
			{
				bullet->SetPoint(bullet->GetPoint().x, bullet->GetPoint().y - (bullet->PLANE_HEIGHT));
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
				&&bullet->GetPoint().y < 719
				&& bullet->GetPoint().y > 0)
			{
				bullet->SetPoint(bullet->GetPoint().x, bullet->GetPoint().y + bullet->PLANE_HEIGHT);
				bullet->Draw(&m_cacheDC, TRUE);
			}
			else{
				enemyBulletList.RemoveAt(tmp);
				delete bullet;
				break;
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
					life--;
					myPlane->SetPoint(1277 / 2 - myPlane->PLANE_WIDTH / 2, 719 - myPlane->PLANE_HEIGHT - 10);
					enemyList.RemoveAt(tmp);
					PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					start = FALSE;
					break;
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
					life--;
					myPlane->SetPoint(1277 / 2 - myPlane->PLANE_WIDTH / 2, 719 - myPlane->PLANE_HEIGHT - 10);
					start = FALSE;
					PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					break;
				}
			}
		}

		/*���ел�*/
		POSITION pos4 = myBulletList.GetHeadPosition();
		while (pos4 != NULL)
		{
			POSITION tmp1 = pos4;
			MyBullet *bullet = (MyBullet*)myBulletList.GetNext(pos4);

			POSITION enemy_pos = enemyList.GetHeadPosition();
			while (enemy_pos != NULL)
			{
				POSITION tmp2 = enemy_pos;
				Enemy *enemy = (Enemy*)enemyList.GetNext(enemy_pos);
				CRect r1 = enemy->GetRect();
				CRect r2 = bullet->GetRect();
				CRect t;
				if (t.IntersectRect(&r1, &r2))
				{
					enemyList.RemoveAt(tmp2);
					myBulletList.RemoveAt(tmp1);
					delete bullet;
					delete enemy;
					PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
					Score++;
				}
				break;
			}
		}//Tips:���ѭ���������ҷ��ӵ�

		if (bossMode)
		{
			if (boss == NULL)boss = new Boss(1277 / 2 - 180, 0);
			if (boss != NULL)
			{
				boss->Draw(&m_cacheDC, TRUE);
				switch (Stage)
				{
				case 1:{
					if (nIDEvent == 8)
					{
						EnemyBullet *bullet0 = new EnemyBullet(boss->GetPoint().x + 20, boss->GetPoint().y + 230);
						EnemyBullet *bullet1 = new EnemyBullet(boss->GetPoint().x + 100, boss->GetPoint().y + 230);
						EnemyBullet *bullet2 = new EnemyBullet(boss->GetPoint().x + 165, boss->GetPoint().y + 230);
						EnemyBullet *bullet3 = new EnemyBullet(boss->GetPoint().x + 220, boss->GetPoint().y + 230);
						EnemyBullet *bullet4 = new EnemyBullet(boss->GetPoint().x + 300, boss->GetPoint().y + 230);
						bossbullet0.AddTail(bullet0);
						bossbullet1.AddTail(bullet1);
						bossbullet2.AddTail(bullet2);
						bossbullet3.AddTail(bullet3);
						bossbullet4.AddTail(bullet4);
					}
					boss->bossBulletMove(&bossbullet0, -40, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet1, -20, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet2, 0, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet3, 20, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet4, 40, 30, &m_cacheDC);
					break;
				}
				case 2:{
					if (nIDEvent == 2)
					{
						EnemyBullet *bullet0 = new EnemyBullet(boss->GetPoint().x + 20, boss->GetPoint().y + 230);
						EnemyBullet *bullet1 = new EnemyBullet(boss->GetPoint().x + 100, boss->GetPoint().y + 230);
						EnemyBullet *bullet2 = new EnemyBullet(boss->GetPoint().x + 165, boss->GetPoint().y + 230);
						EnemyBullet *bullet3 = new EnemyBullet(boss->GetPoint().x + 220, boss->GetPoint().y + 230);
						EnemyBullet *bullet4 = new EnemyBullet(boss->GetPoint().x + 300, boss->GetPoint().y + 230);
						bullet0->type = 1;
						bullet1->type = 1;
						bullet2->type = 1;
						bullet3->type = 1;
						bullet4->type = 1;
						bossbullet0.AddTail(bullet0);
						bossbullet1.AddTail(bullet1);
						bossbullet2.AddTail(bullet2);
						bossbullet3.AddTail(bullet3);
						bossbullet4.AddTail(bullet4);
					}
					boss->bossBulletMove(&bossbullet0, -40, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet1, -20, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet2, 0, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet3, 20, 30, &m_cacheDC);
					boss->bossBulletMove(&bossbullet4, 40, 30, &m_cacheDC);
					break;
				}
				}
			}
			//��ײ���
			//boss�ӵ�
			boss->bossHitMe(&bossbullet0, myPlane, life);
			boss->bossHitMe(&bossbullet1, myPlane, life);
			boss->bossHitMe(&bossbullet2, myPlane, life);
			boss->bossHitMe(&bossbullet3, myPlane, life);
			boss->bossHitMe(&bossbullet4, myPlane, life);
			//boss��ײ
			if (boss->bossCrash(myPlane))life--;
			//
			POSITION _pos = myBulletList.GetHeadPosition();
			while (_pos != NULL)
			{
				POSITION tmp = _pos;
				MyBullet *bullet = (MyBullet*)myBulletList.GetNext(_pos);
				if (bossMode)
				{
					CRect r1 = boss->GetRect();
					CRect r2 = bullet->GetRect();
					CRect t;
					if (t.IntersectRect(&r1, &r2))
					{
						myBulletList.RemoveAt(tmp);
						delete bullet;
						PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
						boss->life--;
					}
				}
			}
			//boss�ƶ�
			if (bossMove)
			{
				boss->SetPoint(boss->GetPoint().x + 10 * bossDirect, boss->GetPoint().y);
				if (boss->GetPoint().x >= 800)
					bossDirect = -1;
				else if (boss->GetPoint().x <= 70)
					bossDirect = 1;
			}
			if (boss->life == 0){ bossMode = FALSE; Score += 100; }
		}

		HFONT font;
		font = CreateFont(30, 30, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		m_cacheDC.SelectObject(font);
		m_cacheDC.SetBkMode(TRANSPARENT);//�ı�͸��
		CString str;
		m_cacheDC.SetTextColor(RGB(0, 255, 0));
		str.Format(_T("�÷�:%d"), Score);
		m_cacheDC.TextOutW(10, 30, str);
		str.Format(_T("����:%d"), life);
		m_cacheDC.TextOutW(10, 60, str);
		if (bossMode)
		{
			str.Format(_T("bossѪ��:%d"), boss->life);
			m_cacheDC.TextOutW(10, 90, str);
		}
	}

	if (life <= 0){
		pause = 1;
		HFONT font1;
		font1 = CreateFont(80, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 10, 0);
		m_cacheDC.SelectObject(font1);
		m_cacheDC.SetBkMode(TRANSPARENT);//�ı�͸��
		CString str;
		m_cacheDC.SetTextColor(RGB(255, 255, 0));
		str.Format(_T("��Ϸ����"));
		m_cacheDC.TextOutW(300, 300, str);
		str.Format(_T("�÷�%d"), Score);
		m_cacheDC.TextOutW(300, 350, str);
		str.Format(_T("��R���¿�ʼ"));
		m_cacheDC.TextOutW(300, 400, str);
		str.Format(_T("��Q���¿�ʼ"));
		m_cacheDC.TextOutW(300, 450, str);
		if (GetKeyState('R') < 0)
		{
			myPlane->SetPoint(1277 / 2 - myPlane->PLANE_WIDTH / 2, 719 - myPlane->PLANE_HEIGHT - 10);
			life = 50;
			myBulletList.RemoveAll();
			enemyBulletList.RemoveAll();
			enemyList.RemoveAll();
			bossMode = 0;
			Score = 0;
			pause = 0;
		}
		else if (GetKeyState('Q') < 0)
		{
			exit(1);
		}
	}

	cDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cacheDC, 0, 0, SRCCOPY);//������ƵĴ���

	

	/*��������ѭ������*/
	if (CTop < 719)
	{
		CTop += 2;
		CBottom += 2;
	}
	else
	{
		CTop = 0;
		CBottom = 719;
	}
	m_cacheCBitmap.DeleteObject();//�ͷŻ���λͼ
	m_cacheDC.DeleteDC();//�ͷŻ���DC
	ReleaseDC(&m_cacheDC);
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
	MyBullet *bullet = new MyBullet(myPlane->GetPoint().x, myPlane->GetPoint().y);
	//bullet->Draw(&m_cacheDC, TRUE);
	myBulletList.AddTail(bullet);
	CWnd::OnLButtonDown(nFlags, point);
}
