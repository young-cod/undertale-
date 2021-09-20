#include "stdafx.h"
#include "battleUI.h"

battleUI::battleUI()
{
}

battleUI::~battleUI()
{
}

HRESULT battleUI::init(int bossName)
{
	
	
	IMAGEMANAGER->AddFrameImage("RED", L"hearts/RED.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("RED_DAMAGED", L"hearts/RED_DAMAGED.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("RED_RUN", L"hearts/RED_RUN.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("BLUE", L"hearts/BLUE.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("BLUE_DAMAGED", L"hearts/BLUE_DAMAGED.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("BLUE_LEFT", L"hearts/BLUE_LEFT.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("BLUE_LEFT_DAMAGED", L"hearts/BLUE_LEFT_DAMAGED.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("BLUE_RIGHT", L"hearts/BLUE_RIGHT.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("BLUE_RIGHT_DAMAGED", L"hearts/BLUE_RIGHT_DAMAGED.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("BLUE_UP", L"hearts/BLUE_UP.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("BLUE_UP_DAMAGED", L"hearts/BLUE_UP_DAMAGED.png", 2, 1);
	IMAGEMANAGER->AddImage("GREEN", L"hearts/GREEN.png");
	IMAGEMANAGER->AddFrameImage("GREEN_DAMAGED", L"hearts/GREEN_DAMAGED.png", 2, 1);
	IMAGEMANAGER->AddFrameImage("PURPLE", L"hearts/PURPLE.png", 1, 1);
	IMAGEMANAGER->AddFrameImage("PURPLE_DAMAGED", L"hearts/PURPLE_DAMAGED.png", 2, 1);

	_menu_off[0] = IMAGEMANAGER->AddImage("공격_off", L"UI이미지/UI_공격_비활성화_110_42.png");
	_menu_off[1] = IMAGEMANAGER->AddImage("행동_off", L"UI이미지/UI_행동_비활성화_110_42.png");
	_menu_off[2] = IMAGEMANAGER->AddImage("아이템_off", L"UI이미지/UI_아이템_비활성화_110_42.png");
	_menu_off[3] = IMAGEMANAGER->AddImage("자비_off", L"UI이미지/UI_자비_비활성화_110_42.png");
	_menu_on[0] = IMAGEMANAGER->AddImage("공격_on", L"UI이미지/UI_공격_활성화_110_42.png");
	_menu_on[1] = IMAGEMANAGER->AddImage("행동_on", L"UI이미지/UI_행동_활성화_110_42.png");
	_menu_on[2] = IMAGEMANAGER->AddImage("아이템_on", L"UI이미지/UI_아이템_활성화_110_42.png");
	_menu_on[3] = IMAGEMANAGER->AddImage("자비_on", L"UI이미지/UI_자비_활성화_110_42.png");
	_heart = IMAGEMANAGER->AddImage("하트", L"UI이미지/UI_하트_20_20.png");
	_speechBubble = IMAGEMANAGER->AddImage("말풍선오른쪽", L"UI이미지/UI_말풍선_오른쪽_237_130.png");
	_attack_ground = IMAGEMANAGER->AddImage("전투판", L"UI이미지/UI_공격타이밍판_540_132.png");

	IMAGEMANAGER->AddImage("전투바_화이트", L"UI이미지/UI_공격타이밍바_10_151.png");
	IMAGEMANAGER->AddImage("전투바_블랙", L"UI이미지/UI_공격타이밍바_black_10_151.png");
	_attack_bar.img = IMAGEMANAGER->FindImage("전투바_화이트");

	_main_rc.x = WINSIZEX / 2;
	_main_rc.y = WINSIZEY / 2 + 70;
	_main_rc.width_max = 150;
	_main_rc.height_max = 150;
	_main_rc.rc = RectMakeCenter(_main_rc.x, _main_rc.y, _main_rc.width_max, _main_rc.height_max);

	_attack_bar.x = 30;
	_attack_bar.y = WINSIZEY / 2 - 5;
	_attack_bar_count = 0;

	_menu_action_count = 0;
	_menu_action_click = false;
	daCount = 1;
	daCount2 = 1;
	_isMercy = false;

	_enemy_attack_max = 100;

	isTurn = TALK_BUBBLE;
	_menu_main_count = 1;
	_menu_input1_count = 0;
	_battle_turn = 0;
	_isAttack_start = false;
	_isAttack_finish = false;
	_enemy_attack_count = 0;
	//==========다이얼로그==============

	_title_int = 1;
	_title_int2 = 1;
	_word_count = 0;
	_word_count2 = 0;
	_word_speed = 0;

	_heartPlayer.x = (_main_rc.rc.left + _main_rc.rc.right) / 2;
	_heartPlayer.y = (_main_rc.rc.top + _main_rc.rc.bottom) / 2;
	_heartPlayer.rc = RectMakeCenter(_heartPlayer.x, _heartPlayer.y, 20, 20);
	_heartPlayer.currentFrameX = _heartPlayer.currentFrameY = 0;
	_heartPlayer.speed = 3.0f;

	
	_heartPlayer.maxHP = 50;
	_heartPlayer.currentHP = 50;

	_bar = new progressBar;
	_bar->init(WINSIZEX / 2, WINSIZEY / 2 + 170, 60, 30);


	//폰트추가
	D2DRENDER->AddTextFormat(L"-윤디자인웹돋움");
	switch (bossName)
	{
	case 0:
		_boss_name = L"* 언다인";
		_boss_bubble = "언다인_말풍선";
		_boss_main = "언다인_메인";
		_boss_stage = "언다인_스테이지";
		for (int i = 0; i < 30; i++)
		{
			_select_talk[i] = _undy_talk[i];
		}
		_heartPlayer.img = IMAGEMANAGER->FindImage("RED");
		break;
	case 1:
		_boss_name = L"* 샌즈";
		_boss_bubble = "샌즈_말풍선";
		_boss_main = "샌즈_메인";
		_boss_stage = "샌즈_스테이지";
		for (int i = 0; i < 30; i++)
		{
			_select_talk[i] = _sans_talk[i];
		}
		_heartPlayer.img = IMAGEMANAGER->FindImage("BLUE");
		break;
	case 2:
		_boss_name = L"* 머펫";
		_boss_bubble = "머펫_말풍선";
		_boss_main = "머펫_메인";
		_boss_stage = "머펫_스테이지";
		for (int i = 0; i < 30; i++)
		{
			_select_talk[i] = _muffet_talk[i];
		}
		_heartPlayer.img = IMAGEMANAGER->FindImage("PURPLE");
		break;
	}



	talk_bubble_start(_boss_bubble, 1);
	talk_main_start(_boss_main, 1);



	return S_OK;
}

void battleUI::release()
{
}

void battleUI::update()
{	
	_bar->update();
	if (_heartPlayer.currentHP <= 0)_heartPlayer.currentHP = 0;
	_bar->setGauge(_heartPlayer.currentHP, _heartPlayer.maxHP);

	_heartPlayer.rc = RectMakeCenter(_heartPlayer.x, _heartPlayer.y, 20, 20);
	if (isTurn == TALK_BUBBLE)
	{
		
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_heartPlayer.x -= _heartPlayer.speed;
			if (_heartPlayer.rc.left < _main_rc.rc.left)
			{
				_heartPlayer.x += _heartPlayer.speed;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_heartPlayer.x += _heartPlayer.speed;
			if (_heartPlayer.rc.right > _main_rc.rc.right)
			{
				_heartPlayer.x -= _heartPlayer.speed;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_heartPlayer.y -= _heartPlayer.speed;
			if (_heartPlayer.rc.top < _main_rc.rc.top)
			{
				_heartPlayer.y += _heartPlayer.speed;
			}
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_heartPlayer.y += _heartPlayer.speed;
			if (_heartPlayer.rc.bottom > _main_rc.rc.bottom)
			{
				_heartPlayer.y -= _heartPlayer.speed;
			}
		}

	}
	if (isTurn == MENU_SELECT)
	{
		//메뉴 선택 키 왼쪽
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _menu_input1_count == 0)
		{
			_menu_main_count--;
			if (_menu_main_count < 1) _menu_main_count = 4;
		}
		//메뉴 선택 키 오른쪽
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _menu_input1_count == 0)
		{
			_menu_main_count++;
			if (_menu_main_count > 4) _menu_main_count = 1;
		}
		if (_menu_action_count != 0)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				_menu_action_count--;
				if (_menu_action_count < 1) _menu_action_count = 3;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				_menu_action_count++;
				if (_menu_action_count > 3) _menu_action_count = 1;
			}
		}
	}

	//Z버튼 == 엔터
	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		//메뉴선택 턴
		if (isTurn == MENU_SELECT)
		{
			//공격시작 후 공격바 멈추고 싶을떄
			if (_isAttack_start && !_isAttack_finish)
			{
				_isAttack_finish = true;
			}
			//공격창에서 Z버튼 누를 시 공격 시작
			if (_menu_input1_count == 1 && !_isAttack_start)
			{
				_attack_bar.x = 30;
				_isAttack_start = true;
			}
			//행동버튼에서 살펴보기, 애원하기, 도전하기
			if (_menu_input1_count == 2 && _menu_action_count == 1 && !_menu_action_click)
			{
				_word_count = 0;
				_menu_action_click = true;
				_str_main = INIDATA->loadDataString("우전없", _boss_main, "100");

			}
			if (_menu_input1_count == 2 && _menu_action_count == 2 && !_menu_action_click)
			{
				_word_count = 0;
				_menu_action_click = true;
				_str_main = INIDATA->loadDataString("우전없", _boss_main, "101");
			}
			if (_menu_input1_count == 2 && _menu_action_count == 3 && !_menu_action_click)
			{
				_word_count = 0;
				_menu_action_click = true;
				_str_main = INIDATA->loadDataString("우전없", _boss_main, "102");
			}
			if (_word_count == strlen(_word_cut) && _word_count >= 3)
			{
				_word_count = 0;
				_menu_action_click = false;
			}
			//행동버튼 누를시
			if (_menu_input1_count == 2 && _menu_action_count == 0)
			{
				_menu_action_count = 1;
				_word_count = 0;
			}

			//살려주기버튼 누를시
			if (_menu_input1_count == 4 && !_isMercy)
			{
				_isMercy = true;
				_word_count2 = 0;
			}
			//버튼 누른 메뉴로 이동
			_menu_input1_count = _menu_main_count;
		}
		//메인 대화 턴 =========수정해야함
		if (isTurn == TALK_MAIN)
		{
			//처음시작할때 메인대화
			if (talk_main_end(daCount))
			{
				_word_count = 0;
				_menu_main_count = 1;
				_menu_input1_count = 0;
				isTurn = MENU_SELECT;
				daCount++;
			}
			//처음이후 메인대화
			if (_word_count == strlen(_word_cut) && _word_count >= 3 && daCount > 1)
			{
				_word_count = 0;
				_menu_main_count = 1;
				_menu_input1_count = 0;
				isTurn = MENU_SELECT;
			}

		}
		//말풍선 턴
		if (isTurn == TALK_BUBBLE)
		{

			//말풍선에서 인게임으로 넘어가는 타이밍
			talk_bubble_end(_select_talk[_battle_turn]);

			//i가 대사의 길이와 같으면 다음 대사로 넘어감
			if (_word_count2 == strlen(_word_cut2) && _word_count2 >= 3 && !_isMercy)
			{
				_title_int2++;
				_word_count2 = 0;
				//이니데이터 title값을 변경해주기위해 int to string 변환
				_title_char2[1024] = _itoa_s(_title_int2, _title_char2, sizeof(_title_char2), 10);
				_str_bubble = INIDATA->loadDataString2("우전없", _boss_bubble, _title_char2);

			}
			//자비(살려주기)일때도 대사의 길이가 같으면 다음대사로
			if (_word_count2 == strlen(_word_cut2) && _word_count2 >= 3 && _isMercy)
			{
				_word_count2 = 0;
				isTurn = INGAME;
				_isMercy = false;
				_menu_input1_count = 0;

			}
		}
	}
	//X버튼 == 취소
	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		//메뉴선택 턴
		if (isTurn == MENU_SELECT)
		{
			//메뉴 선택 취소
			if (_menu_input1_count != 0 && !_isAttack_start && !_menu_action_click)
			{
				if (_menu_input1_count == 2 && _menu_action_count != 0 && _menu_action_click)
				{
					_menu_action_click = false;
				}
				else if (_menu_input1_count == 2 && _menu_action_count != 0 && !_menu_action_click) _menu_action_count = 0;
				else
				{
					_menu_main_count = _menu_input1_count;
					_menu_input1_count = 0;
				}

			}
		}
		//메인 대화 턴
		if (isTurn == TALK_MAIN || isTurn == MENU_SELECT && _menu_action_click)
		{
			//i가 대사의 길이와 같이 않으면 대사를 모두 표시
			if (_word_count != strlen(_str_main))	_word_count = strlen(_str_main);
		}
	}
	//자비(살려주기)
	if (_isMercy)
	{
		isTurn = TALK_BUBBLE;
		_str_bubble = INIDATA->loadDataString2("우전없", _boss_bubble, "200");
	}
	if (isTurn == TALK_MAIN)
	{
		if (daCount == 1) _str_main = INIDATA->loadDataString("우전없", _boss_main, "1");
		if (daCount > 1) _str_main = INIDATA->loadDataString("우전없", _boss_main, "2");
	}

	//메뉴 카운터2에 따른 텍스트 변경
	if (_menu_input1_count == 1) menu_select = _boss_name;
	if (_menu_input1_count == 2 && _menu_action_count == 0) menu_select = _boss_name;
	if (_menu_input1_count == 2 && _menu_action_count != 0) menu_select = L"* 살펴보기 \n* 애원하기 \n* 도전하기";
	if (_menu_input1_count == 3) menu_select = L" * 아이템 목록";
	if (_menu_input1_count == 4 && !_isMercy) menu_select = L" * 살려주기";
	//공격 실행 시 공격바 움직임
	if (_isAttack_start && !_isAttack_finish)
	{
		_attack_bar.x += 5;
		_attack_bar_count = 0;
		if (_attack_bar.x >= 560) _isAttack_finish = true;
	}
	//공격 완료 후
	if (_isAttack_start && _isAttack_finish)
	{
		_attack_bar_count++;
	}
	//공격 완료 후 깜박임 끝났을때
	if (_attack_bar_count >= 100)
	{
		_isAttack_start = false;
		_isAttack_finish = false;
		_heartPlayer.x = (_main_rc.rc.left + _main_rc.rc.right) / 2;
		_heartPlayer.y = (_main_rc.rc.top + _main_rc.rc.bottom) / 2;
		isTurn = TALK_BUBBLE;
		_title_char2[1024] = _itoa_s(_title_int2, _title_char2, sizeof(_title_char2), 10);
		_str_bubble = INIDATA->loadDataString2("우전없", _boss_bubble, _title_char2);
		_word_count2 = 0;
		_word_count = 0;
		_menu_input1_count = 0;
		_attack_bar_count = 0;
		_battle_turn++;
	}
	//인게임인 경우
	if (isTurn == INGAME)
	{
		_enemy_attack_count++;

		if (SCENEMANAGER->isCurrentScene("undybattle"))
		{
		_heartPlayer.x = (_main_rc.rc.left + _main_rc.rc.right) / 2;
		_heartPlayer.y = (_main_rc.rc.top + _main_rc.rc.bottom) / 2;
		

		}
	}
	//인게임 시간이 끝나면
	if (_enemy_attack_count >= _enemy_attack_max)
	{
		_word_count = 0;
		_enemy_attack_count = 0;
		isTurn = TALK_MAIN;

	}
	//메인 대화중, 메뉴 선택중, 메인 전투창 크기를 늘림
	if (isTurn == MENU_SELECT || isTurn == TALK_MAIN) main_rect_control_default(true);
	if (isTurn == TALK_BUBBLE) main_rect_control_default(false);

	//==========다이얼로그==============
	_word_speed++;

	//속도에 따라 타이핑 효과 생성
	if (_word_speed % 2 == 0)
	{
		if (isTurn == TALK_MAIN || isTurn == MENU_SELECT && _menu_action_click)
		{
			strncpy_s(_word_cut, sizeof(_word_cut), _str_main, _word_count * 2);
			_word_count++;
			if (_word_count >= strlen(_str_main)) _word_count = strlen(_str_main);
		}

		if (isTurn == TALK_BUBBLE)
		{
			strncpy_s(_word_cut2, sizeof(_word_cut2), _str_bubble, _word_count2 * 2);
			_word_count2++;
			if (_word_count2 >= strlen(_str_bubble)) _word_count2 = strlen(_str_bubble);
		}
		_word_speed = 0;

	}
		
		
}

void battleUI::render()
{
	_bar->render();


	//선택창 텍스트
	if (_menu_input1_count != 0 && !_isMercy && !_menu_action_click)
	{
		D2DRENDER->RenderText(120, 250, menu_select, 25, D2DRenderer::DefaultBrush::White);
	}
	//공격 시 이미지
	if (_isAttack_start)
	{
		_attack_ground->Render(0, 0, 1, 1, 0, 0, 0, 50, WINSIZEY / 2);
		_attack_bar.img->Render(0, 0, 1, 1, 0, 0, 0, _attack_bar.x, _attack_bar.y);
		if (_attack_bar_count % 10 < 5) _attack_bar.img = IMAGEMANAGER->FindImage("전투바_화이트");
		else _attack_bar.img = IMAGEMANAGER->FindImage("전투바_블랙");
	}
	//메인 전투창 렉트
	D2DRENDER->DrawRectangle
	(
		_main_rc.rc,
		D2DRenderer::DefaultBrush::White,
		5.F
	);
	//메뉴 off 이미지
	_menu_off[0]->Render(0, 0, 1, 1, 0, 0, 0, 20, WINSIZEY - 50);
	_menu_off[1]->Render(0, 0, 1, 1, 0, 0, 0, 20 + 150, WINSIZEY - 50);
	_menu_off[2]->Render(0, 0, 1, 1, 0, 0, 0, 20 + 300, WINSIZEY - 50);
	_menu_off[3]->Render(0, 0, 1, 1, 0, 0, 0, 20 + 450, WINSIZEY - 50);
	//말풍선
	if (isTurn == TALK_BUBBLE)	_speechBubble->Render(0, 0, 1, 1, 0, 0, 0, 400, 80);


	//메뉴 선택에 따른 이미지
	if (isTurn == MENU_SELECT)
	{
		if (_menu_main_count == 1 && !_isAttack_start)
		{
			_menu_on[0]->Render(0, 0, 1, 1, 0, 0, 0, 20, WINSIZEY - 50);
			if (_menu_input1_count == 1) _heart->Render(0, 0, 1, 1, 0, 0, 0, 100, WINSIZEY - 225);
			else _heart->Render(0, 0, 1, 1, 0, 0, 0, 30, WINSIZEY - 40);
		}
		if (_menu_main_count == 2 && !_isAttack_start)
		{
			_menu_on[1]->Render(0, 0, 1, 1, 0, 0, 0, 20 + 150, WINSIZEY - 50);
			if (_menu_input1_count == 2 && _menu_action_count == 0 && !_menu_action_click)
				_heart->Render(0, 0, 1, 1, 0, 0, 0, 100, WINSIZEY - 225);
			if (_menu_input1_count == 2 && _menu_action_count == 1 && !_menu_action_click)
				_heart->Render(0, 0, 1, 1, 0, 0, 0, 100, WINSIZEY - 225);
			if (_menu_input1_count == 2 && _menu_action_count == 2 && !_menu_action_click)
				_heart->Render(0, 0, 1, 1, 0, 0, 0, 100, WINSIZEY - 190);
			if (_menu_input1_count == 2 && _menu_action_count == 3 && !_menu_action_click)
				_heart->Render(0, 0, 1, 1, 0, 0, 0, 100, WINSIZEY - 155);
			if (_menu_input1_count != 2) _heart->Render(0, 0, 1, 1, 0, 0, 0, 30 + 150, WINSIZEY - 40);
		}
		if (_menu_main_count == 3 && !_isAttack_start)
		{
			_menu_on[2]->Render(0, 0, 1, 1, 0, 0, 0, 20 + 300, WINSIZEY - 50);
			if (_menu_input1_count == 3) _heart->Render(0, 0, 1, 1, 0, 0, 0, 100, WINSIZEY - 225);
			else _heart->Render(0, 0, 1, 1, 0, 0, 0, 30 + 300, WINSIZEY - 40);
		}
		if (_menu_main_count == 4 && !_isAttack_start)
		{
			_menu_on[3]->Render(0, 0, 1, 1, 0, 0, 0, 20 + 450, WINSIZEY - 50);
			if (_menu_input1_count == 4) _heart->Render(0, 0, 1, 1, 0, 0, 0, 100, WINSIZEY - 225);
			else _heart->Render(0, 0, 1, 1, 0, 0, 0, 30 + 450, WINSIZEY - 40);
		}

	}

	//==========다이얼로그==============
	//메인
	if (isTurn == TALK_MAIN || isTurn == MENU_SELECT && _menu_action_click)
	{
		D2DRENDER->RenderTextField(70, 200, ConverCtoWC(_word_cut), D2D1::ColorF::White, 25, 500, 200, 1,
			DWRITE_TEXT_ALIGNMENT_LEADING, L"-윤디자인웹돋움");
	}
	//말풍선
	if (isTurn == TALK_BUBBLE)
	{
		D2DRENDER->RenderTextField(440, 80, ConverCtoWC(_word_cut2), D2D1::ColorF::Black, 19, 180, 100, 1,
			DWRITE_TEXT_ALIGNMENT_LEADING, L"-윤디자인웹돋움");
	}
	//========================================================================================gkxm
	D2DRENDER->RenderText(10, 395, L"PLAYER : 우전없", 20, D2DRenderer::DefaultBrush::White);
	D2DRENDER->RenderText(230, 395, L"H  P", 20, D2DRenderer::DefaultBrush::White);
	if (isTurn == TALK_BUBBLE|| isTurn == INGAME)_heartPlayer.img->autoFrameRender(_heartPlayer.rc.left, _heartPlayer.rc.top, _heartPlayer.currentFrameX, _heartPlayer.currentFrameY);

}
//메인 전투 렉트 컨트롤함수 기본값		 (늘리고 싶으면 true, 줄이고 싶으면 false)
void battleUI::main_rect_control_default(bool expandOrReduce)
{
	if (expandOrReduce)
	{
		_main_rc.width_max += 15;
		_main_rc.height_max += 15;
		if (_main_rc.width_max >= 550) _main_rc.width_max = 550;
		if (_main_rc.height_max >= 160) _main_rc.height_max = 160;
	}
	else
	{
		_main_rc.width_max -= 15;
		_main_rc.height_max -= 15;
		if (_main_rc.width_max <= 150) _main_rc.width_max = 150;
		if (_main_rc.height_max <= 150) _main_rc.height_max = 150;
	}
	_main_rc.rc = RectMakeCenter(_main_rc.x, _main_rc.y, _main_rc.width_max, _main_rc.height_max);
}
//메인 전투 렉트 컨트롤함수 커스터마이징(늘릴지 줄일지 여부,	 크기변환 속도,	최소 혹은 최대 넓이,	최소 혹은 최대 높이)
void battleUI::main_rect_control_customizing(bool expandOrReduce, int speed, int maxSizeWidth, int maxSizeHeight)
{
	if (isTurn == INGAME)
	{
		if (expandOrReduce)
		{
			_main_rc.width_max += speed;
			_main_rc.height_max += speed;
			if (_main_rc.width_max >= maxSizeWidth) _main_rc.width_max = maxSizeWidth;
			if (_main_rc.height_max >= maxSizeHeight) _main_rc.height_max = maxSizeHeight;
		}
		else
		{
			_main_rc.width_max -= speed;
			_main_rc.height_max -= speed;
			if (_main_rc.width_max <= maxSizeWidth) _main_rc.width_max = maxSizeWidth;
			if (_main_rc.height_max <= maxSizeHeight) _main_rc.height_max = maxSizeHeight;
		}
		_main_rc.rc = RectMakeCenter(_main_rc.x, _main_rc.y, _main_rc.width_max, _main_rc.height_max);
	}
}



//wchar_t 에서 char 로의 형변환 함수
char * battleUI::ConvertWCtoC(wchar_t * str)
{
	//반환할 char* 변수 선언
	char* pStr;

	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
	//char* 메모리 할당
	pStr = new char[strSize];

	//형 변환 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}
//char 에서 wchar_t 로의 형변환 함수
wchar_t * battleUI::ConverCtoWC(char * str)
{
	//wchar_t형 변수 선언
	wchar_t* pStr;
	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);
	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];
	//형 변환
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
	return pStr;
}

void battleUI::talk_bubble_start(const char * subject, int startNum)
{
	_title_int2 = startNum;
	char title_name[64];
	title_name[32] = _itoa_s(startNum, title_name, sizeof(title_name), 10);
	_str_bubble = INIDATA->loadDataString2("우전없", subject, title_name);
}

void battleUI::talk_bubble_end(int endNum)
{
	if (endNum == _title_int2 && _word_count2 == strlen(_word_cut2) && _word_count2 >= 3)
	{
		isTurn = INGAME;
	}
}

void battleUI::talk_main_start(const char * subject, int startNum)
{
	char title_name[64];
	title_name[32] = _itoa_s(startNum, title_name, sizeof(title_name), 10);
	_str_main = INIDATA->loadDataString("우전없", subject, title_name);
}

bool battleUI::talk_main_end(int endNum)
{
	if (endNum == _title_int && _word_count == strlen(_word_cut) && _word_count >= 3)
	{
		return true;
	}
	else return false;
}



