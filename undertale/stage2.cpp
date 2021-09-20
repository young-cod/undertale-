#include "stdafx.h"
#include "stage2.h"

HRESULT stage2::init()
{
	if (SCENEMANAGER->isCurrentScene("stage2"))	cout << "일치" << endl;
	IMAGEMANAGER->AddImage("언다인스테이지", L"스테이지이미지/undyne stage.png");
	_backGround = IMAGEMANAGER->FindImage("언다인스테이지");

	CAMERAMANAGER->setMapCamera(640, 1280);

	if (SCENEMANAGER->isCurrentScene("stage2"))	cout << "일치" << endl;

	_player = new player;
	_player->init(WINSIZEX / 2, 1200);
	
	_undy = new undyne;
	_undy->init();
	


	SAVELOADMANAGER->linkPlayer(_player);

	_setRect = new stageRect;

	_setRect->setGround(0, 200, 230, 1300);
	_setRect->setGround(400, 200, 240, 1300);

	_sceneRect = RectMake(250,980, 70, 30);

	_changeScene = RectMakeCenter(WINSIZEX / 2, 1100, 10, 10);

	_setRect->linkPlayer(_player);


	_bg = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, WINSIZEX, WINSIZEY);

	return S_OK;
}

void stage2::release()
{
	_undy->release();
	_player->release();
	_setRect->release();
}

void stage2::update()
{
	if (IsCollision(_player->getBRect(), _sceneRect))
	{
		_player->setMoveStop(1);
		_player->setAlpha(_player->getAlpha() - 0.01f);
		if (_player->getAlpha() <= 0.f)
		{
			release();
			SCENEMANAGER->changeScene("stage3");
		}
	}

	if (IsCollision(_player->getHRect(), _changeScene))
	{
		release();
		SCENEMANAGER->changeScene("undybattle");
	}
	if (!_player->getMoveStop())_player->update(); 
	_setRect->update();
	_undy->update();

	float x = _player->getX();
	float y = _player->getY();
	float angle;
	RECT temp;
	if (IntersectRect(&temp, &_player->getRect(), &_undy->getRect()))
		_player->setBattlechk(true);

	if (_player->getBattlechk())
	{
		_player->setHeart(x, y);
	}
}

void stage2::render()
{
	_backGround->mapRender(0, 0);
	_undy->render();
	if (_player->getBattlechk())D2DRENDER->FillRectangle(_bg, D2DRenderer::DefaultBrush::Black);
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
