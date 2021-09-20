#pragma once
#include "gameNode.h"
#include "battleUI.h"
#include "sans_state.h"



struct sansObject
{
	Image* img;
	RECT rc;
	float x, y;
	int width, hieght;
	int currentFrameX;
	int currentFrameY;
};
struct object
{
	bool _isattack;
	bool _isMove;

};

class sansBattle : public gameNode
{
private:
	battleUI* _ui;
	sans_state* _state;

	//========»÷Áî==========
	sansObject _sans_head;
	sansObject _sans_sweat;
	sansObject _sans_body;
	sansObject _sans_legs;
	sansObject _sans_attack;
	//======================

	object _info;


public:

	sansBattle();
	~sansBattle();


	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void collision();

	//UI get
	battleUI* getUI() { return _ui; }
	//info get set
	object& getObject() { return _info; }

	void InputHandle();
};

