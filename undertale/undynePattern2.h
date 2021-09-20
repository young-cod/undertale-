#pragma once
#include "undyneState.h"
#include "undyneIdle.h"

class undybattle;

class undynePattern2 :public undyneState
{
private:
	float distance;
	
	float _accel;
public:
	virtual undyneState* inputHandle(undybattle* undybattle);
	virtual void update(undybattle* undybattle);
	virtual void enter(undybattle* undybattle);
	virtual void render(undybattle* undybattle);
	virtual void exit(undybattle* undybattle);

	void undybulletFire(undybattle* undybattle);
	void mindist(undybattle * undybattle);
};

