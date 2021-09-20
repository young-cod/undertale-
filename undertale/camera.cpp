#include "stdafx.h"
#include "camera.h"

camera::camera()
{
}

camera::~camera()
{
}

HRESULT camera::init()
{
	_camera.x = WINSIZEX / 2;
	_camera.y = WINSIZEY / 2;
	_camera.width = WINSIZEX;
	_camera.height = WINSIZEY;

	_camera.rc = RectMakeCenter(_camera.x, _camera.y, WINSIZEX, WINSIZEY);

	return S_OK;
}

void camera::release()
{
}

void camera::update()
{
}

void camera::render()
{
	D2DRENDER->DrawRectangle
	(
		_camera.rc,
		D2DRenderer::DefaultBrush::White
	);
}

void camera::cameraRange()
{
	//가로 축
	if (_camera.rc.left < 0) _camera.rc.left = 0;
	else if (_camera.x + _camera.width / 2 > _map.width)_camera.rc.left = (_map.width - _camera.width);
	//세로 축
	if (_camera.rc.top < 0)_camera.rc.top = 0;
	else if (_camera.y + _camera.height / 2 > 0) _camera.rc.top = (_map.height - _camera.height);
}

//void camera::setCamera(float x, float y)
//{
//	if (x > (WINSIZEX / 2))
//	{
//		playerX += x-WINSIZEX/2;
//		_camera.rc.left = -(playerX - _camera.width / 2);
//		x = _camera.width / 2 - 30;
//	}
//	cout << playerX << "플레이어 리얼 X" << endl;
//	//camera.rc.left = x - _camera.width / 2;
//	//camera.rc.top = y - _camera.height / 2;
//}

void camera::setImgCamera(float x, float y)
{
	_map.width = x;
	_map.height = y;
}

void camera::setPlayerCamera(float& x, float& y)
{
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
}

void camera::updateCamera(float x, float y)
{
	if (x - _camera.width * 0.5 < 0)
	{
		x = 0;
	}
	else if (x + _camera.width * (1 - 0.5) > _map.width)
	{
		x = _map.width - _camera.width;
	}
	else
	{
		x -= _camera.width * 0.5;
	}

	//Y축 (상, 하)

	if (y - _camera.height * 0.5 < 0)
	{
		y = 0;
	}
	else if (y + _camera.height * (1 - 0.5) > _map.height)
	{
		y = _map.height - _camera.height;
	}
	else
	{
		y -= _camera.height * 0.5;
	}

	//갱신
	_x = x;
	_y = y;

}

void camera::updateCamera(RECT& player)
{
	float x = (player.left + player.right) / 2;
	float y = (player.top + player.bottom) / 2;

	x += _camera.rc.left*0.5;
	y += _camera.rc.top*0.5;

	player.left += _camera.rc.left*0.5;
	player.top += _camera.rc.top*0.5;


	//가로 축
	if (x - (_camera.width*0.5) < 0)_camera.rc.left = 0;
	else if (x + (_camera.width*0.5) > _map.width)
	{
		_camera.rc.left = _map.width - _camera.width;
	}
	else _camera.rc.left -= x - (_camera.width*0.5);

	//세로 축
	if (y - (_camera.height*0.5) < 0)_camera.rc.top = 0;
	else if (y + (_camera.height*0.5) > _map.height)_camera.rc.top = _map.height - _camera.height;
	else _camera.rc.top -= _camera.height*0.5;

	_camera.x = x;
	_camera.y = y;

	//_camera.rc = RectMakeCenter(_camera.x, _camera.y, WINSIZEX, WINSIZEY);
}

void camera::updateCamera(RECT & player, float ratio)
{

}

void camera::updateCamera(RECT & player, float&  x, float&  y)
{
	
	
}

void camera::updateCamera(RECT& player, float ratioX, float ratioY, float ratioX2, float ratioY2)
{
	if (ratioX > 0 && ratioX < 0.5f)
	{
		if (player.left < _camera.x + ratioX * WINSIZEX)
		{
			_camera.x = (player.left - ratioX * WINSIZEX);
		}
	}

	if (ratioX2 > 0.5f && ratioX2 < 1.0f)
	{
		if (player.right > _camera.x + ratioX2 * WINSIZEX)
		{
			_camera.x = (player.right - ratioX2 * WINSIZEX);
		}
	}

	if (ratioY > 0 && ratioY < 0.5f)
	{
		if (player.top < _camera.y + ratioY * WINSIZEY)
		{
			_camera.y = (player.top - ratioY * WINSIZEY);
		}
	}

	if (ratioY2 > 0.5f && ratioY2 < 1.0f)
	{
		if (player.bottom > _camera.y + ratioY2 * WINSIZEY)
		{
			_camera.y = (player.bottom - ratioY2 * WINSIZEY);
		}
	}
	cameraRange();

}
