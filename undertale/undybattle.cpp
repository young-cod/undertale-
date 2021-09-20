#include "stdafx.h"
#include "undybattle.h"
#include "undyneFireArrowState.h"

HRESULT undybattle::init()
{
	_bui = new battleUI;
	_bui->init(0);

	_undyState = new undyneIdle;
	_undyState->enter(this);
	_undyState->linkundynebattle(this);

	ImageManager::GetInstance()->AddFrameImage("und_hair", L"Undyne/Und_battle_hair.png", 4, 1);
	ImageManager::GetInstance()->AddFrameImage("und_head", L"Undyne/Und_battle_head1.png", 1, 1);
	ImageManager::GetInstance()->AddFrameImage("und_torso", L"Undyne/Und_Torso.png", 1, 1);
	ImageManager::GetInstance()->AddFrameImage("und_leftarm", L"Undyne/Und_left_arm.png", 1, 1);
	ImageManager::GetInstance()->AddFrameImage("und_rightarm", L"Undyne/Und_right_arm.png", 1, 1);
	ImageManager::GetInstance()->AddFrameImage("und_belly", L"Undyne/Und_belly.png", 1, 1);
	ImageManager::GetInstance()->AddFrameImage("und_legs", L"Undyne/Und_legs.png", 1, 1);
	ImageManager::GetInstance()->AddFrameImage("battleback", L"Undyne/BATTLE_BACKGROUND.png", 1, 1);
	ImageManager::GetInstance()->AddFrameImage("janSang", L"Undyne/Und_battle_slasheffect.png", 6, 1);

	IMAGEMANAGER->AddImage("LEFTBULLET_OFF", L"Undyne/LEFT_ARROW_OFF.png");
	IMAGEMANAGER->AddImage("RIGHTBULLET_OFF", L"Undyne/RIGHT_ARROW_OFF.png");
	IMAGEMANAGER->AddImage("DOWNBULLET_OFF", L"Undyne/DOWN_ARROW_OFF.png");
	IMAGEMANAGER->AddImage("UPBULLET_OFF", L"Undyne/UP_ARROW_OFF.png");

	IMAGEMANAGER->AddImage("LEFTBULLET_ON", L"Undyne/LEFT_ARROW_ON.png");
	IMAGEMANAGER->AddImage("RIGHTBULLET_ON", L"Undyne/RIGHT_ARROW_ON.png");
	IMAGEMANAGER->AddImage("DOWNBULLET_ON", L"Undyne/DOWN_ARROW_ON.png");
	IMAGEMANAGER->AddImage("UPBULLET_ON", L"Undyne/UP_ARROW_ON.png");

	IMAGEMANAGER->AddImage("LEFTBULLET_FAKE", L"Undyne/LEFT_ARROW_FAKE.png");
	IMAGEMANAGER->AddImage("RIGHTBULLET_FAKE", L"Undyne/RIGHT_ARROW_FAKE.png");
	IMAGEMANAGER->AddImage("DOWNBULLET_FAKE", L"Undyne/DOWN_ARROW_FAKE.png");
	IMAGEMANAGER->AddImage("UPBULLET_FAKE", L"Undyne/UP_ARROW_FAKE.png");

	
	currentFrameX = currentFrameY = 0;
	_torso.x = WINSIZEX/2;
	_torso.y = WINSIZEY/2 -150;
	_torso.rc = RectMakeCenter(_torso.x, _torso.y, 66, 33);
	_torso.img = ImageManager::GetInstance()->FindImage("und_torso");
	_torso.currentFrameX = _torso.currentFrameY = 0;
	

	_head.x = _torso.x-2.5;
	_head.y = _torso.y -30;
	_head.rc = RectMakeCenter(_head.x, _head.y, 32, 28);
	_head.img = ImageManager::GetInstance()->FindImage("und_head");
	_head.currentFrameX = _head.currentFrameY = 0;

	_hair.x = _head.x -50;
	_hair.y = _head.y;
	_hair.rc = RectMakeCenter(_hair.x, _hair.y, 30, 20);
	_hair.img = ImageManager::GetInstance()->FindImage("und_hair");
	_hair.currentFrameX = _hair.currentFrameY = 0;

	_leftArm.x = _torso.x-30;
	_leftArm.y = _torso.y+30;
	_leftArm.rc = RectMakeCenter(_leftArm.x, _leftArm.y, 47, 71);
	_leftArm.img = ImageManager::GetInstance()->FindImage("und_leftarm");
	_leftArm.currentFrameX = _leftArm.currentFrameY = 0;
	_leftArm.isAttack = true;

	_rightArm.x = _torso.x + 20;
	_rightArm.y = _torso.y +10;
	_rightArm.rc = RectMakeCenter(_rightArm.x, _rightArm.y, 15, 37);
	_rightArm.img = ImageManager::GetInstance()->FindImage("und_rightarm");
	_rightArm.currentFrameX = _rightArm.currentFrameY = 0;


	_belly.x = _torso.x-3;
	_belly.y = _torso.y+20;
	_belly.rc = RectMakeCenter(_belly.x, _belly.y, 37, 24);
	_belly.img = ImageManager::GetInstance()->FindImage("und_belly");
	_belly.currentFrameX = _belly.currentFrameY = 0;


	_legs.x = _belly.x+1;
	_legs.y = _belly.y+25;
	_legs.rc = RectMakeCenter(_legs.x, _legs.y, 39, 37);
	_legs.img = ImageManager::GetInstance()->FindImage("und_legs");
	_legs.currentFrameX = _legs.currentFrameY = 0;

	_leftArm.janSang = RectMakeCenter(((_bui->get_main_rect().left + _bui->get_main_rect().right) / 2), ((_bui->get_main_rect().bottom + _bui->get_main_rect().top) / 2),380,169);
	_jansang = ImageManager::GetInstance()->FindImage("janSang");
	

	_hair.rc = RectMakeCenter(_hair.x, _head.y, 10, 10);
	_head.rc = RectMakeCenter(_head.x, _head.y, 32, 28);
	_leftArm.rc = RectMakeCenter(_leftArm.x, _leftArm.y, 47, 71);
	_rightArm.rc = RectMakeCenter(_rightArm.x, _rightArm.y, 15, 37);
	_belly.rc = RectMakeCenter(_belly.x, _belly.y, 37, 24);
	_legs.rc = RectMakeCenter(_legs.x, _legs.y, 39, 37);
	_torso.rc = RectMakeCenter(_torso.x, _torso.y, 66, 33);

	_shieldLine.angle = PI / 2;
	_shieldLine.length = 70;
	_shieldLine.lineCenter.x = (_bui->get_main_rect().left + _bui->get_main_rect().right) / 2;
	_shieldLine.lineCenter.y = (_bui->get_main_rect().top + _bui->get_main_rect().bottom) / 2;

	return S_OK;
}

void undybattle::release()
{
}

void undybattle::update()
{
	inputHandle();
	_undyState->update(this);

	

	_count++;
	
	if (_bui->get_bubble_talk_count() == 0&&_count == 20) maxangle = true; // 처음에 하트를 초록색으로 바꿔줄때 사용

	if (_bui->getState() == INGAME)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_shieldLine.angle = 0;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_shieldLine.angle = PI * 1.5;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_shieldLine.angle = PI / 2;
		}
		else if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_shieldLine.angle = PI;
		}
	}

	_shieldLine.lineEnd.x = cosf(_shieldLine.angle) * _shieldLine.length + _shieldLine.lineCenter.x;
	_shieldLine.lineEnd.y = -sinf(_shieldLine.angle) * _shieldLine.length + _shieldLine.lineCenter.y;


	
	

	if (_count % 5 == 0)
	{
		_hair.currentFrameX++;
		if (_hair.currentFrameX >= _hair.img->GetMaxFrameX())_hair.currentFrameX = 0;
		_hair.currentFrameY = 0;
	}
	if (!_leftArm.isAttack)
	{
		if (_head.isMove)
		{
			_head.y -= 0.2;
			if (_head.y < _torso.y - 32) _head.isMove = false;
		}
		else
		{
			_head.y += 0.2;
			if (_head.y > _torso.y - 29)_head.isMove = true;
		}


		if (_torso.isMove)
		{
			_torso.y -= 0.2;
			if (_torso.y < WINSIZEY / 2 - 154)_torso.isMove = false;
		}
		else
		{
			_torso.y += 0.2;
			if (_torso.y > WINSIZEY / 2 - 148)_torso.isMove = true;
		}

		if (_leftArm.isMove)
		{
			_leftArm.y -= 0.2;
			_leftArm.x -= 0.2;
			if (_leftArm.y < _torso.y + 29)_leftArm.isMove = false;
		}
		else
		{
			_leftArm.y += 0.2;
			_leftArm.x += 0.2;
			if (_leftArm.y > _torso.y + 31) _leftArm.isMove = true;
		}

		if (_rightArm.isMove)
		{
			_rightArm.y -= 0.2;
			_rightArm.x -= 0.1;
			if (_rightArm.y < _torso.y + 12) _rightArm.isMove = false;
		}
		else
		{
			_rightArm.y += 0.2;
			_rightArm.x += 0.1;
			if (_rightArm.y > _torso.y + 10) _rightArm.isMove = true;
		}

		if (_belly.isMove)
		{
			_belly.y -= 0.2;
			if (_belly.y < _torso.y + 23)_belly.isMove = false;
		}
		else
		{
			_belly.y += 0.2;
			if (_belly.y > _torso.y + 27)_belly.isMove = true;
		}
	}
	
	// 하트를 초록색으로 변경해주는 파트@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	if (_leftArm.isAttack&& maxangle)
	{
		angle += 5;
		if (angle == 80.f)maxangle =false;
	}

	if (!maxangle)
	{
		if (_count == 60)minangle = true;
		if (minangle)
		{
			if(angle > -60.f)angle -= 5;
			else if(angle > -70.f)angle -= 0.5;
			
		}
		if (angle == -70.f)
		{
			minangle = false;
			_bui->set_inGame_heart_image(IMAGEMANAGER->FindImage("GREEN"));
		}
	}

	if (!maxangle && !minangle&&_count >170)
	{
		if (angle < 0)angle += 5;
		if(angle==0)_leftArm.isAttack = false;
	}
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	
	_hair.rc = RectMakeCenter(_hair.x, _head.y-10, 10, 10);
	_head.rc = RectMakeCenter(_head.x, _head.y, 32, 28);
	_leftArm.rc = RectMakeCenter(_leftArm.x, _leftArm.y, 47, 71);
	_rightArm.rc = RectMakeCenter(_rightArm.x, _rightArm.y, 15, 37);
	_belly.rc = RectMakeCenter(_belly.x, _belly.y, 37, 24);
	_legs.rc = RectMakeCenter(_legs.x, _legs.y, 39, 37);
	_torso.rc = RectMakeCenter(_torso.x, _torso.y, 66, 33);

	if (_shieldLine.angle == 0 || _shieldLine.angle == PI)rc_shield = RectMakeCenter(_shieldLine.lineEnd.x, _shieldLine.lineEnd.y, 1, 45);
	else  rc_shield = RectMakeCenter(_shieldLine.lineEnd.x, _shieldLine.lineEnd.y, 45, 1);
	
	_bui->update();
}

void undybattle::render()
{
	_undyState->render(this);
	
	if (_leftArm.isAttack)
	{
		if(angle<=-60)_jansang->autoFrameRender(_leftArm.janSang.left, _leftArm.janSang.top-50, currentFrameX, currentFrameY);

		_torso.img->bossFrameRender(_torso.rc.left, _torso.rc.top, _torso.currentFrameX, _torso.currentFrameY);
		_belly.img->bossFrameRender(_belly.rc.left, _belly.rc.top, _belly.currentFrameX, _belly.currentFrameY);
		_legs.img->bossFrameRender(_legs.rc.left, _legs.rc.top, _legs.currentFrameX, _legs.currentFrameY);
		_leftArm.img->bossFrameRender(_leftArm.rc.left, _leftArm.rc.top, _leftArm.currentFrameX, _leftArm.currentFrameY, 1.f, 1.f, angle, 35.f, 0.f, 0.f, 0.f);
	}
	else {
		_leftArm.img->bossFrameRender(_leftArm.rc.left, _leftArm.rc.top, _leftArm.currentFrameX, _leftArm.currentFrameY);
		_torso.img->bossFrameRender(_torso.rc.left, _torso.rc.top, _torso.currentFrameX, _torso.currentFrameY);
		_belly.img->bossFrameRender(_belly.rc.left, _belly.rc.top, _belly.currentFrameX, _belly.currentFrameY);
		_legs.img->bossFrameRender(_legs.rc.left, _legs.rc.top, _legs.currentFrameX, _legs.currentFrameY);
	}
	_rightArm.img->bossFrameRender(_rightArm.rc.left, _rightArm.rc.top, _rightArm.currentFrameX, _rightArm.currentFrameY);
	_hair.img->bossFrameRender(_hair.rc.left, _hair.rc.top, _hair.currentFrameX, _hair.currentFrameY);
	_head.img->bossFrameRender(_head.rc.left, _head.rc.top, _head.currentFrameX, _head.currentFrameY);
	_bui->render();

	if (_bui->getState() == INGAME)
	{
		D2DRENDER->DrawLine(PointMake(_shieldLine.lineCenter.x, _shieldLine.lineCenter.y)
			, PointMake(_shieldLine.lineEnd.x, _shieldLine.lineEnd.y), D2DRenderer::DefaultBrush::Blue, 1.0);
		D2DRENDER->DrawRectangle(rc_shield, D2DRenderer::DefaultBrush::Blue, 4.f);
	}
	
}

void undybattle::inputHandle()
{
	undyneState* newState = _undyState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_undyState);
		_undyState = newState;
		_undyState->enter(this);
	}
}
