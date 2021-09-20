#include "stdafx.h"
#include "stage3.h"

HRESULT stage3::init()
{
	ImageManager::GetInstance()->AddImage("통로", L"스테이지이미지/node stage.png");
	_backGround = ImageManager::GetInstance()->FindImage("통로");

	CAMERAMANAGER->setMapCamera(1320, 480);
	cout << _reStage << endl;
	_player = new player;
	if(!_reStage)_player->init(100,350);
	else _player->init(470, 440);

	SAVELOADMANAGER->linkPlayer(_player);

	_setRect = new stageRect;
	_setRect->release();
	_setRect->setGround(0, 280, 40, 160);
	_setRect->setGround(40, 440, 400, 40);
	_setRect->setGround(520, 440, 80, 40);
	_setRect->setGround(600, 280, 40, 160);
	_setRect->setGround(160, 240, 440, 40);

	_sceneRect = RectMake(440, 480, 100, 20);
	_sceneRect2 = RectMake(45, 250, 100, 20);

	_setRect->linkPlayer(_player);

	return S_OK;
}

void stage3::release()
{
	_player->release();
	_setRect->release();
}

void stage3::update()
{
	if (IsCollision(_player->getBRect(), _sceneRect))
	{
		release();
		SCENEMANAGER->changeScene("stage4");
		_reStage = true;
	}
	if (IsCollision(_player->getBRect(), _sceneRect2))
	{
		release();
		SCENEMANAGER->changeScene("stage6");
	}
	_player->update();
	_setRect->update();
}

void stage3::render()
{
	_backGround->mapRender(0, 0);

	_player->render();

	if (keyManager::getSingleton()->isToggleKey(VK_F1))
	{
		for (int i = 0; i < _setRect->getvGround().size(); i++)
		{
			D2DRENDER->DrawRectangle(_setRect->getvGround()[i].rc, D2DRenderer::DefaultBrush::Red, 1.f);
		}
		D2DRENDER->DrawRectangle(_sceneRect, D2DRenderer::DefaultBrush::White, 1.f);
	}
}
