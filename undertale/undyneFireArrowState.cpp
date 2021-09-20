#include "stdafx.h"
#include "undyneFireArrowState.h"

undyneState* undyneFireArrowState::inputHandle(undybattle* undybattle)
{
	

	if (undybattle->getUI()->getState() != INGAME)
	{
		return new undyneIdle();
	}
	return nullptr;

}

void undyneFireArrowState::update(undybattle* undybattle)
{
	_timer++;

	undybattle->getUI()->setEnemy_attackTime_max(300);

	if (_timer % 20 == 0)
	{
		undybulletFire(undybattle);
	}
	
	if (_vUBullet.size() != 0)
	{
		
		for (int i = 0; i < _vUBullet.size(); i++)
		{

			switch (_directionSelect)
			{
			case 0:
				_bulletDirect = LEFTFIRE;
				break;
			case 1:
				_bulletDirect = RIGHTFIRE;
				break;
			case 2:
				_bulletDirect = UPFIRE;
				break;
			case 3:
				_bulletDirect = DOWNFIRE;
				break;
			}

			switch (_vUBullet[i]._bulletDirect)
			{
			case LEFTFIRE:
					_vUBullet[i].x += 5+undybattle->getUI()->getBattle_turn();
					_vUBullet[i].rc = RectMake(_vUBullet[i].x, _vUBullet[i].y, _vUBullet[i].image->GetWidth(), _vUBullet[i].image->GetHeight());
				break;

			case RIGHTFIRE:
					_vUBullet[i].x -= 5 + undybattle->getUI()->getBattle_turn();
					_vUBullet[i].rc = RectMake(_vUBullet[i].x, _vUBullet[i].y, _vUBullet[i].image->GetWidth(), _vUBullet[i].image->GetHeight());
				
				break;
			case UPFIRE:
				
					_vUBullet[i].y += 5 + undybattle->getUI()->getBattle_turn();
					_vUBullet[i].rc = RectMake(_vUBullet[i].x, _vUBullet[i].y, _vUBullet[i].image->GetWidth(), _vUBullet[i].image->GetHeight());
				
				break;
			case DOWNFIRE:
					_vUBullet[i].y -= 5 + undybattle->getUI()->getBattle_turn();
					_vUBullet[i].rc = RectMake(_vUBullet[i].x, _vUBullet[i].y, _vUBullet[i].image->GetWidth(), _vUBullet[i].image->GetHeight());
				break;

			}
		}
		
	}


	for (_viUBullet = _vUBullet.begin(); _viUBullet != _vUBullet.end();)
	{
		if (IsCollision(_viUBullet->rc, undybattle->getUI()->getIGH().rc))

		{
			undybattle->getUI()->set_inGame_heart_currentHp(undybattle->getUI()->getIGH().currentHP - 5);
			_viUBullet = _vUBullet.erase(_viUBullet);
		}

		else if (IsCollision(_viUBullet->rc, undybattle->getShieldRECT()))_viUBullet = _vUBullet.erase(_viUBullet);

		else _viUBullet++;
	}

	mindist(undybattle);
}

void undyneFireArrowState::enter(undybattle * undybattle)
{


	//BULLETMANAGER->init("LEFTBULLET_OFF", 10, 600);

	//switch (_bulletDirect)
	//{
	//case LEFTFIRE:
	//	BULLETMANAGER->init("LEFTBULLET_OFF", 10, 600);
	//	break;
	//case RIGHTFIRE:
	//	BULLETMANAGER->init("RIGHTBULLET_OFF", 10, 600);
	//	break;
	//case UPFIRE:
	//	BULLETMANAGER->init("UPBULLET_OFF", 10, 600);
	//	break;
	//case DOWNFIRE:
	//	BULLETMANAGER->init("DOWNBULLET_OFF", 10, 600);
	//	break;
	//
	//}
}

void undyneFireArrowState::render(undybattle * undybattle)
{
	//BULLETMANAGER->render();
	if (_vUBullet.size() != 0)
	{
		for (int i = 0; i < _vUBullet.size(); i++)
		{
			
				_vUBullet[i].image->Render(_vUBullet[i].x, _vUBullet[i].y);
				if (KEYMANAGER->isToggleKey(VK_F1))
				{
					D2DRENDER->DrawRectangle(_vUBullet[i].rc, D2DRenderer::DefaultBrush::Red);
				}
		
		}
	}
}

void undyneFireArrowState::exit(undybattle * undybattle)
{

}

void undyneFireArrowState::undybulletFire(undybattle * undybattle)
{
	
	//_directionSelect = RND->getFromIntTo(0, 3);


	_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
	_undybullet._bulletDirect = RND->getFromIntTo(0, 4);
	

	switch (_undybullet._bulletDirect)
	{
		
	case LEFTFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("LEFTBULLET_OFF");
		_undybullet.x = 0;
		_undybullet.y = (undybattle->getUI()->get_main_rect().bottom + undybattle->getUI()->get_main_rect().top) / 2;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	case RIGHTFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("RIGHTBULLET_OFF");
		_undybullet.x = WINSIZEX;
		_undybullet.y = (undybattle->getUI()->get_main_rect().bottom + undybattle->getUI()->get_main_rect().top) / 2;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	case UPFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("UPBULLET_OFF");
		_undybullet.x = (undybattle->getUI()->get_main_rect().left+ undybattle->getUI()->get_main_rect().right) / 2;
		_undybullet.y = 0;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	case DOWNFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("DOWNBULLET_OFF");
		_undybullet.x = (undybattle->getUI()->get_main_rect().left + undybattle->getUI()->get_main_rect().right) / 2;
		_undybullet.y = WINSIZEY;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	}
	_vUBullet.push_back(_undybullet);
}

void undyneFireArrowState::mindist(undybattle * undybattle)
{
	float dist, minDist;
	int minIndex;
	bool isLeft = false;
	minDist = WINSIZEX;
	minIndex = 0;
	float distance;
	for (int i = 0; i < _vUBullet.size(); i++)
	{
		distance = GetDistance(_vUBullet[i].x, _vUBullet[i].y, undybattle->getUI()->getIGH().x, undybattle->getUI()->getIGH().y);
		
		if (distance <= 100)
		{
			switch (_vUBullet[i]._bulletDirect)
			{
			case 0:
				_vUBullet[i].image = IMAGEMANAGER->FindImage("LEFTBULLET_ON");
				break;

			case 1:
				_vUBullet[i].image = IMAGEMANAGER->FindImage("RIGHTBULLET_ON");
				break;
			case 2:
				_vUBullet[i].image = IMAGEMANAGER->FindImage("UPBULLET_ON");
				break;
			case 3:
				_vUBullet[i].image = IMAGEMANAGER->FindImage("DOWNBULLET_ON");
				break;

			}
			
		}

	}
}
