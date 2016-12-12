#include "stdafx.h"
#include "Scene.h"


Scene::Scene()
{
	image.Load(_T("./image/galaxy.bmp"));
	//imagePos = 400;
	imagePos = 0;
}

void Scene::DrawScene(CDC* pDC, CRect *client)
{
	//pDC->SetStretchBltMode(COLORONCOLOR);
	if (imagePos > client->bottom)
	{
		imagePos = 0;
	}
	int height = client->Height();
	client->bottom += imagePos;
	client->top = imagePos;
	image.StretchBlt(*pDC, *client, SRCCOPY);//»æÖÆÏÂ¶Ë
	client->bottom -= height;
	client->top -= height;
	image.StretchBlt(*pDC, *client, SRCCOPY);
}

int Scene::sceneMove()
{ 
	imagePos += 2; 
	return 1;
}

Scene::~Scene()
{
	if (!image.IsNull())image.Destroy();
}
