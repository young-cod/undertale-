#include "stdafx.h"
#include "undyne.h"

HRESULT undyne::init()
{
	ImageManager::GetInstance()->AddFrameImage("undyneEyespark", L"Undyne/Und_eyeSpark.png", 9, 1);
	_fullbody.x = WINSIZEX / 2 - 50;
	_fullbody.y = 1100;
	_fullbody.rc = RectMakeCenter(_fullbody.x, _fullbody.y, 80, 100);
	_fullbody.img = ImageManager::GetInstance()->FindImage("undyneEyespark");
	_fullbody.currentFrameX = _fullbody.currentFrameY = 0;

	return S_OK;
}

void undyne::release()
{
}

void undyne::update()
{
	_count++;

	if (_count % 5 == 0)
	{
		_fullbody.currentFrameX++;
		if (_fullbody.currentFrameX >= _fullbody.img->GetMaxFrameX())_fullbody.currentFrameX = 0;
		_fullbody.currentFrameY = 0;
	}
}

void undyne::render()
{
	D2DRENDER->DrawRectangle
	(
		_fullbody.rc,
		D2DRenderer::DefaultBrush::Red, 1.f
	);
	_fullbody.img->FrameRender(_fullbody.rc.left, _fullbody.rc.top, _fullbody.currentFrameX, _fullbody.currentFrameY, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f);

}


