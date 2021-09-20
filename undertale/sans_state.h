#pragma once
#define BONEMAX 20
#define BONEMAX50 50

class sansBattle;

struct objectBone
{
	Image* img;
	RECT rc;
	float x, y;
	int width, hieght;
	float angle;
	int currentFrameX;
	int currentFrameY;
	bool isColision;
};

class sans_state
{
private:
	sansBattle* _sanBattle;
protected:
	//=======충돌부분=========
	objectBone _bone_20[BONEMAX50];
	objectBone _bone_40[BONEMAX50];
	objectBone _bone_50[BONEMAX50];
	objectBone _bone_100[BONEMAX50];
	objectBone _laser_bim[BONEMAX50];

	//=======충돌안함=========
	objectBone _bone2_100[BONEMAX50];
	objectBone _foothold[BONEMAX50];
	objectBone _laser_body[BONEMAX50];
	//==============================
	float _bone_speed;
	bool _isJump;
	float _jumpPower;
public:

	virtual sans_state* inputHandle(sansBattle* sansBattle) = 0;
	virtual	void update(sansBattle* sansBattle) = 0;
	virtual	void enter(sansBattle* sansBattle) = 0;
	virtual void render(sansBattle* sansBattle) = 0;
	virtual void exit(sansBattle* sansBattle) = 0;

	void heart_control(sansBattle* sansBattle, bool gravity_bool, float gravity, float jumpPower);
	void collision(sansBattle* sansBattle, RECT rect);
	void linkSans(sansBattle* sans) { _sanBattle = sans; }

	//충돌부분 get
	objectBone get_bone_20(int index) { return _bone_20[index]; }
	objectBone get_bone_40(int index) { return _bone_40[index]; }
	objectBone get_bone_50(int index) { return _bone_50[index]; }
	objectBone get_bone_100(int index) { return _bone_100[index]; }
	objectBone get__laser_bim(int index) { return _laser_bim[index]; }
	//충돌부분 set
	void set_bone_20(int index, bool isColision) {  _bone_20[index].isColision = isColision; }
	void set_bone_40(int index, bool isColision) {  _bone_40[index].isColision = isColision; }
	void set_bone_50(int index, bool isColision) {  _bone_50[index].isColision = isColision; }
	void set_bone_100(int index, bool isColision) {  _bone_100[index].isColision = isColision; }
	void set_laser_bim(int index, bool isColision) { _laser_bim[index].isColision = isColision; }
};

