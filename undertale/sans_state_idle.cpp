#include "stdafx.h"
#include "sans_state_idle.h"
#include "sans_state_attack1.h"
#include "sans_state_attack2.h"
#include "sans_state_attack3.h"
#include "sans_state_attack4.h"
#include "sans_state_attack5.h"
#include "sans_state_attack6.h"


sans_state * sans_state_idle::inputHandle(sansBattle * sansBattle)
{
	battleUI* ui = sansBattle->getUI();
	if (ui->getState() == INGAME)
	{
		//하트 위치 지정
		sansBattle->getUI()->set_inGame_heart_y(sansBattle->getUI()->get_main_rect().bottom);
		if (ui->getBattle_turn() == 0 || ui->getBattle_turn() == 6 ||
			ui->getBattle_turn() == 12 || ui->getBattle_turn() == 18 ||
			ui->getBattle_turn() == 24)
		{
			return new sans_state_attack1();
		}
		if (ui->getBattle_turn() == 1 || ui->getBattle_turn() == 7 ||
			ui->getBattle_turn() == 13 || ui->getBattle_turn() == 19 || 
			ui->getBattle_turn() == 25)
		{
			return new sans_state_attack2();
		}
		if (ui->getBattle_turn() == 2 || ui->getBattle_turn() == 8 ||
			ui->getBattle_turn() == 14 || ui->getBattle_turn() == 20 || 
			ui->getBattle_turn() == 26)
		{
			return new sans_state_attack3();
		}
		if (ui->getBattle_turn() == 3 || ui->getBattle_turn() == 9 ||
			ui->getBattle_turn() == 15 || ui->getBattle_turn() == 21)
		{
			return new sans_state_attack4();
		}
		if (ui->getBattle_turn() == 4 || ui->getBattle_turn() == 10 ||
			ui->getBattle_turn() == 16 || ui->getBattle_turn() == 22)
		{
			return new sans_state_attack5();
		}
		if (ui->getBattle_turn() == 5 || ui->getBattle_turn() == 11 ||
			ui->getBattle_turn() == 17 || ui->getBattle_turn() == 23 ||
			ui->getBattle_turn() == 27)
		{
			return new sans_state_attack6();
		}
	}

	return nullptr;
}

void sans_state_idle::enter(sansBattle * sansBattle)
{

}

void sans_state_idle::update(sansBattle * sansBattle)
{

}

void sans_state_idle::render(sansBattle * sansBattle)
{

}

void sans_state_idle::exit(sansBattle * sansBattle)
{
}
