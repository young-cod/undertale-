#pragma once
#include "gameNode.h"

class title : public gameNode
{
	Image* _backGround;

public :
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	title* getScene() { return this; }
};

