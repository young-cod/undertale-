#pragma once
#include "muffetStateBase.h"
#include <vector>

class muffetBattle;

struct spiderBullet
{
	Image* image;
	float x, y;
	RECT rc;
};
class muffetPattern1 : public muffetStateBase
{
	Bullet _spider;

	int _fireRndNum;

	bool increase;

public:
	virtual muffetStateBase* inputHandle(muffetBattle* muffet);
	virtual void update(muffetBattle* muffet);
	virtual void enter(muffetBattle* muffet);
	virtual void render(muffetBattle* muffet);
	virtual void exit(muffetBattle* muffet);

	void spiderBulletFire(muffetBattle * muffet);
};

