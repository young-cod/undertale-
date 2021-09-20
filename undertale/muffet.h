#pragma once
#include "gameNode.h"
class muffet : public gameNode
{
	RECT _mfRc;

	Image* _muffet;
	Image* _muffetFrame;

	int _fCount;
	int _currentFrameX;

	float _x, _y;

	float _angle;

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

