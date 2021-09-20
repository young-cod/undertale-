#include "stdafx.h"
#include "sans_state.h"
#include "sansBattle.h"

void sans_state::heart_control(sansBattle* sansBattle, bool gravity_bool, float gravity, float jumpPower)
{

	switch (gravity_bool)
	{
	case 0:
		//하트 이동
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))sansBattle->getUI()->set_inGame_heart_x(sansBattle->getUI()->getIGH().x - 3);
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))sansBattle->getUI()->set_inGame_heart_x(sansBattle->getUI()->getIGH().x + 3);
		if (KEYMANAGER->isStayKeyDown(VK_UP))sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->getIGH().y - 3);
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->getIGH().y + 3);
		break;
	case 1:
		//하트 이동
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))sansBattle->getUI()->set_inGame_heart_x(sansBattle->getUI()->getIGH().x - 3);
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))sansBattle->getUI()->set_inGame_heart_x(sansBattle->getUI()->getIGH().x + 3);
		if (KEYMANAGER->isOnceKeyDown(VK_UP) && !_isJump)
		{
			_jumpPower = jumpPower;
			_isJump = true;
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->getIGH().y + 3);


		break;
	}
	if (_isJump)
	{
		sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->getIGH().y - _jumpPower);
		_jumpPower -= gravity;
	}
	//예외처리
	if (sansBattle->getUI()->get_main_rect().left + 12 >= sansBattle->getUI()->getIGH().x)
		sansBattle->getUI()->set_inGame_heart_x(sansBattle->getUI()->get_main_rect().left + 12);

	if (sansBattle->getUI()->get_main_rect().right - 12 <= sansBattle->getUI()->getIGH().x)
		sansBattle->getUI()->set_inGame_heart_x(sansBattle->getUI()->get_main_rect().right - 12);

	if (sansBattle->getUI()->get_main_rect().top + 12 >= sansBattle->getUI()->getIGH().y)
		sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->get_main_rect().top + 12);

	if (sansBattle->getUI()->get_main_rect().bottom - 12 <= sansBattle->getUI()->getIGH().y)
		sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->get_main_rect().bottom - 12);

	if (sansBattle->getUI()->get_main_rect().bottom - 12 <= sansBattle->getUI()->getIGH().y) _isJump = false;
}
//상태별 충돌임 현재 사용 x
void sans_state::collision(sansBattle* sansBattle, RECT rect)
{

	if (IsCollision(rect, sansBattle->getUI()->getIGH().rc))
	{
		sansBattle->getUI()->set_inGame_heart_currentHp(sansBattle->getUI()->getIGH().currentHP - 5);
	}

}
