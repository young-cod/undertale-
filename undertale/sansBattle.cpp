#include "stdafx.h"
#include "sansBattle.h"
#include "sans_state_idle.h"

sansBattle::sansBattle()
{
}

sansBattle::~sansBattle()
{
}



HRESULT sansBattle::init()
{

	_state = new sans_state_idle();
	_state->enter(this);
	_state->linkSans(this);

	_ui = new battleUI;
	_ui->init(1);

	IMAGEMANAGER->AddFrameImage("����_�Ӹ�", L"�����̹���/����_head_32_30_17.png", 17, 1);
	IMAGEMANAGER->AddFrameImage("����_��", L"�����̹���/����_sweat_32_9_3.png", 3, 1);
	IMAGEMANAGER->AddFrameImage("����_��", L"�����̹���/����_body_72_35_8.png", 8, 1);
	IMAGEMANAGER->AddFrameImage("����_�ٸ�", L"�����̹���/����_legs_52_23_2.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("����_�Ʒ�����", L"�����̹���/����_attackDown_62_73_5.png", 5, 1);
	IMAGEMANAGER->AddFrameImage("����_������", L"�����̹���/����_attackUp_62_73_5.png", 5, 1);
	IMAGEMANAGER->AddFrameImage("����_�����ʰ���", L"�����̹���/����_attackRight_97_48_6.png", 6, 1);
	IMAGEMANAGER->AddFrameImage("����_���ʰ���", L"�����̹���/����_attackLeft_97_48_6.png", 6, 1);
	IMAGEMANAGER->AddFrameImage("������_�ٵ�", L"�����̹���/����_laser_43_57_6.png", 6, 1);
	IMAGEMANAGER->AddImage("���ٱ�_20", L"�����̹���/���ٱ�_10_20.png");
	IMAGEMANAGER->AddImage("���ٱ�_40", L"�����̹���/���ٱ�_10_40.png");
	IMAGEMANAGER->AddImage("���ٱ�_50", L"�����̹���/���ٱ�_10_50.png");
	IMAGEMANAGER->AddImage("���ٱ�_100", L"�����̹���/���ٱ�_10_100.png");
	IMAGEMANAGER->AddImage("���ٱ�2_100", L"�����̹���/���ٱ�_blue_10_100.png");
	IMAGEMANAGER->AddImage("����", L"�����̹���/����_57_10.png");

	_sans_head.x = 320;
	_sans_head.y = 120;
	_sans_head.width = 32;
	_sans_head.hieght = 30;
	_sans_head.currentFrameX = 4;
	_sans_head.currentFrameY = 0;
	_sans_head.rc = RectMakeCenter(_sans_head.x, _sans_head.y, _sans_head.width, _sans_head.hieght);

	/*_sans_sweat.x = 290;
	_sans_sweat.y = 120;
	_sans_sweat.width = 32;
	_sans_sweat.hieght = 30;
	_sans_sweat.currentFrameX = 0;
	_sans_sweat.currentFrameY = 0;
	_sans_sweat.rc = RectMakeCenter(_sans_sweat.x, _sans_sweat.y, _sans_sweat.width, _sans_sweat.hieght);*/

	_sans_body.x = 320;
	_sans_body.y = 150;
	_sans_body.width = 72;
	_sans_body.hieght = 35;
	_sans_body.currentFrameX = 0;
	_sans_body.currentFrameY = 0;
	_sans_body.rc = RectMakeCenter(_sans_body.x, _sans_body.y, _sans_body.width, _sans_body.hieght);

	_sans_legs.x = 320;
	_sans_legs.y = 170;
	_sans_legs.width = 52;
	_sans_legs.hieght = 23;
	_sans_legs.currentFrameX = 0;
	_sans_legs.currentFrameY = 0;
	_sans_legs.rc = RectMakeCenter(_sans_legs.x, _sans_legs.y, _sans_legs.width, _sans_legs.hieght);

	_sans_attack.x = 291;
	_sans_attack.y = 111;
	_sans_attack.width = 62;
	_sans_attack.hieght = 73;
	_sans_attack.currentFrameX = 0;
	_sans_attack.currentFrameY = 0;
	_sans_attack.rc = RectMake(_sans_attack.x, _sans_attack.y, _sans_attack.width, _sans_attack.hieght);

	_sans_head.img = IMAGEMANAGER->FindImage("����_�Ӹ�");
	_sans_sweat.img = IMAGEMANAGER->FindImage("����_��");
	_sans_body.img = IMAGEMANAGER->FindImage("����_��");
	_sans_legs.img = IMAGEMANAGER->FindImage("����_�ٸ�");
	_sans_attack.img = IMAGEMANAGER->FindImage("����_�Ʒ�����");


	_info._isattack = false;
	_info._isMove = false;

	return S_OK;
}

void sansBattle::release()
{
}

void sansBattle::update()
{
	collision();
	InputHandle();
	_state->update(this);
	//��ǳ�� ��� ī��Ʈ �Ӹ� ��ü
	if (_ui->get_bubble_talk_count() < 4) _sans_head.currentFrameX = 4;
	else if (_ui->get_bubble_talk_count() == 4) _sans_head.currentFrameX = 5;
	else _sans_head.currentFrameX = 0;

	//��ǳ�� ��� ī��Ʈ �� ��ü
	if (_ui->get_bubble_talk_count() == 6)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 11)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 21)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 26)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 37)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 47)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 60)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 69)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 84)_sans_body.currentFrameX = 1;
	else if(_ui->get_bubble_talk_count() == 101)_sans_body.currentFrameX = 1;
	else _sans_body.currentFrameX = 0;

	//���ӻ��°� �ΰ����϶�
	if (_ui->getState() == INGAME || _ui->getState() == TALK_BUBBLE && _ui->get_bubble_talk_count() > 4 ||
		_ui->getState() == TALK_MAIN || _ui->getState() == MENU_SELECT)
	{
		
		if (!_info._isMove)
		{
			_sans_head.x += 0.1f;
			_sans_head.y += 0.2f;
			_sans_body.x += 0.05f;
			_sans_body.y += 0.15f;
			if (_sans_head.y >= 122) _info._isMove = true;
		}
		if (_info._isMove)
		{
			_sans_head.x -= 0.1f;
			_sans_head.y -= 0.2f;
			_sans_body.x -= 0.05f;
			_sans_body.y -= 0.15f;
			if (_sans_head.y <= 119) _info._isMove = false;
		}
	}

	_sans_head.rc = RectMakeCenter(_sans_head.x, _sans_head.y, _sans_head.width, _sans_head.hieght);
	_sans_body.rc = RectMakeCenter(_sans_body.x, _sans_body.y, _sans_body.width, _sans_body.hieght);
	_sans_legs.rc = RectMakeCenter(_sans_legs.x, _sans_legs.y, _sans_legs.width, _sans_legs.hieght);
	_sans_attack.rc = RectMake(_sans_attack.x, _sans_attack.y, _sans_attack.width, _sans_attack.hieght);


	_ui->update();
}

void sansBattle::render()
{
	_state->render(this);

	if (!_info._isattack)
	{
		_sans_body.img->bossFrameRender(_sans_body.rc.left, _sans_body.rc.top, _sans_body.currentFrameX, _sans_body.currentFrameY);
		_sans_legs.img->bossFrameRender(_sans_legs.rc.left, _sans_legs.rc.top, _sans_legs.currentFrameX, _sans_legs.currentFrameY);
	}

	if (_info._isattack)
	{
		_sans_attack.img->autoFrameRender(_sans_attack.rc.left, _sans_attack.rc.top, 0, 0, 10, false);
	}
	_sans_head.img->bossFrameRender(_sans_head.rc.left, _sans_head.rc.top, _sans_head.currentFrameX, _sans_head.currentFrameY);

	_ui->render();
}
//�浹 ó��, ü�� ����
void sansBattle::collision()
{
	for (int i = 0; i < BONEMAX50; i++) 
	{
		if (IsCollision(_state->get_bone_20(i).rc, _ui->getIGH().rc) && !_state->get_bone_20(i).isColision)
		{
			_ui->set_inGame_heart_currentHp(_ui->getIGH().currentHP - 5);
			_state->set_bone_20(i, true);
		}
		if (IsCollision(_state->get_bone_40(i).rc, _ui->getIGH().rc) && !_state->get_bone_40(i).isColision)
		{
			_ui->set_inGame_heart_currentHp(_ui->getIGH().currentHP - 5);
			_state->set_bone_40(i, true);
		}
		if (IsCollision(_state->get_bone_50(i).rc, _ui->getIGH().rc) && !_state->get_bone_50(i).isColision)
		{
			_ui->set_inGame_heart_currentHp(_ui->getIGH().currentHP - 5);
			_state->set_bone_50(i, true);
		}
		if (IsCollision(_state->get_bone_100(i).rc, _ui->getIGH().rc) && !_state->get_bone_100(i).isColision)
		{
			_ui->set_inGame_heart_currentHp(_ui->getIGH().currentHP - 5);
			_state->set_bone_100(i, true);
		}
		if (IsCollision(_state->get__laser_bim(i).rc, _ui->getIGH().rc) && !_state->get__laser_bim(i).isColision)
		{
			_ui->set_inGame_heart_currentHp(_ui->getIGH().currentHP - 5);
			_state->set_laser_bim(i, true);
		}
	}	
}


void sansBattle::InputHandle()
{
	sans_state* newState = _state->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_state);
		_state = newState;
		_state->enter(this);
	}
}