#pragma once
#include "gameNode.h"
#include "stageRect.h"
#include "player.h"

class startStage : public gameNode
{
	stageRect* _setRect;
	Image* _backGround;
	player* _player;

	RECT _sceneRect;



public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	stageRect* getStageRect() { return _setRect; }
	RECT getSceneRect() { return _sceneRect; }

	startStage* getScene() { return this; }

	player* getPlayer() { return _player; }

};

