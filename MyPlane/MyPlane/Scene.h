#pragma once
class Scene
{
private:
	CImage image;
	int imagePos;
public:
	Scene();
	~Scene();
	void DrawScene(CDC* pDC, CRect *client);
	int sceneMove();
};

