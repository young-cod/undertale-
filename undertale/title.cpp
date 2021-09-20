#include "stdafx.h"
#include "title.h"

HRESULT title::init()
{
	IMAGEMANAGER->AddImage("title", L"���������̹���/title.png");
	_backGround = IMAGEMANAGER->FindImage("title");
	
	CAMERAMANAGER->setMapCamera(640, 480);


	return S_OK;
}

void title::release()
{
}

void title::update()
{
	if (keyManager::getSingleton()->isOnceKeyDown('Z'))
	{
		SCENEMANAGER->changeScene("stage1");
	}
}

void title::render()
{
	_backGround->Render(0, 0);
}
