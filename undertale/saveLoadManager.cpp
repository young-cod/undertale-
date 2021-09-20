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
			WINSIZEX / 2 - 180, WINSIZEY / 2, L"���̺� �Ϸ�", D2D1COLOR::Red, 80, 640, 50, _alpha
		);
	}
	if (_load)
	{
		D2DRENDER->RenderTextField
		(
			WINSIZEX / 2 - 140, WINSIZEY / 2, L"�ε� �Ϸ�", D2D1COLOR::Blue, 80, 640, 50,_alpha
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
	_fcvt_s(����,sizeof,value,count,dec,sign)
	 @@����
	 ��ȯ ����� ������ ������ �����Դϴ�.
	 sizeInBytes
	 @@���� ũ��(����Ʈ)�Դϴ�.
	 value
	 @@��ȯ�� �����Դϴ�.
	 count
	 @@�Ҽ��� ���� �ڸ����Դϴ�.
	 dec
	 @@����� �Ҽ��� ��ġ�� �������Դϴ�.
	 sign
	 @@����� ��ȣ ǥ�ñ��� �������Դϴ�.

	playerX[64] = _fcvt_s(playerX,sizeof(playerX),_pl->getX(),2,&decX,&signX);
	playerY[64] = _fcvt_s(playerY,sizeof(playerY),_pl->getY(),2,&decY,&signY);

	 */
	sceneName = SCENEMANAGER->getSceneName();
	cout << sceneName << endl;

	playerHP[64] = _itoa_s(_player->getHP(), playerHP, sizeof(playerHP), 10);
	playerX[64] = _itoa_s(_player->getX(), playerX, sizeof(playerX), 10);
	playerY[64] = _itoa_s(_player->getY(), playerY, sizeof(playerY), 10);
	playerMove[64] = _itoa_s(_player->getMoveStop(), playerMove, sizeof(playerMove), 10);

	INIDATA->addData("�÷��̾�", "HP", playerHP);
	INIDATA->addData("�÷��̾�", "x", playerX);
	INIDATA->addData("�÷��̾�", "y", playerY);
	INIDATA->addData("�÷��̾�", "move", playerMove);
	INIDATA->addData("��������", "�̸�", sceneName.c_str());

	for (int i = 0; i < INVENTORY->getVInven().size(); i++)
	{
		_vInven.push_back(INVENTORY->getVInven()[i]);
	}

	INIDATA->iniSave("������");
	int HP = INIDATA->loadDataInt("������", "�÷��̾�", "HP");
	float X = INIDATA->loadDataInt("������", "�÷��̾�", "x");
	float Y = INIDATA->loadDataInt("������", "�÷��̾�", "y");
	int move = INIDATA->loadDataInt("������", "�÷��̾�", "move");
	string name = INIDATA->loadDataStr("������", "��������", "�̸�");



	cout << HP << " : HP " << endl;
	cout << X << " : X " << endl;
	cout << Y << " : Y " << endl;
	cout << move << " : moveStop " << endl;
	cout << name << endl;
	cout << "���̺� �Ϸ�" << endl;


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

	int HP = INIDATA->loadDataInt("������", "�÷��̾�", "HP");
	float X = INIDATA->loadDataInt("������", "�÷��̾�", "x");
	float Y = INIDATA->loadDataInt("������", "�÷��̾�", "y");
	int move = INIDATA->loadDataInt("������", "�÷��̾�", "move");
	string name = INIDATA->loadDataStr("������", "��������", "�̸�");

	cout << HP << " : HP " << endl;
	cout << X << " : X " << endl;
	cout << Y << " : Y " << endl;
	cout << move << " : moveStop " << endl;
	cout << name << endl;

	sceneSet();

	_player->setPlayerX(X);
	_player->setPlayerY(Y);
	_player->setMoveStop(move);

	cout << "�ε� �Ϸ�" << endl;

}

void saveLoadManager::sceneSet()
{
	string sceneName = INIDATA->loadDataStr("������", "��������", "�̸�");

	SCENEMANAGER->changeScene(sceneName);
}
