#pragma once
#include "singletonBase.h"
#include "stage5.h"

class player;

class saveLoadManager :  public singletonBase<saveLoadManager>
{
private:
	vector<tagItemInfo> _vInven;
	player* _player;

	int _timer;
	bool _go;
	bool _save, _load;
	float _alpha;

public:
	saveLoadManager();
	~saveLoadManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void save();
	void load();

	void sceneSet();

	void linkPlayer(player* player) { _player = player; }
};

