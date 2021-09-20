#pragma once
#include "singletonBase.h"
#include "image.h"

class player;
class undybattle;

struct tagBullet
{
	RECT rc;
	Image* img;
	float x, y;
	float angle;
	float fireX, fireY;
	float speed;

	bool isFire;
	int damage;
};

class bulletManager :	public singletonBase<bulletManager>
{
private:
	vector<tagBullet>			_vBullet;
	vector<tagBullet>::iterator _viBullet;
	tagBullet _bullet;
	const char* _imageName;

	Image* _img;
	float _range;	//�Ѿ��� ������ ���󰥰��ΰ�
	int _bulletMax; //�Ѿ� �ִ� ����

	undybattle* _undybattle;
	player* _player;
public:
	bulletManager() {};
	~bulletManager() {};

	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	void move();
	void fire(float fireX, float fireY, float angle);

	void linkPlayer(player* player) { _player = player; }
	void linkUndybattle(undybattle* undybattle) { _undybattle = undybattle; }

	vector<tagBullet> getVBullet() { return _vBullet; }
	vector<tagBullet>::iterator getViBullet() { return _viBullet; }

};

