#pragma once
#include "sans_state.h"
#include "sansBattle.h"
#include "sans_state_idle.h"

class sans_state_attack6 :	public sans_state
{

private:

	int _count;

public:

	virtual sans_state* inputHandle(sansBattle* sansBattle);
	virtual void enter(sansBattle* sansBattle);
	virtual void update(sansBattle* sansBattle);
	virtual void render(sansBattle* sansBattle);
	virtual void exit(sansBattle* sansBattle);
};

