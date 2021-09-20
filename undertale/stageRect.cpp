#include "stdafx.h"
#include "stageRect.h"
#include "player.h"

//x레프트, y탑
HRESULT stageRect::init()
{
	

	return S_OK;
}

void stageRect::release()
{
	_vGround.clear();
}

void stageRect::update()
{
	RECT temp;

	RECT plRc = _player->getBRect();


	for (int i = 0; i < _vGround.size(); i++)
	{
		RECT groundRect = _vGround[i].rc;

		if (IntersectRect(&temp, &plRc, &groundRect))
		{
			float width = (temp.right - temp.left);
			float height = (temp.bottom - temp.top);

			float playerX = _player->getX();
			float playerY = _player->getY();

			bool _pt;

			//수직 수평
			(width > height) ? _pt = false : _pt = true;

			if (_pt) // 수평
			{
				//왼쪽에 있나
				if (plRc.left < groundRect.left) _player->setPlayerX(playerX -= width);
				//오른쪽에 있나
				if (plRc.right > groundRect.right) _player->setPlayerX(playerX += width);
			}
			else if (!_pt) //수직
			{
				//위에 있나
				if (plRc.top < groundRect.top) _player->setPlayerY(playerY -= height);
				//아래에 있나
				if (plRc.bottom > groundRect.bottom) _player->setPlayerY(playerY += height);
			}
		}
	}
}

void stageRect::render()
{
	for (int i = 0; _vGround.size(); i++)
	{
		_vGround[i].img->Render(_vGround[i].rc.left, _vGround[i].rc.top);
	}
}

void stageRect::setGround(const float x, const float y, const float width, const float height, const string imageName)
{

	tagRect ground;
	//ZeroMemory(&ground, sizeof(tagRect));
	if (imageName != "no") ground.img = ImageManager::GetInstance()->FindImage(imageName);
	ground.width = width;
	ground.height = height;
	ground.x = x;
	ground.y = y;

	ground.rc = RectMake(ground.x, ground.y, ground.width, ground.height);

	_vGround.push_back(ground);

}

HRESULT objectRect::init()
{
	
	return S_OK;
}

void objectRect::release()
{
	_vObject.clear();

}

void objectRect::update()
{
	//여기에 z오더
}

void objectRect::render()
{
	for (int i = 0; _vObject.size(); i++)
	{
		_vObject[i].img->Render(_vObject[i].rc.left, _vObject[i].rc.top);
	}
}

void objectRect::setObject(const float x, const float y, const float width, const float height, const string imageName)
{
	tagRect object;
	ZeroMemory(&object, sizeof(tagRect));
	if (imageName != "no") object.img = ImageManager::GetInstance()->FindImage(imageName);
	object.width = width;
	object.height = height;
	object.x = x;
	object.y = y;

	object.rc = RectMake(object.x, object.y, object.width, object.height);

	_vObject.push_back(object);
}
