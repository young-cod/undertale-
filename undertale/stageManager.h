#pragma once
#include "gameNode.h"
#include "stageRect.h"
#include "title.h"
#include "startStage.h"
#include "stage2.h"
#include "stage3.h"
#include "stage4.h"
#include "stage5.h"
#include "stage6.h"
#include "stage7.h"
#include "undybattle.h"
#include "sansBattle.h"
#include "muffetBattle.h"

class player;

class stageManager : public gameNode
{
	player* _player;
	stageRect* _stageRect;


public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void linkPlayer(player* player) { _player = player; }
	void linkStageRect(stageRect* sr) { _stageRect = sr; }

	//초기 셋팅
	void sceneSet();
};

