#include "stdafx.h"
#include "sans_state_attack3.h"

sans_state * sans_state_attack3::inputHandle(sansBattle * sansBattle)
{
	if (sansBattle->getUI()->getState() != INGAME)
	{
		return new sans_state_idle();
	}

	return nullptr;
}

void sans_state_attack3::enter(sansBattle * sansBattle)
{

	sansBattle->getUI()->setEnemy_attackTime_max(300);
	_bone_speed = 2.f;
	for (int i = 0; i < BONEMAX / 2; i++)
	{
		_bone_20[i].x = i * 150 - 1300;
		_bone_20[i].y = 380;
		_bone_20[i].width = 10;
		_bone_20[i].hieght = 20;
		_bone_20[i].rc = RectMakeCenter(_bone_20[i].x, _bone_20[i].y, _bone_20[i].width, _bone_20[i].hieght);
		_bone_20[i].img = IMAGEMANAGER->FindImage("»À´Ù±Í_20");

		_bone_100[i].x = i * 150 - 1300;
		_bone_100[i].y = 280;
		_bone_100[i].width = 10;
		_bone_100[i].hieght = 100;
		_bone_100[i].rc = RectMakeCenter(_bone_100[i].x, _bone_100[i].y, _bone_100[i].width, _bone_100[i].hieght);
		_bone_100[i].img = IMAGEMANAGER->FindImage("»À´Ù±Í_100");

		_bone_40[i].x = i * 150 + 600;
		_bone_40[i].y = 240;
		_bone_40[i].width = 10;
		_bone_40[i].hieght = 20;
		_bone_40[i].rc = RectMakeCenter(_bone_40[i].x, _bone_40[i].y, _bone_40[i].width, _bone_40[i].hieght);
		_bone_40[i].img = IMAGEMANAGER->FindImage("»À´Ù±Í_40");

		_bone_50[i].x = i * 150 + 600;
		_bone_50[i].y = 350;
		_bone_50[i].width = 10;
		_bone_50[i].hieght = 20;
		_bone_50[i].rc = RectMakeCenter(_bone_50[i].x, _bone_50[i].y, _bone_50[i].width, _bone_50[i].hieght);
		_bone_50[i].img = IMAGEMANAGER->FindImage("»À´Ù±Í_50");
	}
}

void sans_state_attack3::update(sansBattle * sansBattle)
{
	heart_control(sansBattle, false, 0.45f, 6);
	sansBattle->getUI()->main_rect_control_customizing(true, 20, 360, 170);

	for (int i = 0; i < BONEMAX / 2; i++)
	{
		_bone_20[i].x += _bone_speed;
		_bone_20[i].rc = RectMakeCenter(_bone_20[i].x, _bone_20[i].y, _bone_20[i].width, _bone_20[i].hieght);
		_bone_100[i].x += _bone_speed;
		_bone_100[i].rc = RectMakeCenter(_bone_100[i].x, _bone_100[i].y, _bone_100[i].width, _bone_100[i].hieght);

		if (sansBattle->getUI()->getEnemy_attackTime_max() >= 250)
		{
			_bone_40[i].x -= _bone_speed;
			_bone_40[i].rc = RectMakeCenter(_bone_40[i].x, _bone_40[i].y, _bone_40[i].width, _bone_40[i].hieght);
			_bone_50[i].x -= _bone_speed;
			_bone_50[i].rc = RectMakeCenter(_bone_50[i].x, _bone_50[i].y, _bone_50[i].width, _bone_50[i].hieght);
		}
	}
}

void sans_state_attack3::render(sansBattle * sansBattle)
{
	for (int i = 0; i < BONEMAX / 2; i++)
	{
		if (sansBattle->getUI()->get_main_rect().left < _bone_20[i].rc.right &&
			sansBattle->getUI()->get_main_rect().right > _bone_20[i].rc.left)
		{
			_bone_20[i].img->Render(_bone_20[i].x - _bone_20[i].width / 2, _bone_20[i].y - _bone_20[i].hieght / 2);
		}
		if (sansBattle->getUI()->get_main_rect().left < _bone_100[i].rc.right &&
			sansBattle->getUI()->get_main_rect().right > _bone_100[i].rc.left)
		{
			_bone_100[i].img->Render(_bone_100[i].x - _bone_100[i].width / 2, _bone_100[i].y - _bone_100[i].hieght / 2);
		}
		if (sansBattle->getUI()->get_main_rect().left < _bone_40[i].rc.right &&
			sansBattle->getUI()->get_main_rect().right > _bone_40[i].rc.left)
		{
			_bone_40[i].img->Render(_bone_40[i].x - _bone_40[i].width / 2, _bone_40[i].y - _bone_40[i].hieght / 2);
		}
		if (sansBattle->getUI()->get_main_rect().left < _bone_50[i].rc.right &&
			sansBattle->getUI()->get_main_rect().right > _bone_50[i].rc.left)
		{
			_bone_50[i].img->Render(_bone_50[i].x - _bone_50[i].width / 2, _bone_50[i].y - _bone_50[i].hieght / 2);
		}



	}
}

void sans_state_attack3::exit(sansBattle * sansBattle)
{
}
