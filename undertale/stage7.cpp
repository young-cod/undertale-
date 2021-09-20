#include "stdafx.h"
#include "stage7.h"

HRESULT stage7::init()
{
	ImageManager::GetInstance()->AddImage("마지막", L"스테이지이미지/last stage.png");
	_backGround = ImageManager::GetInstance()->FindImage("마지막");

	IMAGEMANAGER->AddFrameImage("end", L"샌즈이미지/end.png", 10, 1);

	_end.img = IMAGEMANAGER->FindImage("end");
	_end.x = 320;
	_end.y = 425;
	_end.rc = RectMakeCenter(_end.x, _end.y, 90, 111);
	_count = 0;
	CAMERAMANAGER->setMapCamera(640, 1200);

	_player = new player;
	_player->init(WINSIZEX / 2 + 20, 1120);


	_setRect = new stageRect;
	_setRect->release();

	_setRect->setGround(0, 0, 80, 1200);
	_setRect->setGround(80, 960, 40, 46);
	_setRect->setGround(120, 1000, 80, 40);
	_setRect->setGround(200, 1400, 80, 160);
	_setRect->setGround(360, 1400, 80, 160);
	_setRect->setGround(440, 1000, 80, 40);
	_setRect->setGround(520, 960, 40, 46);
	_setRect->setGround(560, 0, 80, 1200);
	_setRect->setGround(80, 230, 40, 90);
	_setRect->setGround(120, 150, 400, 86);
	_setRect->setGround(200, 1040, 80, 160);
	_setRect->setGround(360, 1040, 80, 160);
	_setRect->setGround(520, 230, 40, 90);

	SAVELOADMANAGER->linkPlayer(_player);
	_setRect->linkPlayer(_player);
	return S_OK;
}

void stage7::release()
{
	_player->release();
	_setRect->release();
}

void stage7::update()
{
	if (_player->getY() <= 700)
	{
		_count++;
		if (_count % 12 == 0)
		{
			_end.currentFrame++;
			if (_end.currentFrame >= _end.img->GetMaxFrameX()) _end.currentFrame = _end.img->GetMaxFrameX() - 1;
		}
	}
	if (IsCollision(_player->getBRect(), _end.rc))
	{
		_player->setMoveStop(1);
		_player->setAlpha(_player->getAlpha() - 0.01f);
		if (_player->getAlpha() <= 0.f)
		{
			release();
			SCENEMANAGER->changeScene("sansBattle");
		}
	}

	_setRect->update();
	if (!_player->getMoveStop())_player->update();
	

}

void stage7::render()
{
	_backGround->mapRender(0, 0);
	if (_player->getY() <= 700)
	{
		_end.img->FrameRender(_end.rc.left, _end.rc.top, _end.currentFrame, 0);
	}
	_player->render();

	if (keyManager::getSingleton()->isToggleKey(VK_F1))
	{
		for (int i = 0; i < _setRect->getvGround().size(); i++)
		{
			D2DRENDER->DrawRectangle(_setRect->getvGround()[i].rc, D2DRenderer::DefaultBrush::Red, 1.f);
		}
	}
}