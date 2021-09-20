#pragma once
#include "muffetStateBase.h"

class muffetBattle;

struct MiniSpider
{
	Image* image;
	float x, y;
	float speed;
	int count;
	int currentFrameX;
};
class muffetIdle :public muffetStateBase
{
	MiniSpider _minispider;
	MiniSpider _menuPan;

	Image* _menu;
	Image* _menu2;

	//battleUI* _ui;
public:
	virtual muffetStateBase* inputHandle(muffetBattle* muffet);
	virtual void update(muffetBattle* muffet);
	virtual void enter(muffetBattle* muffet);
	virtual void render(muffetBattle* muffet);
	virtual void exit(muffetBattle* muffet);
};

