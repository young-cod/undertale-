#pragma once
#include "gameNode.h"
#include "progressBar.h"
#define PI 3.14156f
//���η�Ʈ ��Ʈ��
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
//�� ����
enum TURN_STATE
{
	MENU_SELECT,
	TALK_BUBBLE,
	INGAME,
	TALK_MAIN
};



//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@��Ʈ ����ü
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
	//���� ��Ʈ
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
	//�޴� ����(����, �ൿ, ������, �ں�)
	int _menu_main_count;
	//�޴� ���� �� �θ޴�
	int _menu_input1_count;
	//�ൿ ���� �� �θ޴�
	int _menu_action_count;
	bool _menu_action_click;
	//��Ʋ �� Ƚ��
	int _battle_turn;

	//_menu_main_count(����) �϶�
	//���ݽ��۰� ���� �� ����
	bool _isAttack_start;
	bool _isAttack_finish;
	//���ݹ� ī��Ʈ
	int _attack_bar_count;

	//������ ��
	int _enemy_attack_count;
	int _enemy_attack_max;

	//_menu_main_count(�ں�) �϶�
	bool _isMercy;

	const wchar_t* menu_select;
	const wchar_t* menu_action;

	//==========���̾�α�==============
	//���� ��� ����
	char* _str_main;
	char* _str_bubble;

	//Ÿ���� ȿ���� ���� ���� ��翡�� �߶�� ����
	char _word_cut[1024];
	char _word_cut2[1024];

	//ini������ Title ������ �ѱ�� ���� ����
	char _title_char[64];
	int _title_int;
	char _title_char2[64];
	int _title_int2;

	//���� ����
	int _word_count;
	int _word_count2;

	//���� �ӵ�
	int _word_speed;
	//=================================
	//���� ���ÿ� ���� ini���� Ÿ��Ʋ
	const char* _boss_bubble;
	const char* _boss_main;
	const char* _boss_stage;
	const wchar_t* _boss_name;
	//==================================
	//��� ���� Ÿ�̹�
	//����� �� 18��
	int _undy_talk[30] = { 2, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22 };
	//���� �� 27��
	int _sans_talk[30] = { 4, 6, 9, 11, 14, 18, 22, 25, 26, 31, 33, 37, 39, 41, 42, 44, 47, 49, 52, 57, 59, 62, 64, 65, 69, 70, 103, 114 };
	//���� �� 17��
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

	//���η�Ʈ ����
	void main_rect_control_default(bool expandOrReduce);
	void main_rect_control_customizing(bool expandOrReduce, int speed, int maxSizeWidth, int maxSizeHeight);
	//���η�Ʈ get
	RECT get_main_rect() { return _main_rc.rc; }
	//�����ð� ���� get, set
	int getEnemy_attackTime_max() { return _enemy_attack_max; }
	void setEnemy_attackTime_max(int maxTime) { _enemy_attack_max = maxTime; }
	//�� get
	int getBattle_turn() { return _battle_turn; }
	//���� get
	int getState() { return isTurn; }
	//���_���� ī��Ʈ get
	int get_main_talk_count() { return _title_int; }
	//���_��ǳ�� ī��Ʈ get
	int get_bubble_talk_count() { return _title_int2; }
	//���������ð� get�ϳ� ��������ϴ�..
	int getEnemy_attackTime() { return _enemy_attack_count; }

	inGameHeart getIGH() { return _heartPlayer; }
	void set_inGame_heart_x(float inGameHeart_x) { _heartPlayer.x = inGameHeart_x; }
	void set_inGame_heart_y(float inGameHeart_y) { _heartPlayer.y = inGameHeart_y; }
	void set_inGame_heart_rc(RECT inGameHeart_rc) { _heartPlayer.rc = inGameHeart_rc; }
	void set_inGame_heart_image(Image* _inGameHeart_image) { _heartPlayer.img = _inGameHeart_image; }
	//����ü��
	void set_inGame_heart_currentHp(float currentHp) { _heartPlayer.currentHP = currentHp; }

};
