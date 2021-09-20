#pragma once
#include "gameNode.h"

struct word
{
	char _change[128];
};

class dialouge : public gameNode
{
private:
	char* _str;
	int _test;

	struct word word;
	char num[64];
	char _change[128];

	int _num;
	int _count;
	int i;

public:
	dialouge();
	~dialouge();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


};


