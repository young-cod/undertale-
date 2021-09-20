#include "stdafx.h"
#include "muffetPattern1.h"
#include "muffetBattle.h"
#include "muffetIdle.h"

muffetStateBase * muffetPattern1::inputHandle(muffetBattle * muffet)
{
	if (muffet->getUI()->getState() != INGAME)
	{
		return new muffetIdle();
	}
	return nullptr;
}

void muffetPattern1::update(muffetBattle * muffet)
{
	_fireRndNum = RND->getFromIntTo(0, 100);
	if (_fireRndNum >= 95) spiderBulletFire(muffet);

	if (_vBullet.size() != 0)
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			_vBullet[i].x -= 5;
			_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y, _vBullet[i].image->GetWidth(), _vBullet[i].image->GetHeight());
		}
	}
	for (int i = 0; i < 3; i++)
	{
		_startPoint[i].x = muffet->getUI()->get_main_rect().left + 10;
		_startPoint[i].y = ((muffet->getUI()->get_main_rect().bottom - muffet->getUI()->get_main_rect().top) / 4 + muffet->getUI()->get_main_rect().top) + 40 * i;

		_endPoint[i].x = muffet->getUI()->get_main_rect().right - 10;
		_endPoint[i].y = _startPoint[i].y;
	}
}

void muffetPattern1::enter(muffetBattle * muffet)
{

	_fireRndNum = 0;
	muffet->getUI()->setEnemy_attackTime_max(500);
	for (int i = 0; i < 3; i++)
	{
		_startPoint[i].x = muffet->getUI()->get_main_rect().left + 10;
		_startPoint[i].y = ((muffet->getUI()->get_main_rect().bottom - muffet->getUI()->get_main_rect().top) / 4 + muffet->getUI()->get_main_rect().top) + 40 * i;

		_endPoint[i].x = muffet->getUI()->get_main_rect().right - 10;
		_endPoint[i].y = _startPoint[i].y;
	}

	increase = false;

	muffet->getUI()->set_inGame_heart_y(_startPoint[2].y);
	muffet->getUI()->setEnemy_attackTime_max(500);
}

void muffetPattern1::render(muffetBattle * muffet)
{
	muffet->getUI()->main_rect_control_customizing(true, 5, 250, 150);

	if (_vBullet.size() != 0)
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (_vBullet[i].x >= 135)
			{
				_vBullet[i].image->Render(_vBullet[i].x, _vBullet[i].y);
				if (KEYMANAGER->isToggleKey(VK_F1))
				{
					D2DRENDER->DrawRectangle(_vBullet[i].rc, D2DRenderer::DefaultBrush::Red);
				}
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		D2DRENDER->DrawLine(_startPoint[i], _endPoint[i], D2DRenderer::DefaultBrush::Purple);
	}

}

void muffetPattern1::exit(muffetBattle * muffet)
{
}

void muffetPattern1::spiderBulletFire(muffetBattle * muffet)
{
	Bullet _spider;
	_spider.image = IMAGEMANAGER->FindImage("muffet_spider");
	_spider.x = 535;
	_spider.y = muffet->getUI()->getIGH().rc.top;
	_spider.rc = RectMake(_spider.x, _spider.y, _spider.image->GetWidth(), _spider.image->GetHeight());

	_vBullet.push_back(_spider);
}
