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

	// �� �̹����� 2��� �ٲ��ֱ�
	void	setImgCamera(float x, float y);
	//�÷��̾��߽�x,y ���� 
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
