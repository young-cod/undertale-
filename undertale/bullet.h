#pragma once
#include "gameNode.h"
#include <vector>


class bullet :	public gameNode
{
private:
	

	
public:

	bullet() {};
	~bullet() {};

	HRESULT init( int bulletMax, float range);
	void release();
	void update();
	void render();

	void fire(const char* imageName, float fireX, float fireY);
	void move();

	void removeBullet();
};

