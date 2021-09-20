#include "stdafx.h"
#include "muffetBattle.h"
#include "muffetIdle.h"

HRESULT muffetBattle::init()
{
	_btUI = new battleUI;
	_btUI->init(2);

	addMuffetImage();
	setImage();

	_muffetState = new muffetIdle;
	_muffetState->enter(this);

	//_muffet = ImageManager::GetInstance()->FindImage("muffet");
	_currentFrameX = 0;
	_downMove = false;
	_downFixcel = 0;
	i = 0;

	_invincibility = 0;
	_isInvin = false;
	return S_OK;
}

void muffetBattle::release()
{
}

void muffetBattle::update()
{
	//�� �Ʒ��� ����̴� ������
	_count++;

	if (_count % 70)
	{
		if (i != 20)
		{
			if (_muffetV[0].y <= 52)
			{
				_muffetV[i].y++;

			}
			else if (_muffetV[0].y >= 50)
			{
				_muffetV[i].y--;
			}

		}
		i++;

		if (i >= _muffetV.size()) i = 0;
		_count = 0;
	}

	inPutHandle();

	_muffetState->update(this);
	_muffetState->heart_control(this);
	_btUI->update();
	collision();
}

void muffetBattle::render()
{
	for (int i = 0; i < _muffetV.size(); i++)
	{
		if (_muffetV[i].isFrameImage)
		{
			_muffetV[i].img->autoFrameRender(_muffetV[i].x, _muffetV[i].y, _muffetV[i].currentFrameX, 1, 10);
		}
		else if (!_muffetV[i].isFrameImage && _muffetV[i].angle == 0)
		{
			_muffetV[i].img->Render(_muffetV[i].x, _muffetV[i].y);
		}
		if (_muffetV[i].angle != 0)
		{
			_muffetV[i].img->Render(_muffetV[i].x, _muffetV[i].y, 1, 1, _muffetV[i].angle);
		}
	}

	_btUI->render();

	_muffetState->render(this);
	//_muffetState->drawNet(this);
}

void muffetBattle::inPutHandle()
{
	muffetStateBase* newState = _muffetState->inputHandle(this);
	if (newState != nullptr)
	{
		SAFE_DELETE(_muffetState);
		_muffetState = newState;
		_muffetState->enter(this);
	}
}


void muffetBattle::collision()
{
	//�Ѿ� �浹
	for (int i = 0; i < _muffetState->getvBullet().size(); i++)
	{
		if (IsCollision(_btUI->getIGH().rc, _muffetState->getBulletRect(i)) && !_isInvin)
		{
			_btUI->set_inGame_heart_currentHp(_btUI->getIGH().currentHP - 5);

			_isInvin = true;
		}
	}
	//���� �ð� ���
	if (_isInvin)
	{
		_invincibility++;
		if (_invincibility % 30 == 0)
		{
			_isInvin = false;
			_invincibility = 0;
		}
	}
}



//�̹��� �ֵ�. (��ϴ�)
void muffetBattle::addMuffetImage()
{
	ImageManager::GetInstance()->AddImage("muffet_head", L"�����̹���/head.png");
	ImageManager::GetInstance()->AddImage("muffet_hair_L", L"�����̹���/hair.png");
	ImageManager::GetInstance()->AddImage("muffet_hair_R", L"�����̹���/hair2.png");

	ImageManager::GetInstance()->AddFrameImage("muffet_eye1", L"�����̹���/eye1.png", 7, 1);
	ImageManager::GetInstance()->AddFrameImage("muffet_eye2", L"�����̹���/eye2.png", 7, 1);
	ImageManager::GetInstance()->AddFrameImage("muffet_eye3", L"�����̹���/eye3.png", 7, 1);
	ImageManager::GetInstance()->AddFrameImage("muffet_eye4", L"�����̹���/eye4.png", 7, 1);
	ImageManager::GetInstance()->AddFrameImage("muffet_eye5", L"�����̹���/eye5.png", 7, 1);

	ImageManager::GetInstance()->AddImage("muffet_shoulder_top", L"�����̹���/shoulder.png");
	ImageManager::GetInstance()->AddImage("muffet_shoulder_bottom", L"�����̹���/shoulder2.png");

	ImageManager::GetInstance()->AddImage("muffet_arm1", L"�����̹���/teaglass left.png");
	ImageManager::GetInstance()->AddImage("muffet_arm2", L"�����̹���/teaglass right.png");
	ImageManager::GetInstance()->AddImage("muffet_arm3", L"�����̹���/arm left.png");
	ImageManager::GetInstance()->AddImage("muffet_arm4", L"�����̹���/arm right.png");

	ImageManager::GetInstance()->AddImage("muffet_arm5", L"�����̹���/bottom arm left.png");
	ImageManager::GetInstance()->AddImage("muffet_arm6", L"�����̹���/bottom arm right.png");

	ImageManager::GetInstance()->AddImage("muffet_arm7", L"�����̹���/bottom arm fist left.png");
	ImageManager::GetInstance()->AddImage("muffet_arm8", L"�����̹���/bottom arm fist right.png");

	ImageManager::GetInstance()->AddImage("muffet_hand_L", L"�����̹���/teaport left.png");
	ImageManager::GetInstance()->AddImage("muffet_hand_R", L"�����̹���/teaport right.png");

	ImageManager::GetInstance()->AddImage("muffet_body_top", L"�����̹���/body top.png");
	ImageManager::GetInstance()->AddImage("muffet_body_bottom", L"�����̹���/body bottom.png");
	ImageManager::GetInstance()->AddImage("muffet_leg", L"�����̹���/leg.png");


	ImageManager::GetInstance()->AddImage("muffet_hit", L"�����̹���/hit.png");
	ImageManager::GetInstance()->AddImage("muffet_samfle", L"�����̹���/battle.png");

	//===========================����Ʈ �� ���� �̹���===================================================
	ImageManager::GetInstance()->AddImage("muffet_dounut", L"�����̹���/dounut.png");
	ImageManager::GetInstance()->AddImage("muffet_croissant", L"�����̹���/croissant.png");
	ImageManager::GetInstance()->AddImage("muffet_flower", L"�����̹���/flower.png");
	ImageManager::GetInstance()->AddImage("muffet_muffin", L"�����̹���/muffin.png");
	ImageManager::GetInstance()->AddFrameImage("muffet_next_close", L"�����̹���/next close.png", 5, 1);
	ImageManager::GetInstance()->AddFrameImage("muffet_next_open", L"�����̹���/next open.png", 5, 1);
	ImageManager::GetInstance()->AddImage("muffet_paper", L"�����̹���/paper.png");
	ImageManager::GetInstance()->AddFrameImage("muffet_pet_down", L"�����̹���/pet down.png", 4, 1);
	ImageManager::GetInstance()->AddImage("muffet_paper", L"�����̹���/paper.png");
	ImageManager::GetInstance()->AddFrameImage("muffet_pet_side", L"�����̹���/pet side.png", 2, 1);
	ImageManager::GetInstance()->AddImage("muffet_puple", L"�����̹���/puple.png");
	ImageManager::GetInstance()->AddFrameImage("muffet_spider_move", L"�����̹���/spider move.png", 2, 1);
	ImageManager::GetInstance()->AddImage("muffet_spider", L"�����̹���/spider.png");
}

//�̹��� ����. (��ϴ�)
void muffetBattle::setImage()
{
	/*_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_samfle");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = WINSIZEX / 2;
	_mfImage.y = 90;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 17, 24);

	_muffetV.push_back(_mfImage);*/

	//�Ӹ� �Ӹ�ī�� LR==================================
	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_hair_L");
	_mfImage.angle = 0;
	_mfImage.x = 285;
	_mfImage.y = 50;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 15, 16);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_hair_R");
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 51;
	_mfImage.y = _muffetV.begin()->y;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 15, 16);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_head");
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 10;
	_mfImage.y = _muffetV.begin()->y;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 46, 50);

	_muffetV.push_back(_mfImage);
	//========================================================
	//2
	//��1~5===================================================
	_mfImage.isFrameImage = true;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_eye1");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 22;
	_mfImage.y = _muffetV.begin()->y + 21;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 7, 9);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = true;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_eye2");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 25;
	_mfImage.y = _muffetV.begin()->y + 16;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 5, 5);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = true;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_eye3");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 31;
	_mfImage.y = _muffetV.begin()->y + 12;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 5, 5);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = true;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_eye4");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 36;
	_mfImage.y = _muffetV.begin()->y + 16;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 9, 9);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = true;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_eye5");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 37;
	_mfImage.y = _muffetV.begin()->y + 21;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 7, 9);

	_muffetV.push_back(_mfImage);
	//========================================================
	//7
	//���=====================================================
	_mfImage.isFrameImage = true;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_shoulder_top");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 15;
	_mfImage.y = _muffetV.begin()->y + 43;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 36, 18);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = true;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_shoulder_bottom");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 13;
	_mfImage.y = _muffetV.begin()->y + 58;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 36, 18);

	_muffetV.push_back(_mfImage);
	////===========================================================
	////9
	////��1~4======================================================
	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm1");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x - 11;
	_mfImage.y = _muffetV.begin()->y + 38;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 27, 22);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm2");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 50;
	_mfImage.y = _muffetV.begin()->y + 38;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 27, 22);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm3");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x - 2;
	_mfImage.y = _muffetV.begin()->y + 56;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 15, 17);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm4");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 54;
	_mfImage.y = _muffetV.begin()->y + 56;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 15, 17);

	_muffetV.push_back(_mfImage);
	//====================================
	//13
	//�Ʒ� ��1, 2==========================
	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm5");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 15;
	_mfImage.x = _muffetV.begin()->x + 15;
	_mfImage.y = _muffetV.begin()->y + 63;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 10, 33);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm6");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 345;
	_mfImage.x = _muffetV.begin()->x + 38;
	_mfImage.y = _muffetV.begin()->y + 67;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 10, 33);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm7");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 15;
	_mfImage.y = _muffetV.begin()->y + 66;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 15, 32);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_arm8");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 40;
	_mfImage.y = _muffetV.begin()->y + 66;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 15, 32);

	_muffetV.push_back(_mfImage);

	////========================
	////18
	////Ƽ��Ʈ=========================
	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_hand_L");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x - 25;
	_mfImage.y = _muffetV.begin()->y + 50;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 24, 17);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_hand_R");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 68;
	_mfImage.y = _muffetV.begin()->y + 50;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 24, 17);

	_muffetV.push_back(_mfImage);
	////======================================================
	////20
	////��==============================================
	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_leg");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 24;
	_mfImage.y = _muffetV.begin()->y + 85;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 17, 24);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_body_bottom");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 20;
	_mfImage.y = _muffetV.begin()->y + 60;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 25, 26);

	_muffetV.push_back(_mfImage);


	_mfImage.isFrameImage = false;
	_mfImage.img = ImageManager::GetInstance()->FindImage("muffet_body_top");
	_mfImage.currentFrameX = 0;
	_mfImage.angle = 0;
	_mfImage.x = _muffetV.begin()->x + 24;
	_mfImage.y = _muffetV.begin()->y + 48;
	_mfImage.rc = RectMake(_mfImage.x, _mfImage.y, 18, 16);

	_muffetV.push_back(_mfImage);

}
