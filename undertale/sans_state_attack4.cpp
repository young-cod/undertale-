#include "stdafx.h"
#include "sans_state_attack4.h"

sans_state * sans_state_attack4::inputHandle(sansBattle * sansBattle)
{
	if (sansBattle->getUI()->getState() != INGAME)
	{
		return new sans_state_idle();

	}
	return nullptr;
}

void sans_state_attack4::enter(sansBattle * sansBattle)
{
	sansBattle->getUI()->setEnemy_attackTime_max(300);
	_bone_speed = 2.f;

	for (int i = 0; i < BONEMAX50; i++)
	{
		_bone_20[i].x = i * 20 - 1000;
		_bone_20[i].y = 380;
		_bone_20[i].width = 10;
		_bone_20[i].hieght = 20;
		_bone_20[i].rc = RectMakeCenter(_bone_20[i].x, _bone_20[i].y, _bone_20[i].width, _bone_20[i].hieght);
		_bone_20[i].img = IMAGEMANAGER->FindImage("ª¿¥Ÿ±Õ_20");

		_foothold[i].x = i * 200 - 1000;
		_foothold[i].y = 330;
		_foothold[i].width = 57;
		_foothold[i].hieght = 10;
		_foothold[i].rc = RectMakeCenter(_foothold[i].x, _foothold[i].y, _foothold[i].width, _foothold[i].hieght);
		_foothold[i].img = IMAGEMANAGER->FindImage("πﬂ∆«");
	}
}

void sans_state_attack4::update(sansBattle * sansBattle)
{
	heart_control(sansBattle, true, 0.3f, 10);
	sansBattle->getUI()->main_rect_control_customizing(true, 20, 360, 170);
	//¿Ãµø
	for (int i = 0; i < BONEMAX50; i++)
	{
		_bone_20[i].x += _bone_speed;
		_bone_20[i].rc = RectMakeCenter(_bone_20[i].x, _bone_20[i].y, _bone_20[i].width, _bone_20[i].hieght);

		_foothold[i].x += _bone_speed;
		_foothold[i].rc = RectMakeCenter(_foothold[i].x, _foothold[i].y, _foothold[i].width, _foothold[i].hieght);
	}
	//√Êµπ
	for (int i = 0; i < BONEMAX50; i++)
	{
		if (_foothold[i].rc.top < sansBattle->getUI()->getIGH().rc.bottom &&
			_foothold[i].rc.left < sansBattle->getUI()->getIGH().rc.right &&
			_foothold[i].rc.right > sansBattle->getUI()->getIGH().rc.left &&
			_foothold[i].rc.bottom > sansBattle->getUI()->getIGH().rc.bottom)
		{
			sansBattle->getUI()->set_inGame_heart_y(_foothold[i].rc.top -= (9 + 0.3f));
			_isJump = false;
		}
		else
		{
			sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->getIGH().y + 0.04f);
		}

	}
}

void sans_state_attack4::render(sansBattle * sansBattle)
{
	for (int i = 0; i < BONEMAX50; i++)
	{
		if (sansBattle->getUI()->get_main_rect().left < _bone_20[i].rc.right &&
			sansBattle->getUI()->get_main_rect().right > _bone_20[i].rc.left)
		{
			_bone_20[i].img->Render(_bone_20[i].x - _bone_20[i].width / 2, _bone_20[i].y - _bone_20[i].hieght / 2);
		}
		if (sansBattle->getUI()->get_main_rect().left < _foothold[i].rc.right &&
			sansBattle->getUI()->get_main_rect().right > _foothold[i].rc.left)
		{
			_foothold[i].img->Render(_foothold[i].x - _foothold[i].width / 2, _foothold[i].y - _foothold[i].hieght / 2);
		}
	}
}

void sans_state_attack4::exit(sansBattle * sansBattle)
{
}
