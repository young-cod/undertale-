#pragma once
#include "gameNode.h"
#include "stageRect.h"
#include "player.h"

class stage6 :public gameNode
{
	stageRect* _setRect;

	Image* _backGround;

	RECT _sceneRect;

	player* _player;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	stageRect* getStageRect() { return _setRect; }
	RECT getSceneRect() { return _sceneRect; }
};

