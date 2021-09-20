#pragma once
#include "singletonBase.h"
#include "stage5.h"

class invenManager : public singletonBase<invenManager>
{
private:

	vector<tagItemInfo>				_vInven;
	vector<tagItemInfo>::iterator	_vIterInven;

	bool _open;

	RECT _inven;
	int _invenMax; //최대 용량


public:
	invenManager() {};
	~invenManager() {};

	HRESULT init();

	void release();
	void update();
	void render();

	void in(tagItemInfo item);
	void out();
	void open();
	void close();
	void clear();


	vector<tagItemInfo> getVInven() { return _vInven; }
	void setInven(vector<tagItemInfo> vInven) { _vInven = vInven; }
};

