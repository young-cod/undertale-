#include "stdafx.h"
#include "bullet.h"

HRESULT bullet::init( int bulletMax, float range)
{

	//_bulletMax = bulletMax;
	//_range = range;

	return S_OK;
}

void bullet::release()
{

}

void bullet::update()
{
	move();
}

void bullet::render()
{
}

void bullet::fire(const char* imageName, float fireX,float fireY)
{
	/*if (_bulletMax < _vBullet.size())return;

	tagBullet newbullet;
	ZeroMemory(&newbullet, sizeof(tagBullet));
	newbullet.img = IMAGEMANAGER->FindImage(imageName);
	newbullet.x = newbullet.fireX = fireX;
	newbullet.y = newbullet.fireY = fireY;
	newbullet.rc = RectMakeCenter(fireX, fireY, 0, 0);
	newbullet.isFire = true;
	newbullet.speed = 10.0f;
	newbullet.angle = angle;
	_vBullet.push_back(newbullet);*/
}

void bullet::move()
{

}

void bullet::removeBullet()
{

}
