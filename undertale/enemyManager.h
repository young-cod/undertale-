#pragma once
#include "gameNode.h"

#include "muffet.h"

class enemyManager : public gameNode
{

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setAsriel();
	
};

