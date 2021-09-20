#include "stdafx.h"
#include "sans_state_attack6.h"

sans_state * sans_state_attack6::inputHandle(sansBattle * sansBattle)
{
	if (sansBattle->getUI()->getState() != INGAME)
	{
		return new sans_state_idle();
	}
	return nullptr;
}

void sans_state_attack6::enter(sansBattle * sansBattle)
{
	_count = 0;
	sansBattle->getUI()->setEnemy_attackTime_max(300);
	_bone_speed = 1.3f;

	for (int i = 0; i < BONEMAX / 4; i++)
	{
		_laser_body[i].angle = 0;
		_laser_body[i].x = 100;
		_laser_body[i].y = i * 60;
		_laser_body[i].width = 43;
		_laser_body[i].hieght = 57;
		_laser_body[i].rc = RectMakeCenter(_laser_body[i].x, _laser_body[i].y, _laser_body[i].width, _laser_body[i].hieght);
		_laser_body[i].img = IMAGEMANAGER->FindImage("레이저_바디");

		_laser_bim[i].angle = _laser_body[i].angle;
		_laser_bim[i].x = 1000;
		_laser_bim[i].y = 1000;
		_laser_bim[i].width = 10;
		_laser_bim[i].hieght = 15;
		_laser_bim[i].rc = RectMakeCenter(_laser_bim[i].x, _laser_bim[i].y, _laser_bim[i].width, _laser_bim[i].hieght);
	}
}

void sans_state_attack6::update(sansBattle * sansBattle)
{
	_count++;

	heart_control(sansBattle, false, 0, 5.f);
	sansBattle->getUI()->main_rect_control_customizing(true, 20, 170, 170);

	if (_count <= 100)
	{
		for (int i = 0; i < BONEMAX / 4; i++)
		{
			_laser_body[i].y += _bone_speed;
		}
	}
	else
	{
		for (int i = 0; i < BONEMAX / 4; i++)
		{
			_laser_body[i].angle += 5.f;

			if (_laser_body[i].angle >= 270)
			{
				_laser_body[i].angle = 270;
				_laser_bim[i].width += 10;
				_laser_bim[i].x = _laser_body[i].x;
				_laser_bim[i].y = _laser_body[i].y;

				if (_laser_bim[i].width >= 500)_laser_bim[i].width = 500;
				_laser_bim[i].rc = RectMake(_laser_bim[i].x + _laser_body[i].width, _laser_bim[i].y, _laser_bim[i].width, _laser_bim[i].hieght);
			}
		}
	}

}

void sans_state_attack6::render(sansBattle * sansBattle)
{
	for (int i = 0; i < BONEMAX / 4; i++)
	{
		D2DRENDER->FillRectangle(_laser_bim[i].rc, D2DRenderer::DefaultBrush::White);

		_laser_body[i].img->autoFrameRender(_laser_body[i].x + _laser_body->width / 2, _laser_body[i].y + _laser_body[i].hieght / 2, 5, 1, 100, false, 1, 1, _laser_body[i].angle);

	}
}

void sans_state_attack6::exit(sansBattle * sansBattle)
{

}
