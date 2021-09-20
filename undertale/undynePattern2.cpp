#include "stdafx.h"
#include "undynePattern2.h"

undyneState * undynePattern2::inputHandle(undybattle * undybattle)
{
	if (undybattle->getUI()->getState() != INGAME)
	{
		return new undyneIdle();
	}
	return nullptr;
}

void undynePattern2::update(undybattle * undybattle)
{

	mindist(undybattle);
	_timer++;

	undybattle->getUI()->setEnemy_attackTime_max(1000);

	if (_timer % 20 == 0)
	{
		undybulletFire(undybattle);
	}


	if (_vUBullet.size() != 0)
	{

		for (int i = 0; i < _vUBullet.size(); i++)
		{
			distance = GetDistance(_vUBullet[i].x, _vUBullet[i].y, undybattle->getUI()->getIGH().x, undybattle->getUI()->getIGH().y);

			switch (_vUBullet[i]._bulletDirect)
			{
			case LEFTFIRE:
				_vUBullet[i].x += cosf(_vUBullet[i].angle) * 5;
				_vUBullet[i].y += sinf(_vUBullet[i].angle) * 5;
				_vUBullet[i].rc = RectMake(_vUBullet[i].x, _vUBullet[i].y, _vUBullet[i].image->GetWidth(), _vUBullet[i].image->GetHeight());
				
				break;

			case RIGHTFIRE:
				_vUBullet[i].x += cosf(_vUBullet[i].angle) * 5;
				_vUBullet[i].y += sinf(_vUBullet[i].angle) * 5;
				_vUBullet[i].rc = RectMake(_vUBullet[i].x, _vUBullet[i].y, _vUBullet[i].image->GetWidth(), _vUBullet[i].image->GetHeight());

				break;
			case UPFIRE:
				_vUBullet[i].x += cosf(_vUBullet[i].angle) * 5;
				_vUBullet[i].y += -sinf(_vUBullet[i].angle) * 5;
				_vUBullet[i].rc = RectMake(_vUBullet[i].x, _vUBullet[i].y, _vUBullet[i].image->GetWidth(), _vUBullet[i].image->GetHeight());

				break;
			case DOWNFIRE:
				_vUBullet[i].x += cosf(_vUBullet[i].angle) * 5;
				_vUBullet[i].y += -sinf(_vUBullet[i].angle) * 5;
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
}

void undynePattern2::enter(undybattle * undybattle)
{
}

void undynePattern2::render(undybattle * undybattle)
{
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

void undynePattern2::exit(undybattle * undybattle)
{
}

void undynePattern2::undybulletFire(undybattle * undybattle)
{
	_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
	_undybullet._bulletDirect = RND->getFromIntTo(0, 4);


	switch (_undybullet._bulletDirect)
	{

	case LEFTFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("LEFTBULLET_FAKE");
		_undybullet.x = 0;
		_undybullet.y = (undybattle->getUI()->get_main_rect().bottom + undybattle->getUI()->get_main_rect().top) / 2;
		_undybullet.angle =-1;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	case RIGHTFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("RIGHTBULLET_FAKE");
		_undybullet.x = WINSIZEX;
		_undybullet.y = (undybattle->getUI()->get_main_rect().bottom + undybattle->getUI()->get_main_rect().top) / 2;
		_undybullet.angle = PI+1;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	case UPFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("UPBULLET_FAKE");
		_undybullet.x = (undybattle->getUI()->get_main_rect().left + undybattle->getUI()->get_main_rect().right) / 2;
		_undybullet.y = 0;
		_undybullet.angle = PI * 1.5 +1;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	case DOWNFIRE:
		_undybullet.image = IMAGEMANAGER->FindImage("DOWNBULLET_FAKE");
		_undybullet.x = (undybattle->getUI()->get_main_rect().left + undybattle->getUI()->get_main_rect().right) / 2;
		_undybullet.y = WINSIZEY;
		_undybullet.angle = PI / 2 + 1;
		_undybullet.rc = RectMakeCenter(_undybullet.x, _undybullet.y, 10, 10);
		break;
	}
	_vUBullet.push_back(_undybullet);
}

void undynePattern2::mindist(undybattle * undybattle)
{
	float dist, minDist;
	int minIndex;
	bool isLeft = false;
	minDist = WINSIZEX;
	minIndex = 0;

	for (int i = 0; i < _vUBullet.size(); i++)
	{
		distance = GetDistance(_vUBullet[i].x, _vUBullet[i].y, undybattle->getUI()->getIGH().x, undybattle->getUI()->getIGH().y);
		{
			switch (_vUBullet[i]._bulletDirect)
			{
			case 0:
				if (_vUBullet[i].x > undybattle->getUI()->get_main_rect().left - 150)
				{
					if (_vUBullet[i].y > (undybattle->getUI()->get_main_rect().left + undybattle->getUI()->get_main_rect().right) / 2)
					{
						_vUBullet[i].angle = PI;
						
					}
					else _vUBullet[i].angle += 0.02f;
				}
				break;

			case 1:
				if (_vUBullet[i].x < undybattle->getUI()->get_main_rect().right + 150)
				{
					if (_vUBullet[i].y > (undybattle->getUI()->get_main_rect().left + undybattle->getUI()->get_main_rect().right) / 2)
					{
						_vUBullet[i].angle = 0;
						cout << _vUBullet[i].angle << endl;
					}
					else _vUBullet[i].angle -= 0.02f;
				}
				break;

			case 2:
				if (_vUBullet[i].y > undybattle->getUI()->get_main_rect().top - 150)
				{
					if (_vUBullet[i].x < (undybattle->getUI()->get_main_rect().top + undybattle->getUI()->get_main_rect().bottom) / 2)
					{
						_vUBullet[i].angle = PI / 2;
					
					}
					else _vUBullet[i].angle -= 0.02f;
				}
				break;
			case 3:
				if (_vUBullet[i].y < undybattle->getUI()->get_main_rect().bottom)
				{
					if (_vUBullet[i].x > (undybattle->getUI()->get_main_rect().top + undybattle->getUI()->get_main_rect().bottom) / 2)
					{
						_vUBullet[i].angle = PI*1.5;
						cout << _vUBullet[i].angle << endl;
					}
					else _vUBullet[i].angle -= 0.02f;
				}
				break;

			}

		}
	}
}