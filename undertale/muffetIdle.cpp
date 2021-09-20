#include "stdafx.h"
#include "muffetIdle.h"
#include "muffetBattle.h"
#include "muffetPurple.h"
#include "muffetPattern1.h"
#include "muffetPattern2.h"
#include "muffetPattern3.h"
#include "muffetPattern4.h"
#include "muffetPattern5.h"

muffetStateBase * muffetIdle::inputHandle(muffetBattle * muffet)
{
	battleUI* ui = muffet->getUI();
	if (ui->getState() == INGAME)
	{
		muffet->getUI()->set_inGame_heart_y(muffet->getUI()->get_main_rect().bottom + muffet->getUI()->get_main_rect().top / 2);

		if (ui->getBattle_turn() == 0)
		{
			//return new muffetPattern5();
		}
		if (ui->getBattle_turn() == 1)
		{
			return new muffetPurple();
		}
		if (ui->getBattle_turn() == 2)
		{
			return new muffetPattern1();
		}
		if (ui->getBattle_turn() == 3)
		{
			return new muffetPattern2();
		}
		if (ui->getBattle_turn() == 4)
		{
			return new muffetPattern3();
		}
		if (ui->getBattle_turn() == 5)
		{
			return new muffetPattern4();
		}
		if (ui->getBattle_turn() == 6)
		{
			return new muffetPattern5();
		}
	}

	return nullptr;
}

void muffetIdle::update(muffetBattle * muffet)
{
	if (_minispider.x <= 220) _minispider.x += _minispider.speed;
	if (_minispider.x >= 220)
	{
		_menuPan.image = IMAGEMANAGER->FindImage("muffet_next_open");
		_menuPan.x = _minispider.x - _menuPan.image->GetFrameWidth() / 2;
		_menuPan.y = _minispider.y - _menuPan.image->GetFrameHeight();
		_menuPan.currentFrameX = 0;
		_menuPan.count = 0;
	}
}

void muffetIdle::enter(muffetBattle * muffet)
{
	battleUI* ui = muffet->getUI();
	if (ui->get_bubble_talk_count() >= 2 && ui->get_bubble_talk_count() <= 4)
	{
		_menu = IMAGEMANAGER->FindImage("muffet_spider");
	}
	if (ui->get_bubble_talk_count() == 5)
	{
		_menu = IMAGEMANAGER->FindImage("muffet_spider");
		_menu2 = IMAGEMANAGER->FindImage("muffet_dounut");
	}
	_minispider.image = IMAGEMANAGER->FindImage("muffet_spider_move");
	_minispider.x = 0;
	_minispider.y = 175;
	_minispider.currentFrameX = 0;
	_minispider.count = 0;
	_minispider.speed = 7;
}

void muffetIdle::render(muffetBattle * muffet)
{
	battleUI* ui = muffet->getUI();
	if (ui->get_bubble_talk_count() >= 2) _minispider.image->autoFrameRender(_minispider.x, _minispider.y, _minispider.currentFrameX, 0);
	if (ui->get_bubble_talk_count() >= 2 && _minispider.x >= 220)
	{
		_menuPan.image->autoFrameRender(_menuPan.x, _menuPan.y, _menuPan.currentFrameX, 0, 10, false);
		//_menu->Render(_menuPan.x, _menuPan.y);
		//if (ui->getBattle_turn() == 5) _menu2->Render(_menuPan.x + _menu->GetWidth(), _menuPan.y + _menu->GetHeight());
	}

}

void muffetIdle::exit(muffetBattle * muffet)
{
}
