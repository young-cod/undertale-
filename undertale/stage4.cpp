#include "stdafx.h"
#include "stage4.h"

HRESULT stage4::init()
{
	ImageManager::GetInstance()->AddImage("테미마을", L"스테이지이미지/temmie villige.png");
	_backGround = ImageManager::GetInstance()->FindImage("테미마을");

	CAMERAMANAGER->setMapCamera(1320, 600);
	_player = new player;
	if(!_shopRe)_player->init(120,100);
	else _player->init(675, 300);

	_setRect = new stageRect;
	_setRect->release();

	_setRect->setGround(0, 0, 80, 480);
	_setRect->setGround(1200, 300, 40, 200);
	_setRect->setGround(720, 290, 480, 40 );
	_setRect->setGround(160, 0, 40, 290);
	_setRect->setGround(600, 0, 35, 290);
	_setRect->setGround(160, 290, 475 , 40);
	_setRect->setGround(80, 480, 1130, 40);
	_setRect->setGround(720, 0, 35, 290);

	_sceneRect = RectMake(640, 255, 75, 20);
	_sceneRect2 = RectMake(82, 10, 75, 20);

	SAVELOADMANAGER->linkPlayer(_player);
	_setRect->linkPlayer(_player);


	return S_OK;
}

void stage4::release()
{
	_player->release();
	_setRect->release();
}

void stage4::update()
{
	if (IsCollision(_player->getBRect(), _sceneRect))
	{
		_player->setMoveStop(1);
		_player->setAlpha(_player->getAlpha() - 0.01f);
		if (_player->getAlpha() <= 0.f)
		{
			release();
			SCENEMANAGER->changeScene("stage5");
			_shopRe = true;
		}
	}
	if (IsCollision(_player->getBRect(), _sceneRect2))
	{
		_shopRe = false;
		release();
		SCENEMANAGER->changeScene("stage3");
	}
	if (!_player->getMoveStop())_player->update();
	_setRect->update();
}

void stage4::render()
{
	_backGround->mapRender(0, 0);

	_player->render();
	INVENTORY->render();
	if (keyManager::getSingleton()->isToggleKey(VK_F1))
	{
		for (int i = 0; i < _setRect->getvGround().size(); i++)
		{
			D2DRENDER->DrawRectangle(_setRect->getvGround()[i].rc, D2DRenderer::DefaultBrush::Red, 1.f);
		}
		D2DRENDER->DrawRectangle(_sceneRect, D2DRenderer::DefaultBrush::White, 1.f);
		D2DRENDER->DrawRectangle(_sceneRect2, D2DRenderer::DefaultBrush::White, 1.f);
	}
}
