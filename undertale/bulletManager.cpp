#include "stdafx.h"
#include "bulletManager.h"
#include "player.h"
#include"undybattle.h"

HRESULT bulletManager::init(const char* imageName, int bulletMax, float range)
{
	_img = IMAGEMANAGER->FindImage(imageName);
	_bulletMax = bulletMax;
	_range = range;

	return S_OK;
}

void bulletManager::release()
{
}

void bulletManager::update()
{
	move();
}

void bulletManager::render()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end(); ++_viBullet)
	{
		if (!_viBullet->isFire)return;
		float degree = _viBullet->angle * 57.3;
		//cout << degree << endl;
		_viBullet->img->bulletRender(_viBullet->rc.left, _viBullet->rc.top, degree);
		D2DRENDER->DrawRectangle
		(
			_viBullet->rc,
			D2DRenderer::DefaultBrush::Red
		);
	}
}

void bulletManager::move()
{
	for (_viBullet = _vBullet.begin(); _viBullet != _vBullet.end();)
	{
		if (!_viBullet->isFire)return;
		_viBullet->x += cosf(_viBullet->angle) * _viBullet->speed;
		_viBullet->y += -sinf(_viBullet->angle) * _viBullet->speed;

		_viBullet->rc = RectMakeCenter(_viBullet->x, _viBullet->y,
			_viBullet->img->GetFrameWidth(), _viBullet->img->GetFrameHeight());

		//사거리 넘게 날아가면 소멸
		if (_range < GetDistance(_viBullet->x, _viBullet->y, _viBullet->fireX, _viBullet->fireY))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		//플레이어와 닿으면 소멸
		if (IsCollision(_viBullet->rc, _undybattle->getUI()->getIGH().rc)|| IsCollision(_viBullet->rc,_undybattle->getShieldRECT()))
		{
			_viBullet = _vBullet.erase(_viBullet);
		}
		else ++_viBullet;
	}

}


void bulletManager::fire(float fireX, float fireY, float angle)
{
	tagBullet newBullet;
	ZeroMemory(&newBullet, sizeof(tagBullet));
	newBullet.img = _img;
	newBullet.x = newBullet.fireX = fireX;
	newBullet.y = newBullet.fireY = fireY;
	newBullet.angle = angle;
	newBullet.damage = 1;
	newBullet.speed = 10.f;
	newBullet.isFire = true;
	newBullet.rc = RectMakeCenter(fireX, fireY, newBullet.img->GetFrameWidth(), newBullet.img->GetFrameHeight());

	_vBullet.push_back(newBullet);
}