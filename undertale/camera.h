#pragma once
#include "singletonBase.h"

struct tagCameraSize
{
	RECT   rc;
	float   width;
	float   height;
	float   x, y;
};

struct tagMapSize
{
	float   width;
	float   height;
};

class camera : public singletonBase<camera>
{
private:
	tagCameraSize   _camera;
	tagMapSize      _map;
	float _x,_y;

public:
	camera();
	~camera();

	HRESULT init();
	void   release();
	void   update();
	void   render();

	void cameraRange();

	// 본 이미지에 2배로 바꿔주기
	void	setImgCamera(float x, float y);
	//플레이어중심x,y 기준 
	void	setPlayerCamera(float& x, float& y);
	void	updateCamera(float x, float y);
	void	updateCamera(RECT& player);
	void	updateCamera(RECT& player,float ratio);
	void	updateCamera(RECT& player, float& x, float& y);
	void	updateCamera(RECT& player, float ratioX,float ratioY, float ratioX2,float ratioY2);

	tagCameraSize getCameraRect() { return _camera; }
	float getX() { return _x; };
	float getY() { return _y; }
};
