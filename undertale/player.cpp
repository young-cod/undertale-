#include "stdafx.h"
#include "player.h"
#include "stageManager.h"
#include <vector>
#include <algorithm>

HRESULT player::init()
{
	cout << SCENEMANAGER->getSceneName() << "인잇"<<endl;
	IMAGEMANAGER->AddFrameImage("LEFT_MOVE", L"frisk/left_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("RIGHT_MOVE", L"frisk/right_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("UP_MOVE", L"frisk/up_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("DOWN_MOVE", L"frisk/down_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("LEFT", L"frisk/left.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("RIGHT", L"frisk/right.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("UP", L"frisk/up.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("DOWN", L"frisk/down.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("RED", L"hearts/RED.png", 1, 1);


	if (SCENEMANAGER->isCurrentScene("stage2")) //산
	{
		_player.x = WINSIZEX / 2 + 20;
		_player.y = 1100;
	}
	else if (SCENEMANAGER->isCurrentScene("stage3"))//위로 올라감
	{
		_player.x = 100;
		_player.y = 350;
	}
	else if (SCENEMANAGER->isCurrentScene("stage4"))//상점 가기 전
	{
		_player.x = 120;
		_player.y = 100;
	}
	else if (SCENEMANAGER->isCurrentScene("stage6"))//엘베
	{
		_player.x = WINSIZEX / 2;
		_player.y = 700;
	}
	else if (SCENEMANAGER->isCurrentScene("stage7"))//마지막 스테이지
	{
		_player.x = WINSIZEX / 2 + 20;
		_player.y = 1120;
	}
	else
	{
		_player.x = WINSIZEX / 2;
		_player.y = WINSIZEY / 2;
	}

	_player.speed = 3.0f;
	_player.img = IMAGEMANAGER->FindImage("DOWN");
	_player.state = DOWN;
	_player.rc = RectMakeCenter(_player.x, _player.y, 40, 60);
	_player.balpan = RectMake(_player.rc.left, _player.rc.bottom - 10, 40, 10);  // 캐릭터 하단의 발판.
	_player.currentFrameX = 0;
	_player.currentFrameY = 0;
	_player.isBattle = false;
	_player.alpha = 1.0f;
	_heart.img = IMAGEMANAGER->FindImage("RED");
	_heart.currentFrameX = 0;

	_vObject.push_back(&_player);
	
	_blink = 0;
	_index = 0;
	_timer = 0;
	return S_OK;
}
HRESULT player::init(float x, float y)
{
	cout << SCENEMANAGER->getSceneName() << "인잇"<<endl;
	IMAGEMANAGER->AddFrameImage("LEFT_MOVE", L"frisk/left_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("RIGHT_MOVE", L"frisk/right_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("UP_MOVE", L"frisk/up_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("DOWN_MOVE", L"frisk/down_move.png", 4, 1);
	IMAGEMANAGER->AddFrameImage("LEFT", L"frisk/left.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("RIGHT", L"frisk/right.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("UP", L"frisk/up.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("DOWN", L"frisk/down.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("RED", L"hearts/RED.png", 1, 1);

	_player.x = x;
	_player.y = y;

	_player.speed = 3.0f;
	_player.img = IMAGEMANAGER->FindImage("DOWN");
	_player.state = DOWN;
	_player.rc = RectMakeCenter(_player.x, _player.y, 40, 60);
	_player.balpan = RectMake(_player.rc.left, _player.rc.bottom - 10, 40, 10);  // 캐릭터 하단의 발판.
	_player.currentFrameX = 0;
	_player.currentFrameY = 0;
	_player.isBattle = false;
	_player.alpha = 1.0f;
	_heart.img = IMAGEMANAGER->FindImage("RED");
	_heart.currentFrameX = 0;
	_imageON = false;
	_vObject.push_back(&_player);

	IMAGEMANAGER->AddFrameImage("bush1", L"오브젝트이미지/bush1.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("bush2", L"오브젝트이미지/bush2.png", 1, 1);
	cout << SCENEMANAGER->getSceneName() << endl;
	


	if (sceneManager::getSingleton()->isCurrentScene("stage2"))
	{
		ImageManager::GetInstance()->AddFrameImage("undyneEyespark", L"Undyne/Und_eyeSpark.png", 9, 1);
		_undy.x = WINSIZEX / 2;
		_undy.y = 800;
		_undy.rc = RectMakeCenter(_undy.x, _undy.y, 80, 100);
		_undy.img = ImageManager::GetInstance()->FindImage("undyneEyespark");
		_undy.currentFrameX = _undy.currentFrameY = 0;

		_vObject.push_back(&_undy);
	}
	return S_OK;
}

void player::release()
{
	_vObject.clear();
}

bool compare(tagPlayer * a, tagPlayer * b)
{
	return a->rc.bottom < b->rc.bottom;
}

void player::update()
{
	if (SCENEMANAGER->isCurrentScene("stage1")) setBush();
	for (int i = 0; i < _vObject.size(); i++)
	{
		sort(_vObject.begin(), _vObject.end(), compare);
	}
	collisionBush();

	if (!_player.isBattle)
	{
		for (int i = 0; i < _vObject.size(); i++)
		{
			_vObject[i]->count++;
			if (_vObject[i]->count % 10 == 0)
			{
				_vObject[i]->currentFrameX++;
				if (_vObject[i]->currentFrameX >= _vObject[i]->img->GetMaxFrameX()) _vObject[i]->currentFrameX = 0;
				_vObject[i]->currentFrameY = 0;

				_vObject[i]->count = 0;
			}
			_vObject[i]->rc = RectMakeCenter(_vObject[i]->x, _vObject[i]->y, _vObject[i]->img->GetFrameWidth(), _vObject[i]->img->GetFrameHeight());
		}
		//_player.count++;
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_player.state = LEFT_MOVE;
			_player.x -= _player.speed;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_player.state = LEFT;
		}

		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_player.state = RIGHT_MOVE;
			_player.x += _player.speed;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_player.state = RIGHT;
		}

		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_player.state = UP_MOVE;
			_player.y -= _player.speed;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_player.state = UP;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_player.state = DOWN_MOVE;
			_player.y += _player.speed;
		}
		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_player.state = DOWN;
		}
		switch (_player.state)
		{
		case LEFT_MOVE:
			_player.img = ImageManager::GetInstance()->FindImage("LEFT_MOVE");
			if (_player.count % 5 == 0)
			{
				_player.currentFrameX++;
				if (_player.currentFrameX >= _player.img->GetMaxFrameX())_player.currentFrameX = 0;
				_player.currentFrameY = 0;
			}
			break;

		case RIGHT_MOVE:
			_player.img = ImageManager::GetInstance()->FindImage("RIGHT_MOVE");
			if (_player.count % 5 == 0)
			{
				_player.currentFrameX++;
				if (_player.currentFrameX >= _player.img->GetMaxFrameX())_player.currentFrameX = 0;
				_player.currentFrameY = 0;
			}
			break;

		case UP_MOVE:
			_player.img = ImageManager::GetInstance()->FindImage("UP_MOVE");
			if (_player.count % 5 == 0)
			{
				_player.currentFrameX++;
				if (_player.currentFrameX >= _player.img->GetMaxFrameX())_player.currentFrameX = 0;
				_player.currentFrameY = 0;
			}
			break;

		case DOWN_MOVE:
			_player.img = ImageManager::GetInstance()->FindImage("DOWN_MOVE");
			if (_player.count % 5 == 0)
			{
				_player.currentFrameX++;
				if (_player.currentFrameX >= _player.img->GetMaxFrameX())_player.currentFrameX = 0;
				_player.currentFrameY = 0;
			}
			break;

		case LEFT:
			_player.img = ImageManager::GetInstance()->FindImage("LEFT");
			_player.currentFrameX = 0;
			break;

		case RIGHT:
			_player.img = ImageManager::GetInstance()->FindImage("RIGHT");
			_player.currentFrameX = 0;
			break;

		case UP:
			_player.img = ImageManager::GetInstance()->FindImage("UP");
			_player.currentFrameX = 0;
			break;

		case DOWN:
			_player.img = ImageManager::GetInstance()->FindImage("DOWN");
			_player.currentFrameX = 0;
			break;
		}
		_player.rc = RectMakeCenter(_player.x, _player.y, 40, 60);
		_player.balpan = RectMake(_player.rc.left, _player.rc.bottom - 10, 40, 10);
	}


	if (!_imageON)
	{
		_heart.img->SetAlpha(0);
	}
	else
	{
		_heart.img->SetAlpha(1);
	}

	if (_blink >= 3)
	{
		_heart.angle = GetAngle(_heart.x, _heart.y, WINSIZEX/2,1100);
		_heart.x -= cosf(_heart.angle) * -_player.speed;
		_heart.y -= -sinf(_heart.angle) * -_player.speed;
		_heart.rc = RectMakeCenter(_heart.x, _heart.y, 20, 20);
	}
	CAMERAMANAGER->updateCamera(_player.x, _player.y);
}

void player::render()
{
	if (!_player.deletepl)
	{
		for (int i = 0; i < _vObject.size(); i++)
		{
			_vObject[i]->img->FrameRender(_vObject[i]->rc.left, _vObject[i]->rc.top, _vObject[i]->currentFrameX, _vObject[i]->currentFrameY, _vObject[i]->alpha);
		}
	}
	if(_timer % 10 <5)
	_heart.img->FrameRender(_heart.rc.left, _heart.rc.top, _heart.currentFrameX, _heart.currentFrameY);

	//D2DRENDER->DrawRectangle
	//(
	//	_player.rc,
	//	D2DRenderer::DefaultBrush::Red,
	//	1.f
	//	//angle
	//);
	//D2DRENDER->DrawRectangle
	//(
	//	_player.balpan,
	//	D2DRenderer::DefaultBrush::Red,
	//	1.f
	//	//angle
	//);



}

void player::setBush()
{
	if (_vObject.size() <= 10)
	{
		_object.img = IMAGEMANAGER->FindImage("bush1");
		_object.x = 400;
		_object.y = 250;
		_object.rc = RectMake(_object.x, _object.y, 70, 74);
		_object.currentFrameX = 0;
		_object.currentFrameY = 0;
		_object.alpha = 1;

		_vObject.push_back(&_object);

		_bush2.img = IMAGEMANAGER->FindImage("bush1");
		_bush2.x = 400 + _bush2.img->GetFrameWidth();
		_bush2.y = 250 + _bush2.img->GetFrameHeight();
		_bush2.rc = RectMake(_bush2.x, _bush2.y, 70, 74);
		_bush2.currentFrameX = 0;
		_bush2.currentFrameY = 0;
		_bush2.alpha = 1;

		_vObject.push_back(&_bush2);

		_bush3.img = IMAGEMANAGER->FindImage("bush1");
		_bush3.x = 400;
		_bush3.y = 250 + _bush3.img->GetFrameHeight();
		_bush3.rc = RectMake(_bush3.x, _bush3.y, 70, 74);
		_bush3.currentFrameX = 0;
		_bush3.currentFrameY = 0;
		_bush3.alpha = 1;

		_vObject.push_back(&_bush3);

		_bush4.img = IMAGEMANAGER->FindImage("bush1");
		_bush4.x = 400 + _bush4.img->GetFrameWidth();
		_bush4.y = 250;
		_bush4.rc = RectMake(_bush4.x, _bush4.y, 70, 74);
		_bush4.currentFrameX = 0;
		_bush4.currentFrameY = 0;
		_bush4.alpha = 1;

		_vObject.push_back(&_bush4);
	}
}

void player::collisionBush()
{
	if (IsCollision(_player.rc, _object.rc))
	{
		_object.img = IMAGEMANAGER->FindImage("bush2");
	}
	else _object.img = IMAGEMANAGER->FindImage("bush1");
	if (IsCollision(_player.rc, _bush2.rc))
	{
		_bush2.img = IMAGEMANAGER->FindImage("bush2");
	}
	else _bush2.img = IMAGEMANAGER->FindImage("bush1");
	if (IsCollision(_player.rc, _bush3.rc))
	{
		_bush3.img = IMAGEMANAGER->FindImage("bush2");
	}
	else _bush3.img = IMAGEMANAGER->FindImage("bush1");
	if (IsCollision(_player.rc, _bush4.rc))
	{
		_bush4.img = IMAGEMANAGER->FindImage("bush2");
	}
	else _bush4.img = IMAGEMANAGER->FindImage("bush1");
}



void player::setHeart(float x, float y)
{
	_heart.rc = RectMakeCenter(_heart.x, _heart.y, 20, 20);

	_timer++;
	if (_blink < 3)
	{
		if (_timer % 10 == 0)
		{
			_blink++;
			
		}
		_heart.x = _player.x;
		_heart.y = _player.y;
	}
	if (_blink == 3)
	{
		_player.deletepl = true;
		_heart.rc = RectMakeCenter(_heart.x, _heart.y, 20, 20);
		_imageON = true;
	}
}




