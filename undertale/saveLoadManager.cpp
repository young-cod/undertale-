#include "stdafx.h"
#include "saveLoadManager.h"
#include "player.h"

saveLoadManager::saveLoadManager()
{
}

saveLoadManager::~saveLoadManager()
{
}

HRESULT saveLoadManager::init()
{
	_alpha = 1.f;
	_timer = 1;
	_go = false;
	_save = false;
	_load = false;

	return S_OK;
}

void saveLoadManager::release()
{
}

void saveLoadManager::update()
{
	if (_go)_timer++;
	if (KEYMANAGER->isOnceKeyDown('O'))save();
	if (KEYMANAGER->isOnceKeyDown('P'))load();
}

void saveLoadManager::render()
{
	if (_timer % 3 == 0)
	{
		_timer = 0;
		_alpha -= 0.08f;
	}

	if (_alpha <= 0)
	{
		_alpha = 1.f;
		_go = false;
		_save = false;
		_load = false;
	}
	if (_save)
	{
		D2DRENDER->RenderTextField
		(
			WINSIZEX / 2 - 180, WINSIZEY / 2, L"세이브 완료", D2D1COLOR::Red, 80, 640, 50, _alpha
		);
	}
	if (_load)
	{
		D2DRENDER->RenderTextField
		(
			WINSIZEX / 2 - 140, WINSIZEY / 2, L"로드 완료", D2D1COLOR::Blue, 80, 640, 50,_alpha
		);
	}

}

void saveLoadManager::save()
{
	_go = true;
	_save = true;
	_alpha = 1.f;
	_timer++;

	char playerHP[128];
	char playerX[128];
	char playerY[128];
	char playerMove[128];

	string sceneName;
	int decX, signX;
	int decY, signY;

	/*
	_fcvt_s(버퍼,sizeof,value,count,dec,sign)
	 @@버퍼
	 변환 결과를 포함할 제공된 버퍼입니다.
	 sizeInBytes
	 @@버퍼 크기(바이트)입니다.
	 value
	 @@변환할 숫자입니다.
	 count
	 @@소수점 뒤의 자릿수입니다.
	 dec
	 @@저장된 소수점 위치의 포인터입니다.
	 sign
	 @@저장된 부호 표시기의 포인터입니다.

	playerX[64] = _fcvt_s(playerX,sizeof(playerX),_pl->getX(),2,&decX,&signX);
	playerY[64] = _fcvt_s(playerY,sizeof(playerY),_pl->getY(),2,&decY,&signY);

	 */
	sceneName = SCENEMANAGER->getSceneName();
	cout << sceneName << endl;

	playerHP[64] = _itoa_s(_player->getHP(), playerHP, sizeof(playerHP), 10);
	playerX[64] = _itoa_s(_player->getX(), playerX, sizeof(playerX), 10);
	playerY[64] = _itoa_s(_player->getY(), playerY, sizeof(playerY), 10);
	playerMove[64] = _itoa_s(_player->getMoveStop(), playerMove, sizeof(playerMove), 10);

	INIDATA->addData("플레이어", "HP", playerHP);
	INIDATA->addData("플레이어", "x", playerX);
	INIDATA->addData("플레이어", "y", playerY);
	INIDATA->addData("플레이어", "move", playerMove);
	INIDATA->addData("스테이지", "이름", sceneName.c_str());

	for (int i = 0; i < INVENTORY->getVInven().size(); i++)
	{
		_vInven.push_back(INVENTORY->getVInven()[i]);
	}

	INIDATA->iniSave("우전없");
	int HP = INIDATA->loadDataInt("우전없", "플레이어", "HP");
	float X = INIDATA->loadDataInt("우전없", "플레이어", "x");
	float Y = INIDATA->loadDataInt("우전없", "플레이어", "y");
	int move = INIDATA->loadDataInt("우전없", "플레이어", "move");
	string name = INIDATA->loadDataStr("우전없", "스테이지", "이름");



	cout << HP << " : HP " << endl;
	cout << X << " : X " << endl;
	cout << Y << " : Y " << endl;
	cout << move << " : moveStop " << endl;
	cout << name << endl;
	cout << "세이브 완료" << endl;


}

void saveLoadManager::load()
{
	_go = true;
	_load = true;
	_alpha = 1.f;

	INVENTORY->clear();
	for (int i = 0; i < _vInven.size(); i++)
	{
		INVENTORY->in(_vInven[i]);
	}

	int HP = INIDATA->loadDataInt("우전없", "플레이어", "HP");
	float X = INIDATA->loadDataInt("우전없", "플레이어", "x");
	float Y = INIDATA->loadDataInt("우전없", "플레이어", "y");
	int move = INIDATA->loadDataInt("우전없", "플레이어", "move");
	string name = INIDATA->loadDataStr("우전없", "스테이지", "이름");

	cout << HP << " : HP " << endl;
	cout << X << " : X " << endl;
	cout << Y << " : Y " << endl;
	cout << move << " : moveStop " << endl;
	cout << name << endl;

	sceneSet();

	_player->setPlayerX(X);
	_player->setPlayerY(Y);
	_player->setMoveStop(move);

	cout << "로드 완료" << endl;

}

void saveLoadManager::sceneSet()
{
	string sceneName = INIDATA->loadDataStr("우전없", "스테이지", "이름");

	SCENEMANAGER->changeScene(sceneName);
}
