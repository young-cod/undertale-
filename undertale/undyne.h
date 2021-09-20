#pragma once
#include "gameNode.h"
#include "player.h"


struct tagUndy
{
	RECT rc;
	Image* img;
	int currentFrameX;
	int currentFrameY;
	float x, y;
	float angle;
};

class undyne :
	public gameNode
{

private:
	int _count;

	tagUndy _fullbody; //얘는 일반스테이지에서
	player* _player;

public:
	 HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();



	RECT getRect() { return _fullbody.rc; }
	tagUndy getUndy() { return _fullbody; }
};

