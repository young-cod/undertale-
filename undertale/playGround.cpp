#include "stdafx.h"
#include "playGround.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")


playGround::playGround()
{
	
}


playGround::~playGround()
{
}

//�ʱ�ȭ �Լ�
HRESULT playGround::init()
{
	gameNode::init(true);;

	_sm = new stageManager;
	_sm->init();

	//===========��ȣ������ ��ũ


	//==========================

	return S_OK;
}

//�޸� ����
void playGround::release()
{
}

//����
void playGround::update()
{
	gameNode::update();

	_sm->update();

	
	CAMERAMANAGER->mousePoint();
}

//�׸��� ����
void playGround::render()
{
	//����� �ʱ�ȭ
	D2DRENDER->BeginRender(D2D1::ColorF::Black);

	_sm->render();


	CAMERAMANAGER->render();

	//����ۿ� �׸� ������� ȭ�鿡 �ѷ���~
	D2DRENDER->EndRender();
}
