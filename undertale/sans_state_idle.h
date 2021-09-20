#pragma once
#include "sans_state.h"
#include "sansBattle.h"

class sansBattle;

class sans_state_idle : public sans_state
{

public:
	virtual sans_state* inputHandle(sansBattle* sansBattle);
	virtual void enter(sansBattle* sansBattle);
	virtual void update(sansBattle* sansBattle);
	virtual void render(sansBattle* sansBattle);
	virtual void exit(sansBattle* sansBattle);
};

