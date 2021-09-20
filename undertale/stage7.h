#pragma once
#include "gameNode.h"
#include "stageRect.h"
#include "player.h"

struct end_sans
{
	RECT rc;
	Image* img;
	float x, y;
	string name;
	int currentFrame;
};

class stage7 : public gameNode
{
	stageRect* _setRect;

	Image* _backGround;
	player* _player;
	end_sans _end;
	int _count;

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	stageRect* getStageRect() { return _setRect; }
};

