#pragma once
#include "gameNode.h"
#include <vector>
#include "battleUI.h"
#include "muffetStateBase.h"

struct  tagImage
{
	RECT rc;
	Image* img;
	float x, y;
	int currentFrameX;
	float angle;
	bool isFrameImage;
};
enum MUFFET
{
	HEAD,
	HAIR,
	EYE = 3,
	SHOULDER = 8,
	ARM = 10,
	BOTTOM_HAND = 14,
	BOTTOM_HAND_FIST = 16,
	TEAPORT = 18,
	LEG = 20,
	BODY
};
class muffetBattle : public gameNode
{
	tagImage _mfImage;
	//bullet* _bullet;
	battleUI* _btUI;

	vector<tagImage> _muffetV;

	Image* _muffet;
	muffetStateBase* _muffetState;

	int _currentFrameX, _currentFrameY;
	int _frameCount;

	bool _downMove;
	int _count;
	int i;

	int _downFixcel;

	//무적 시간 여부
	int _invincibility;
	bool _isInvin;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void inPutHandle();
	void addMuffetImage();
	void setImage();

	void collision();

	vector<tagImage> getMuffetImageV() { return _muffetV; }

	battleUI* getUI() { return _btUI; }
};

