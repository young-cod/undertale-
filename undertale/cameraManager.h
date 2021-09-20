#pragma once
#include "singletonBase.h"

struct tagCamera
{
	RECT rc;
	float width, height;
	float x, y;
};

struct tagMap
{
	RECT rc;
	float width, height;
	float x, y;
};



class cameraManager : public singletonBase<cameraManager>
{
private:
	tagCamera _camera;
	tagMap _map;

	float _x, _y;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void setMapCamera(float x, float y);
	void setPlayerCamera();


	//∏  ¡ﬂæ” ±‚¡ÿ
	void updateCamera(RECT& player, float playerX, float playerY);
	void updateCamera(float x, float y);
	void updateCameraH(float x, float y);

	//∏  ???? æÓµ ±‚¡ÿ
	void updateCamera(bool a);

	float getX() { return _x; }
	float getY() { return _y; }
	tagCamera getCameraInfo() { return _camera; }
	
	void mousePoint();
};

