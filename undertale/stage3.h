#pragma once
#include "gameNode.h"
#include "stageRect.h"
#include "player.h"

class stage3 : public gameNode
{
	stageRect* _setRect;

	Image* _backGround;

	player* _player;
	
	RECT _sceneRect;
	RECT _sceneRect2;

	bool _reStage;

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	stageRect* getStageRect() { return _setRect; }
	RECT getSceneRect() { return _sceneRect; }
	RECT getSceneRect2() { return _sceneRect2; }
};

