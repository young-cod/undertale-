#include "stdafx.h"
#include "stage6.h"

HRESULT stage6::init()
{
	ImageManager::GetInstance()->AddImage("통로2", L"스테이지이미지/node stage2.png");
	_backGround = ImageManager::GetInstance()->FindImage("통로2");

	CAMERAMANAGER->setMapCamera(638, 676);

	_player = new player;
	_player->init(WINSIZEX / 2, 650);

	_setRect = new stageRect;
	_setRect->release();

	_sceneRect = RectMake(285, 270, 75, 40);

	SAVELOADMANAGER->linkPlayer(_player);
	_setRect->linkPlayer(_player);

	return S_OK;
}

void stage6::release()
{
	_player->release();
	_setRect->release();
}

void stage6::update()
{
	if (IsCollision(_player->getBRect(), _sceneRect))
	{
		_player->setMoveStop(1);
		_player->setAlpha(_player->getAlpha() - 0.01f);
		if (_player->getAlpha() <= 0.f)
		{
			release();
			SCENEMANAGER->changeScene("stage7");
		}
	}
		if (!_player->getMoveStop())_player->update(); 
	_setRect->update();
}

void stage6::render()
{
	_backGround->mapRender(0, 0);

	_player->render();

	if (keyManager::getSingleton()->isToggleKey(VK_F1))
	{
		/*for (int i = 0; i < _setRect->getvGround().size(); i++)
		{
			D2DRENDER->DrawRectangle(_setRect->getvGround()[i].rc, D2DRenderer::DefaultBrush::Red, 1.f);
		}*/
		D2DRENDER->DrawRectangle(_sceneRect, D2DRenderer::DefaultBrush::White, 1.f);
	}
}
