#pragma once
#include "muffetStateBase.h"
#include "gameNode.h"
#include <vector>

class muffetBattle;

struct purpleBullet
{
	Image* imag;
	float x, y;
	RECT rc;
};
class muffetPurple : public muffetStateBase, public gameNode
{
	string _stateName;

	Image* _imageName;
	int _count;
	int _currentFrameX, _currentFrameY;

	purpleBullet _bullet;
	vector<purpleBullet> _purpleBullet;
	vector<purpleBullet> _purpleBullet2;

	RECT _purple;
	float _purpleHeight;

	int i;
	POINT _startPoint[3];
	POINT _endPoint[3];

public:
	virtual muffetStateBase* inputHandle(muffetBattle* muffet);
	virtual void update(muffetBattle* muffet);
	virtual void enter(muffetBattle* muffet);
	virtual void render(muffetBattle* muffet);
	virtual void exit(muffetBattle* muffet);

	void bulletFrie();
};

