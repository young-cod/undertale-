#pragma once
#include "gameNode.h"
#include "progressBar.h"
#define PI 3.14156f
//메인렉트 컨트롤
struct rc_control
{
	RECT rc;
	int x, y;
	int width_max, height_max;
};
struct battle_bar
{
	Image* img;
	RECT rc;
	int x, y;
};
//턴 상태
enum TURN_STATE
{
	MENU_SELECT,
	TALK_BUBBLE,
	INGAME,
	TALK_MAIN
};



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@하트 구조체
struct inGameHeart
{
	Image* img;
	RECT rc;
	int currentHP;
	int maxHP;
	float x, y;
	float speed;
	int currentFrameX;
	int currentFrameY;
	bool isBattle;

};


class battleUI : public gameNode
{
private:
	//메인 렉트
	rc_control _main_rc;
	inGameHeart _heartPlayer;
	Image* _menu_off[4];
	Image* _menu_on[4];
	Image* _heart;
	Image* _speechBubble;
	Image* _attack_ground;
	battle_bar _attack_bar;

	progressBar* _bar;
	float _hp;

	int daCount;
	int daCount2;


	TURN_STATE isTurn;
	//메뉴 선택(공격, 행동, 아이템, 자비)
	int _menu_main_count;
	//메뉴 선택 후 인메뉴
	int _menu_input1_count;
	//행동 선택 후 인메뉴
	int _menu_action_count;
	bool _menu_action_click;
	//배틀 턴 횟수
	int _battle_turn;

	//_menu_main_count(공격) 일때
	//공격시작과 공격 끝 여부
	bool _isAttack_start;
	bool _isAttack_finish;
	//공격바 카운트
	int _attack_bar_count;

	//적공격 중
	int _enemy_attack_count;
	int _enemy_attack_max;

	//_menu_main_count(자비) 일때
	bool _isMercy;

	const wchar_t* menu_select;
	const wchar_t* menu_action;

	//==========다이얼로그==============
	//원본 대사 변수
	char* _str_main;
	char* _str_bubble;

	//타이핑 효과를 위해 원본 대사에서 잘라온 변수
	char _word_cut[1024];
	char _word_cut2[1024];

	//ini데이터 Title 순번을 넘기기 위한 변수
	char _title_char[64];
	int _title_int;
	char _title_char2[64];
	int _title_int2;

	//글자 갯수
	int _word_count;
	int _word_count2;

	//글자 속도
	int _word_speed;
	//=================================
	//보스 선택에 따른 ini파일 타이틀
	const char* _boss_bubble;
	const char* _boss_main;
	const char* _boss_stage;
	const wchar_t* _boss_name;
	//==================================
	//대사 끊는 타이밍
	//언다인 총 18턴
	int _undy_talk[30] = { 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
	//샌즈 총 27턴
	int _sans_talk[30] = { 4, 6, 9, 11, 14, 18, 22, 25, 26, 31, 33, 37, 39, 41, 42, 44, 47, 49, 52, 57, 59, 62, 64, 65, 69, 70, 103, 114 };
	//머펫 총 17턴
	int _muffet_talk[30] = { 1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 19, 20, };
	int _asriel_talk[30] = { 4, 5, 7 };
	int _select_talk[30];

public:
	battleUI();
	~battleUI();

	virtual HRESULT init(int bossName);
	virtual void release();
	virtual void update();
	virtual void render();



	char* ConvertWCtoC(wchar_t* str);
	wchar_t* ConverCtoWC(char* str);

	void talk_bubble_start(const char* subject, int startNum);
	void talk_bubble_end(int endNum);
	void talk_main_start(const char* subject, int startNum);
	bool talk_main_end(int endNum);

	//메인렉트 조절
	void main_rect_control_default(bool expandOrReduce);
	void main_rect_control_customizing(bool expandOrReduce, int speed, int maxSizeWidth, int maxSizeHeight);
	//메인렉트 get
	RECT get_main_rect() { return _main_rc.rc; }
	//전투시간 조절 get, set
	int getEnemy_attackTime_max() { return _enemy_attack_max; }
	void setEnemy_attackTime_max(int maxTime) { _enemy_attack_max = maxTime; }
	//턴 get
	int getBattle_turn() { return _battle_turn; }
	//상태 get
	int getState() { return isTurn; }
	//대사_메인 카운트 get
	int get_main_talk_count() { return _title_int; }
	//대사_말풍선 카운트 get
	int get_bubble_talk_count() { return _title_int2; }
	//현재전투시간 get하나 만들었습니다..
	int getEnemy_attackTime() { return _enemy_attack_count; }

	inGameHeart getIGH() { return _heartPlayer; }
	void set_inGame_heart_x(float inGameHeart_x) { _heartPlayer.x = inGameHeart_x; }
	void set_inGame_heart_y(float inGameHeart_y) { _heartPlayer.y = inGameHeart_y; }
	void set_inGame_heart_rc(RECT inGameHeart_rc) { _heartPlayer.rc = inGameHeart_rc; }
	void set_inGame_heart_image(Image* _inGameHeart_image) { _heartPlayer.img = _inGameHeart_image; }
	//현재체력
	void set_inGame_heart_currentHp(float currentHp) { _heartPlayer.currentHP = currentHp; }

};
