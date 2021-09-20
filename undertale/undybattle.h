#pragma once
#include "gameNode.h"
#include "battleUI.h"
#include <vector>
#include "bullet.h"
#include "undyneState.h"

struct tagUndyne
{
	RECT rc;
	RECT janSang;
	Image* img;
	int currentFrameX;
	int currentFrameY;
	float x, y;
	float angle;
	bool isMove;
	bool isAttack;
};
struct background
{
	RECT rc;
	Image* img;
	int currentFrameX;
	int currentFrameY;
	float x, y;
	bool isMove;
};

struct shieldLine
{
	float x, y;
	float length;
	float angle;
	POINT lineCenter;
	POINT lineEnd;
};

class undybattle :
	public gameNode
{
private:
	int _count = 0;
	tagUndyne _head;
	tagUndyne _hair;
	tagUndyne _torso;
	tagUndyne _leftArm;
	tagUndyne _rightArm;
	tagUndyne _belly;
	tagUndyne _legs; //여기까진 배틀씬에서..
	Image* _jansang;
	bullet* _bullet;
	undyneState* _undyState;
	shieldLine _shieldLine;
	RECT rc_shield;

	battleUI* _bui;
	int currentFrameX;
	int currentFrameY;

	int _timer;
	float angle;
	bool maxangle;
	bool minangle;
	bool up;

	vector<background>			 _vBack;
	vector<background>::iterator _viBack;
	
	vector<bullet*>		_vBullet;
	vector<bullet*>::iterator _viBullet;

public:

	HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void inputHandle();

	
	RECT getShieldRECT() { return rc_shield; }

	battleUI* getUI() { return _bui; }

	vector<background> getVback() { return _vBack; }
	vector<background>::iterator getViback() { return _viBack; }

	vector<bullet*> getVbullet() { return _vBullet; }
	vector<bullet*>::iterator getVIbullet() { return _viBullet; }
};

