#include "stdafx.h"
#include "muffet.h"

HRESULT muffet::init()
{
	ImageManager::GetInstance()->AddImage("¸ÓÆê", L"¸ÓÆêÀÌ¹ÌÁö/idle.png");
	ImageManager::GetInstance()->AddFrameImage("¸ÓÆê¿ôÀ½", L"¸ÓÆêÀÌ¹ÌÁö/lauhing.png", 5, 1);

	_muffet = ImageManager::GetInstance()->FindImage("¸ÓÆê");
	_muffetFrame = ImageManager::GetInstance()->FindImage("¸ÓÆê¿ôÀ½");
	_mfRc = RectMake(200, 200, 100, 100);

	_fCount = 0;
	_currentFrameX = 0;

	_x = WINSIZEX / 2;
	_y = WINSIZEY / 2;

	_angle = 0;

	return S_OK;
}

void muffet::release()
{
}

void muffet::update()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= 5.0f;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += 5.0f;
	}


	_fCount++;

	if (_fCount % 10 == 0)
	{
		_currentFrameX++;

		if (_currentFrameX >= _muffetFrame->GetMaxFrameX()) _currentFrameX = 0;

	}

	_angle += 2;
}

void muffet::render()
{
	_muffet->Render(_x, _y, 2, 2, _angle, 20, 20);

	_muffetFrame->FrameRender(200, 200, _currentFrameX, 0);
}
