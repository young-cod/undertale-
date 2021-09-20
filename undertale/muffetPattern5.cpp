#include "stdafx.h"
#include "muffetPattern5.h"
#include "muffetBattle.h"
#include "muffetIdle.h"

muffetStateBase * muffetPattern5::inputHandle(muffetBattle * muffet)
{
	if (muffet->getUI()->getState() != INGAME)
	{
		return new muffetIdle();
	}
	return nullptr;
}

void muffetPattern5::update(muffetBattle * muffet)
{
	_fireRndNum = RND->getFromIntTo(0, 100);
	if (_fireRndNum >= 95)
	{
		if (_fireRndNum % 2 == 0) _way = true;
		else if (_fireRndNum % 2 == 1) _way = false;
		spiderBulletFire(muffet, _way);
	}

	if (_vBullet.size() != 0)
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (_vBullet[i].direction && i < 8) _vBullet[i].x += 5;
			if (!_vBullet[i].direction && i < 8) _vBullet[i].x -= 5;

			if (i >= 8)
			{
				if (_vBullet[i].direction)
				{
					_vBullet[i].x += cosf(_vBullet[i].angle) * 5;
					_vBullet[i].y += -sinf(_vBullet[i].angle) * 5;
				}
				else if (!_vBullet[i].direction)
				{
					_vBullet[i].x += cosf(_vBullet[i].angle) * 5;
					_vBullet[i].y += -sinf(_vBullet[i].angle) * 5;
				}

				if (_vBullet[i].rc.top < muffet->getUI()->get_main_rect().top) //렉트 위로 도넛이 나가면
				{
					_vBullet[i].angle = PI * 2 - _vBullet[i].angle;
					_vBullet[i].y += _vBullet[i].image->GetHeight() / 2;
				}
				else if (_vBullet[i].rc.bottom > muffet->getUI()->get_main_rect().bottom) //아래로 나가면
				{
					_vBullet[i].angle = PI * 2 - _vBullet[i].angle;
					_vBullet[i].y -= _vBullet[i].image->GetHeight() / 2;
				}
			}

			_vBullet[i].rc = RectMake(_vBullet[i].x, _vBullet[i].y, _vBullet[i].image->GetWidth(), _vBullet[i].image->GetHeight());
		}
	}

	for (int i = 0; i < 5; i++)
	{
		_startPoint[i].x = muffet->getUI()->get_main_rect().left + 10;
		_startPoint[i].y = ((muffet->getUI()->get_main_rect().bottom - muffet->getUI()->get_main_rect().top) / 4 + muffet->getUI()->get_main_rect().top) + 40 * i;

		_endPoint[i].x = muffet->getUI()->get_main_rect().right - 10;
		_endPoint[i].y = _startPoint[i].y;
	}
}

void muffetPattern5::enter(muffetBattle * muffet)
{
	_fireRndNum = 0;
	muffet->getUI()->setEnemy_attackTime_max(500);
	for (int i = 0; i < 5; i++)
	{
		_startPoint[i].x = muffet->getUI()->get_main_rect().left + 10;
		_startPoint[i].y = ((muffet->getUI()->get_main_rect().bottom - muffet->getUI()->get_main_rect().top) / 4 + muffet->getUI()->get_main_rect().top) + 40 * i;

		_endPoint[i].x = muffet->getUI()->get_main_rect().right - 10;
		_endPoint[i].y = _startPoint[i].y;
	}

	_way = false;
	_dounutCount = 0;

	muffet->getUI()->set_inGame_heart_y(_startPoint[2].y);
	muffet->getUI()->setEnemy_attackTime_max(700);
}

void muffetPattern5::render(muffetBattle * muffet)
{
	//시간마다 렉트 모양 변하도록
	if (muffet->getUI()->getEnemy_attackTime() <= 300) muffet->getUI()->main_rect_control_customizing(true, 5, 250, 150);
	else if (muffet->getUI()->getEnemy_attackTime() <= 350) muffet->getUI()->main_rect_control_customizing(true, 7, 400, 150);
	else if (muffet->getUI()->getEnemy_attackTime() > 350) muffet->getUI()->main_rect_control_customizing(true, 5, 250, 300);

	if (_vBullet.size() != 0)
	{
		for (int i = 0; i < _vBullet.size(); i++)
		{
			if (_vBullet[i].x <= 535 && _vBullet[i].x >= 135)
			{
				_vBullet[i].image->Render(_vBullet[i].x, _vBullet[i].y);
			}
			if (KEYMANAGER->isToggleKey(VK_F1))
			{
				D2DRENDER->DrawRectangle(_vBullet[i].rc, D2DRenderer::DefaultBrush::Red);
			}
		}
	}

	for (int i = 0; i < 5; i++)
	{
		if (_startPoint[i].y >= muffet->getUI()->get_main_rect().top &&
			_startPoint[i].y <= muffet->getUI()->get_main_rect().bottom)
		{
			D2DRENDER->DrawLine(_startPoint[i], _endPoint[i], D2DRenderer::DefaultBrush::Purple);
		}
	}
}

void muffetPattern5::exit(muffetBattle * muffet)
{
}

void muffetPattern5::spiderBulletFire(muffetBattle * muffet, bool way)
{
	if (_vBullet.size() < 10)
	{
		Bullet _spider;

		_spider.image = IMAGEMANAGER->FindImage("muffet_spider");
		if (way) _spider.x = 135;
		else _spider.x = 535;
		_spider.y = muffet->getUI()->getIGH().rc.top;
		_spider.rc = RectMake(_spider.x, _spider.y, _spider.image->GetWidth(), _spider.image->GetHeight());
		_spider.direction = _way;

		_vBullet.push_back(_spider);
	}
	//if (_vBullet.size())
	//else if (_vBullet.size() >= 8 && _dounutCount <= 2) //거미 7개 뿌리면 도넛 3개를 발사
	//{
	//	Bullet _dounut;

	//	_dounut.image = IMAGEMANAGER->FindImage("muffet_dounut");
	//	_dounut.x = 135;
	//	_dounut.y = 310;
	//	_dounut.rc = RectMake(_dounut.x, _dounut.y, _dounut.image->GetWidth(), _dounut.image->GetHeight());
	//	_dounut.direction = _way;
	//	if (way) _dounut.angle = 0.6;
	//	else _dounut.angle = 5.8;

	//	_vBullet.push_back(_dounut);
	//	_dounutCount++;
	//}
}
