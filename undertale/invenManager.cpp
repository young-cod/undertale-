#include "stdafx.h"
#include "invenManager.h"

HRESULT invenManager::init()
{
	_open = false;
	_invenMax = 8;
	_inven = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2, 600, 400);

	return S_OK;
}


void invenManager::release()
{
}

void invenManager::update()
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		open();
	}
	if (KEYMANAGER->isOnceKeyUp('B'))close();
}

void invenManager::render()
{
	if (_open)
	{
		D2DRENDER->FillRectangle
		(
			_inven,
			D2D1COLOR::Black,
			0.5f
		);

		for (int i = 0; i < _vInven.size(); i++)
		{
			int height = i%4;
			int x = (_inven.left + _inven.right) / 2;
			D2DRENDER->RenderTextField
			(
				(i/4==1)?x:_inven.left+30, 60+(height*95), ConvertCtoWC(_vInven[i].name), D2D1COLOR::White, 15, 280, 20
			);
			D2DRENDER->RenderTextField
			(
				(i / 4 == 1) ? x : _inven.left + 30, 90 + (height * 95), ConvertCtoWC(_vInven[i].description), D2D1COLOR::White, 10, 460, 20
			);
			D2DRENDER->RenderTextField
			(
				(i / 4 == 1) ? x : _inven.left + 30, 120 + (height * 95), L"회복 효과:", D2D1COLOR::White,10,280,20
			);
			char str[128];
			str[64] = _itoa_s(_vInven[i].ablity, str, sizeof(str), 10);
			D2DRENDER->RenderTextField
			(
				(i / 4 == 1) ? x + 60 : _inven.left + 90, 120 + (height * 95), ConvertCtoWC(str), D2D1COLOR::White, 10, 280, 20
			);

		}
	};
}

void invenManager::in(tagItemInfo item)
{
	if (_vInven.size() >= _invenMax)return;
	_vInven.push_back(item);
}

void invenManager::out()
{
	if (_vInven.size() <= 0)return;
	_vInven.pop_back();
	_vInven.resize(_vInven.size());
	cout << _vInven.size() << endl;
}

void invenManager::open()
{
	_open = true;
}

void invenManager::close()
{
	_open = false;
}

void invenManager::clear()
{
	_vInven.clear();
}
