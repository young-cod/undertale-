#include "stdafx.h"
#include "muffetPurple.h"
#include "muffetBattle.h"
#include "muffetIdle.h"

muffetStateBase * muffetPurple::inputHandle(muffetBattle * muffet)
{
	if (muffet->getUI()->getState() != INGAME)
	{
		return new muffetIdle();
	}
	return nullptr;
}

void muffetPurple::update(muffetBattle * muffet)
{
	_count++;

	for (int i = 0; i < _purpleBullet.size(); i++)
	{
		if (_count % 3 == 0)
		{
			_purpleBullet[i].y += 10;
			_purpleBullet2[i].y += 10;
		}
	}
	if (_purple.bottom - _purple.top <
		muffet->getUI()->get_main_rect().bottom - muffet->getUI()->get_main_rect().top && _purpleHeight > 0)
	{
		if (_count % 30 == 0)
		{
			bulletFrie();
			if (_purpleBullet.size() >= 5) _purpleHeight += 15;
			_count = 0;
		}
	}
	else if (_purple.bottom - _purple.top >=
		muffet->getUI()->get_main_rect().bottom - muffet->getUI()->get_main_rect().top)
	{
		_purpleHeight = 0;
	}

	_purple = RectMake(muffet->getUI()->get_main_rect().left, muffet->getUI()->get_main_rect().bottom - _purpleHeight,
		muffet->getUI()->get_main_rect().right - muffet->getUI()->get_main_rect().left, _purpleHeight);
}

void muffetPurple::enter(muffetBattle * muffet)
{
	_stateName = "changePurple";
	_count = 0;
	_purpleHeight = 1;

	//보라색으로 채워지는 연출용 렉트
	_purple = RectMake(muffet->getUI()->get_main_rect().left, muffet->getUI()->get_main_rect().bottom,
		muffet->getUI()->get_main_rect().right - muffet->getUI()->get_main_rect().left, _purpleHeight);

	//렉트의 4등분한 곳에 줄을 그어준다.
	for (int i = 0; i < 3; i++)
	{
		_startPoint[i].x = muffet->getUI()->get_main_rect().left + 10;
		_startPoint[i].y = ((muffet->getUI()->get_main_rect().bottom - muffet->getUI()->get_main_rect().top) / 4 + muffet->getUI()->get_main_rect().top) + 40 * i;

		_endPoint[i].x = muffet->getUI()->get_main_rect().right - 10;
		_endPoint[i].y = _startPoint[i].y;
	}
	muffet->getUI()->set_inGame_heart_y(_startPoint[2].y);
	muffet->getUI()->setEnemy_attackTime_max(500);
	i = 0;
}

void muffetPurple::render(muffetBattle * muffet)
{
	for (int i = 0; i < _purpleBullet.size(); i++)
	{
		if (_purpleBullet[i].y <= muffet->getUI()->get_main_rect().bottom - 20) _purpleBullet[i].imag->Render(_purpleBullet[i].x, _purpleBullet[i].y);
		if (_purpleBullet2[i].y <= muffet->getUI()->get_main_rect().bottom - 20) _purpleBullet2[i].imag->Render(_purpleBullet2[i].x, _purpleBullet2[i].y);
	}

	D2DRENDER->FillRectangle(_purple, D2DRenderer::DefaultBrush::Purple);

	if (_purpleHeight == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			D2DRENDER->DrawLine(_startPoint[i], _endPoint[i], D2DRenderer::DefaultBrush::Purple);
		}
	}
}

void muffetPurple::exit(muffetBattle * muffet)
{
}

void muffetPurple::bulletFrie()
{
	if (_purpleBullet.size() <= 8)
	{
		purpleBullet _bullet;
		_bullet.imag = ImageManager::GetInstance()->FindImage("muffet_puple");
		_bullet.x = 260;
		_bullet.y = 130;

		_purpleBullet.push_back(_bullet);

		purpleBullet _bullet2;
		_bullet2.imag = ImageManager::GetInstance()->FindImage("muffet_puple");
		_bullet2.x = 370;
		_bullet2.y = 130;

		_purpleBullet2.push_back(_bullet2);
	}
}
