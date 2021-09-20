#pragma once
#include "gameNode.h"
#include "stageRect.h"
#include "player.h"

class stage4 : public gameNode
{
	stageRect* _setRect;

	Image* _backGround;

	RECT _sceneRect;
	RECT _sceneRect2;

	player* _player;


	bool _shopRe;

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	stageRect* getStageRect() { return _setRect; }
	RECT getSceneRect() { return _sceneRect; }
	RECT getSceneRect2() { return _sceneRect2; }


};

