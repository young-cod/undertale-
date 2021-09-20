#include "stdafx.h"
#include "muffetStateBase.h"
#include "muffetBattle.h"

void muffetStateBase::heart_control(muffetBattle * muffet)
{
	//하트 이동
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		muffet->getUI()->set_inGame_heart_x(muffet->getUI()->getIGH().x - 3);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		muffet->getUI()->set_inGame_heart_x(muffet->getUI()->getIGH().x + 3);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP) && muffet->getUI()->getIGH().rc.top >= muffet->getUI()->get_main_rect().top + 40)
	{
		muffet->getUI()->set_inGame_heart_y(muffet->getUI()->getIGH().y - 40);
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && muffet->getUI()->getIGH().rc.bottom <= muffet->getUI()->get_main_rect().bottom - 40)
	{
		muffet->getUI()->set_inGame_heart_y(muffet->getUI()->getIGH().y + 40);
	}
	//예외처리
	if (muffet->getUI()->get_main_rect().left + 12 >= muffet->getUI()->getIGH().x)
	{
		muffet->getUI()->set_inGame_heart_x(muffet->getUI()->get_main_rect().left + 12);
	}
	if (muffet->getUI()->get_main_rect().right - 12 <= muffet->getUI()->getIGH().x)
	{
		muffet->getUI()->set_inGame_heart_x(muffet->getUI()->get_main_rect().right - 12);
	}
	if (muffet->getUI()->get_main_rect().top + 12 >= muffet->getUI()->getIGH().y)
	{
		muffet->getUI()->set_inGame_heart_y(muffet->getUI()->get_main_rect().top + 12);
	}
	if (muffet->getUI()->get_main_rect().bottom - 12 <= muffet->getUI()->getIGH().y)
	{
		muffet->getUI()->set_inGame_heart_y(muffet->getUI()->get_main_rect().bottom - 12);
	}
}