#include "stdafx.h"
#include "sans_state_attack1.h"

sans_state * sans_state_attack1::inputHandle(sansBattle * sansBattle)
{
	if (sansBattle->getUI()->getState() != INGAME)
	{
		return new sans_state_idle();
	}
	return nullptr;
}

void sans_state_attack1::enter(sansBattle * sansBattle)
{
	sansBattle->getUI()->setEnemy_attackTime_max(300);
	_bone_speed = 2.f;
	for (int i = 0; i < BONEMAX / 2; i++)
	{
		_bone_20[i].x = i * 100 - 800;
		_bone_20[i].y = 380;
		_bone_20[i].width = 10;
		_bone_20[i].hieght = 20;
		_bone_20[i].rc = RectMakeCenter(_bone_20[i].x, _bone_20[i].y, _bone_20[i].width, _bone_20[i].hieght);

		_bone_20[i].img = IMAGEMANAGER->FindImage("»À´Ù±Í_20");

		_bone_100[i].x = i * 100 - 800;
		_bone_100[i].y = 280;
		_bone_100[i].width = 10;
		_bone_100[i].hieght = 100;
		_bone_100[i].rc = RectMakeCenter(_bone_100[i].x, _bone_100[i].y, _bone_100[i].width, _bone_100[i].hieght);

		_bone_100[i].img = IMAGEMANAGER->FindImage("»À´Ù±Í_100");

		_bone_20[i + BONEMAX / 2].x = (i + BONEMAX / 2) * 100 - 200;
		_bone_20[i + BONEMAX / 2].y = 380;
		_bone_20[i + BONEMAX / 2].width = 10;
		_bone_20[i + BONEMAX / 2].hieght = 20;
		_bone_20[i + BONEMAX / 2].rc = RectMakeCenter(_bone_20[i + BONEMAX / 2].x, _bone_20[i + BONEMAX / 2].y, _bone_20[i + BONEMAX / 2].width, _bone_20[i + BONEMAX / 2].hieght);

		_bone_20[i + BONEMAX / 2].img = IMAGEMANAGER->FindImage("»À´Ù±Í_20");

		_bone_100[i + BONEMAX / 2].x = (i + BONEMAX / 2) * 100 - 200;
		_bone_100[i + BONEMAX / 2].y = 280;
		_bone_100[i + BONEMAX / 2].width = 10;
		_bone_100[i + BONEMAX / 2].hieght = 100;
		_bone_100[i + BONEMAX / 2].rc = RectMakeCenter(_bone_100[i + BONEMAX / 2].x, _bone_100[i + BONEMAX / 2].y, _bone_100[i + BONEMAX / 2].width, _bone_100[i + BONEMAX / 2].hieght);

		_bone_100[i + BONEMAX / 2].img = IMAGEMANAGER->FindImage("»À´Ù±Í_100");
	}

}

void sans_state_attack1::update(sansBattle * sansBattle)
{
	/*for (int i = 0; i < BONEMAX / 2; i++) 
	{
		collision(sansBattle, _bone_20[i].rc);
	}*/
	
	heart_control(sansBattle, true, 0.45f, 6);
	sansBattle->getUI()->main_rect_control_customizing(true, 20, 400, 170);

	for (int i = 0; i < BONEMAX / 2; i++)
	{
		
		_bone_20[i].x += _bone_speed;
		_bone_20[i].rc = RectMakeCenter(_bone_20[i].x, _bone_20[i].y, _bone_20[i].width, _bone_20[i].hieght);
		_bone_100[i].x += _bone_speed;
		_bone_100[i].rc = RectMakeCenter(_bone_100[i].x, _bone_100[i].y, _bone_100[i].width, _bone_100[i].hieght);
		_bone_20[i + BONEMAX / 2].x -= _bone_speed;
		_bone_20[i + BONEMAX / 2].rc = RectMakeCenter(_bone_20[i + BONEMAX / 2].x, _bone_20[i + BONEMAX / 2].y, _bone_20[i + BONEMAX / 2].width, _bone_20[i + BONEMAX / 2].hieght);
		_bone_100[i + BONEMAX / 2].x -= _bone_speed;
		_bone_100[i + BONEMAX / 2].rc = RectMakeCenter(_bone_100[i + BONEMAX / 2].x, _bone_100[i + BONEMAX / 2].y, _bone_100[i + BONEMAX / 2].width, _bone_100[i + BONEMAX / 2].hieght);
	}
}

void sans_state_attack1::render(sansBattle * sansBattle)
{

	for (int i = 0; i < BONEMAX; i++)
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
	}
}

void sans_state_attack1::exit(sansBattle * sansBattle)
{
}
