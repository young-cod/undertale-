#pragma once
#include "muffetStateBase.h"
#include <vector>

class muffetBattle;

class muffetPattern3 : public muffetStateBase
{
	Bullet _spider;

	POINT _startPoint[3];
	POINT _endPoint[3];

	int _fireRndNum;

	bool _way;

public:
	virtual muffetStateBase* inputHandle(muffetBattle* muffet);
	virtual void update(muffetBattle* muffet);
	virtual void enter(muffetBattle* muffet);
	virtual void render(muffetBattle* muffet);
	virtual void exit(muffetBattle* muffet);

	void spiderBulletFire(muffetBattle * muffet, bool way);
};

