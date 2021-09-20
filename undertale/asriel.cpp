#include "stdafx.h"
#include "asriel.h"

HRESULT asriel::init()
{
	imgSet();
	asrielSet();

	return S_OK;
}

void asriel::release()
{
}

void asriel::update()
{
}

void asriel::render()
{
	_asriel.img->autoFrameRender(_asriel.x, _asriel.y, _asriel.currentFrameX, _asriel.currentFrameY,5);
}

void asriel::imgSet()
{
	//인트로 이미지
	IMAGEMANAGER->AddFrameImage("back", L"asriel/back_14x1.png", 14, 1);
	IMAGEMANAGER->AddFrameImage("front", L"asriel/front_6x1.png",6, 1);

	//풀 바디
	IMAGEMANAGER->AddImage("fullBody", L"asriel/fullBody.png");
	IMAGEMANAGER->AddImage("fullBodyEffect", L"asriel/fullBody_effect.png");

	//바디 파츠
	IMAGEMANAGER->AddFrameImage("partsFace1", L"asriel/bodyParts/face1_5x1.png",5,1);
	IMAGEMANAGER->AddFrameImage("partsFace2", L"asriel/bodyParts/face2_8x1.png",8,1);
	IMAGEMANAGER->AddImage("partsArm", L"asriel/bodyParts/arm.png");
	IMAGEMANAGER->AddImage("partsBody", L"asriel/bodyParts/body.png");
	IMAGEMANAGER->AddImage("partsFoot", L"asriel/bodyParts/foot.png");
	IMAGEMANAGER->AddImage("partsNeck", L"asriel/bodyParts/neck.png");
	IMAGEMANAGER->AddImage("partsNecklace", L"asriel/bodyParts/necklace.png");
	IMAGEMANAGER->AddImage("partsNeckSide", L"asriel/bodyParts/neckSide.png");
	IMAGEMANAGER->AddImage("partsUpArm", L"asriel/bodyParts/upArm.png");

	//불렛 이미지
	IMAGEMANAGER->AddFrameImage("fireBullet", L"asriel/fireBullet_2x1.png",2,1);


}

void asriel::asrielSet()
{
	_asriel.img = IMAGEMANAGER->FindImage("partsFace2");
	_asriel.x = WINSIZEX / 2;
	_asriel.y = WINSIZEY / 2;

	_asriel.currentFrameX = _asriel.currentFrameY = 0;

	_asriel.armL.img = IMAGEMANAGER->FindImage("partsFace1");
	_asriel.armL.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.armR.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.body.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.foot.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.neck.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.necklace.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.neckSide.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.upArmL.img = IMAGEMANAGER->FindImage("partsArm");
	_asriel.upArmR.img = IMAGEMANAGER->FindImage("partsArm");
}
