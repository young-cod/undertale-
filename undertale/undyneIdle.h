#pragma once
#include "undyneState.h"
#include "undybattle.h"

class undybattle;

class undyneIdle : public undyneState
{

public:
	virtual undyneState* inputHandle(undybattle* undybattle);
	virtual void enter(undybattle* undybattle);
	virtual void update(undybattle* undybattle);
	virtual void render(undybattle* undybattle);
	virtual void exit(undybattle* undybattle);
};

